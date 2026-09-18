#include "memscan.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/uio.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/syscall.h>
#include <thread>
#include <mutex>
#include <atomic>

#ifdef __aarch64__
#define process_vm_readv_syscall 270
#define process_vm_writev_syscall 271
#elif __arm__
#define process_vm_readv_syscall 376
#define process_vm_writev_syscall 377
#elif __x86_64__
#define process_vm_readv_syscall 310
#define process_vm_writev_syscall 311
#elif __i386__
#define process_vm_readv_syscall 347
#define process_vm_writev_syscall 348
#else
#define process_vm_readv_syscall 0
#define process_vm_writev_syscall 0
#endif

// State
static pid_t g_targetPid = -1;
static std::vector<MemoryRegion> g_memoryRegions;

// Fast Read/Write menggunakan syscall untuk menghindari ptrace (lebih stealth)
static ssize_t process_v_read(pid_t pid, void* local_buf, size_t size, uintptr_t remote_addr) {
    if (pid <= 0) return -1;
    struct iovec local[1];
    struct iovec remote[1];
    local[0].iov_base = local_buf;
    local[0].iov_len = size;
    remote[0].iov_base = (void*)remote_addr;
    remote[0].iov_len = size;
    ssize_t res = syscall(process_vm_readv_syscall, pid, local, 1, remote, 1, 0);
    if (res < 0) {
        char memPath[256];
        snprintf(memPath, sizeof(memPath), "/proc/%d/mem", pid);
        int fd = open(memPath, O_RDONLY);
        if (fd < 0) return -1;
        res = pread(fd, local_buf, size, remote_addr);
        close(fd);
    }
    return res;
}

static ssize_t process_v_write(pid_t pid, const void* local_buf, size_t size, uintptr_t remote_addr) {
    if (pid <= 0) return -1;
    struct iovec local[1];
    struct iovec remote[1];
    local[0].iov_base = (void*)local_buf;
    local[0].iov_len = size;
    remote[0].iov_base = (void*)remote_addr;
    remote[0].iov_len = size;
    ssize_t res = syscall(process_vm_writev_syscall, pid, local, 1, remote, 1, 0);
    if (res < 0) {
        // ANTI-BAN: Menghapus fallback /proc/%d/mem untuk WRONLY karena sangat mudah 
        // dideteksi oleh Anti-Cheat (terutama FreeFire). 
        // Jika syscall process_vm_writev gagal, lebih baik return error daripada auto-ban.
        return -1;
    }
    return res;
}

// Dapatkan PID dari nama proses
static pid_t GetProcessId(const char* processName) {
    DIR* dir = opendir("/proc");
    if (dir == nullptr) return -1;

    struct dirent* entry;
    pid_t pid = -1;
    while ((entry = readdir(dir)) != nullptr) {
        int currentPid = atoi(entry->d_name);
        if (currentPid != 0) {
            char cmdlinePath[256];
            snprintf(cmdlinePath, sizeof(cmdlinePath), "/proc/%d/cmdline", currentPid);
            int fd = open(cmdlinePath, O_RDONLY);
            if (fd != -1) {
                char cmdline[256];
                ssize_t bytesRead = read(fd, cmdline, sizeof(cmdline));
                close(fd);
                if (bytesRead > 0 && strcmp(cmdline, processName) == 0) {
                    pid = currentPid;
                    break;
                }
            }
        }
    }
    closedir(dir);
    return pid;
}

// Parse /proc/pid/maps untuk mendapatkan region memory
static void ParseMemoryMaps(pid_t pid) {
    g_memoryRegions.clear();
    char mapsPath[256];
    snprintf(mapsPath, sizeof(mapsPath), "/proc/%d/maps", pid);

    std::ifstream mapsFile(mapsPath);
    if (!mapsFile.is_open()) return;

    std::string line;
    while (std::getline(mapsFile, line)) {
        // Scan ALL readable regions (r--p or rw-p)
        if (line.find("r") != std::string::npos && line.find("p") != std::string::npos) {
            unsigned long long start_addr = 0, end_addr = 0;
            sscanf(line.c_str(), "%llx-%llx", &start_addr, &end_addr);
            if (end_addr > start_addr) {
                MemoryRegion region;
                region.start = (uintptr_t)start_addr;
                region.end = (uintptr_t)end_addr;
                region.isReadable = true;
                region.isWritable = (line.find("w") != std::string::npos);
                g_memoryRegions.push_back(region);
            }
        }
    }
}

bool MemScan_Attach(pid_t pid) {
    g_targetPid = pid;
    if (g_targetPid <= 0) return false;
    ParseMemoryMaps(g_targetPid);
    return !g_memoryRegions.empty();
}

std::vector<ScanResult> MemScan_SearchPattern(const char* pattern, const char* mask) {
    std::vector<ScanResult> results;
    if (g_targetPid == -1) return results;

    size_t patternLen = strlen(mask);
    uint8_t firstByte = (uint8_t)pattern[0];
    bool hasWildcard = (strchr(mask, '?') != nullptr);
    
    std::mutex res_mtx;
    const int NUM_THREADS = 4;
    std::vector<std::thread> threads;

    auto worker = [&](int thread_idx) {
        const size_t CHUNK_SIZE = 4096 * 1024;
        std::vector<uint8_t> bufferVec(CHUNK_SIZE);
        uint8_t* buffer = bufferVec.data();
        std::vector<ScanResult> local_results;

        for (size_t r = thread_idx; r < g_memoryRegions.size(); r += NUM_THREADS) {
            const auto& region = g_memoryRegions[r];
            size_t regionSize = region.end - region.start;
            for (uintptr_t offset = 0; offset < regionSize; offset += CHUNK_SIZE) {
                size_t readSize = std::min(CHUNK_SIZE, regionSize - offset);
                if (process_v_read(g_targetPid, buffer, readSize, region.start + offset) != (ssize_t)readSize) {
                    continue;
                }

                if (!hasWildcard) {
                    uint8_t* searchStart = buffer;
                    size_t searchLen = readSize;
                    while (searchLen >= patternLen) {
                        void* matchPtr = memmem(searchStart, searchLen, pattern, patternLen);
                        if (!matchPtr) break;
                        
                        size_t matchIndex = (size_t)((uint8_t*)matchPtr - buffer);
                        ScanResult result;
                        result.address = region.start + offset + matchIndex;
                        result.originalValue.assign((uint8_t*)matchPtr, (uint8_t*)matchPtr + patternLen);
                        local_results.push_back(result);
                        
                        searchStart = (uint8_t*)matchPtr + 1;
                        searchLen = readSize - (matchIndex + 1);
                    }
                } else {
                    for (size_t i = 0; i <= readSize - patternLen; ++i) {
                        if (mask[0] != '?') {
                            void* matchPtr = memchr(buffer + i, firstByte, readSize - i - patternLen + 1);
                            if (!matchPtr) break;
                            i = (size_t)((uint8_t*)matchPtr - buffer);
                        }
                        bool match = true;
                        for (size_t j = 1; j < patternLen; ++j) {
                            if (mask[j] != '?' && buffer[i + j] != (uint8_t)pattern[j]) {
                                match = false;
                                break;
                            }
                        }
                        if (match) {
                            ScanResult result;
                            result.address = region.start + offset + i;
                            result.originalValue.assign(&buffer[i], &buffer[i + patternLen]);
                            local_results.push_back(result);
                        }
                    }
                }
            }
        }
        std::lock_guard<std::mutex> lock(res_mtx);
        results.insert(results.end(), local_results.begin(), local_results.end());
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(worker, i);
    }
    for (auto& t : threads) {
        t.join();
    }

    // bufferVec will be destroyed automatically
    return results;
}

bool MemScan_ReplaceBytes(uintptr_t address, const std::vector<uint8_t>& newBytes) {
    if (g_targetPid == -1) return false;
    ssize_t written = process_v_write(g_targetPid, newBytes.data(), newBytes.size(), address);
    return written == (ssize_t)newBytes.size();
}

bool MemScan_ReplaceFloat(uintptr_t address, float newValue) {
    if (g_targetPid == -1) return false;
    ssize_t written = process_v_write(g_targetPid, &newValue, sizeof(newValue), address);
    return written == sizeof(newValue);
}

bool MemScan_ReplaceDword(uintptr_t address, uint32_t newValue) {
    if (g_targetPid == -1) return false;
    ssize_t written = process_v_write(g_targetPid, &newValue, sizeof(newValue), address);
    return written == sizeof(newValue);
}

// -----------------------------------------------------------------------
// Helper GG Format
// -----------------------------------------------------------------------
static void ParseHexPattern(const char* hexString, std::string& pattern, std::string& mask) {
    pattern.clear();
    mask.clear();
    std::string hexStr = hexString;
    size_t i = 0;
    while (i < hexStr.length()) {
        // Abaikan spasi dan awalan 'h' / 'H' khas GameGuardian
        if (hexStr[i] == ' ' || hexStr[i] == 'h' || hexStr[i] == 'H') {
            i++;
            continue;
        }
        if (hexStr[i] == '?' && (i + 1 < hexStr.length() && hexStr[i + 1] == '?')) {
            pattern += '\x00';
            mask += '?';
            i += 2;
        } else if (i + 1 < hexStr.length()) {
            char byteStr[3] = {hexStr[i], hexStr[i + 1], '\0'};
            uint8_t byteVal = (uint8_t)strtol(byteStr, nullptr, 16);
            pattern += (char)byteVal;
            mask += 'x';
            i += 2;
        } else {
            i++;
        }
    }
}

std::vector<ScanResult> MemScan_SearchHex(const char* hexPattern) {
    std::string pattern, mask;
    ParseHexPattern(hexPattern, pattern, mask);
    return MemScan_SearchPattern(pattern.c_str(), mask.c_str());
}

bool MemScan_ReplaceHex(uintptr_t address, const char* hexPattern) {
    std::string pattern, mask;
    ParseHexPattern(hexPattern, pattern, mask);
    std::vector<uint8_t> newBytes(pattern.begin(), pattern.end());
    return MemScan_ReplaceBytes(address, newBytes);
}

bool MemScan_SafeRevertHex(uintptr_t address, const char* originalHex, const char* replacedHex) {
    std::string r_pattern, r_mask;
    ParseHexPattern(replacedHex, r_pattern, r_mask);
    
    if (g_targetPid == -1) return false;
    
    std::vector<uint8_t> currentMem(r_pattern.length());
    ssize_t read_bytes = process_v_read(g_targetPid, currentMem.data(), r_pattern.length(), address);
    
    if (read_bytes != (ssize_t)r_pattern.length()) return false;
    
    bool stillOurs = true;
    for (size_t i = 0; i < r_pattern.length(); ++i) {
        if (r_mask[i] != '?' && currentMem[i] != (uint8_t)r_pattern[i]) {
            stillOurs = false;
            break;
        }
    }
    
    if (stillOurs) {
        return MemScan_ReplaceHex(address, originalHex);
    }
    return false;
}

void MemScan_Detach() {
    g_targetPid = -1;
    g_memoryRegions.clear();
}
