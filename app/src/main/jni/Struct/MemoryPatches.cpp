#include "MemoryPatches.h"
#include "memscan.h"
#include <mutex>
#include <unistd.h>
#include <android/log.h>

#define MP_LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "MemPatch", __VA_ARGS__)

static std::mutex g_patchMtx;

std::string ApplyMemoryPatch(int patchId, bool enable) {
    std::lock_guard<std::mutex> lock(g_patchMtx);

    pid_t target_pid = getpid();
    MP_LOGD("ApplyMemoryPatch: patchId=%d enable=%d pid=%d", patchId, enable, target_pid);

    if (!MemScan_Attach(target_pid)) {
        MP_LOGD("MemScan_Attach failed!");
        return "Failed: Process not found!";
    }

    std::string status = "Status: Failed";

    switch (patchId) {
        case 1: { // Camera Left
            const char* scanString_ON    = "00 00 00 00 00 00 80 3f 00 00 00 00 00 00 00 00 00 00 80 bf 00 00 00 00 00 00 80 bf 00 00 00 00 00 00 00 00 00 00 80 3f 00 00 00 00 00 00 00 00";
            const char* replaceString_ON = "00 00 00 00 00 00 80 40 00 00 00 00 00 00 00 00 00 00 80 bf 00 00 00 00 00 00 80 bf 00 00 00 00 00 00 00 00 00 00 80 3f 00 00 00 00 00 00 80 bf";

            static std::vector<uintptr_t> saved_addr_cam;

            if (enable) {
                saved_addr_cam.clear();
                bool foundAny = false;
                auto results = MemScan_SearchHex(scanString_ON);
                int count = 0;
                for (auto res : results) {
                    if (MemScan_ReplaceHex(res.address, replaceString_ON)) {
                        saved_addr_cam.push_back(res.address);
                        foundAny = true;
                        count++;
                        if (count >= 50) break;
                    }
                }
                status = foundAny ? "Status: Camera Activated" : "Status: Failed";
            } else {
                bool revertedAny = false;
                for (auto addr : saved_addr_cam) {
                    if (MemScan_SafeRevertHex(addr, scanString_ON, replaceString_ON)) {
                        revertedAny = true;
                    }
                }
                saved_addr_cam.clear();
                status = revertedAny ? "Status: Camera Deactivated" : "Status: Failed";
            }
            break;
        }
        
        case 2: { // Sniper Switch
            const char* scanString_ON    = "3F 00 00 80 3E 00 00 00 00 04 00 00 00 00 00 80 3F 00 00 20 41 00 00 34 42 01 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 80 3F";
            const char* replaceString_ON = "1A 00 00 80 1A 00 00 00 00 04 00 00 00 00 00 80 3F 00 00 20 41 00 00 34 42 01 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 80 3F"; 
            
            static std::vector<uintptr_t> saved_addr_sniper;

            if (enable) {
                saved_addr_sniper.clear();
                bool foundAny = false;
                auto results = MemScan_SearchHex(scanString_ON);
                int count = 0;
                for (auto res : results) {
                    if (MemScan_ReplaceHex(res.address, replaceString_ON)) {
                        saved_addr_sniper.push_back(res.address);
                        foundAny = true;
                        count++;
                        if (count >= 50) break;
                    }
                }
                status = foundAny ? "Status: Sniper Switch Activated" : "Status: Failed";
            } else {
                bool revertedAny = false;
                for (auto addr : saved_addr_sniper) {
                    if (MemScan_SafeRevertHex(addr, scanString_ON, replaceString_ON)) {
                        revertedAny = true;
                    }
                }
                saved_addr_sniper.clear();
                status = revertedAny ? "Status: Sniper Switch Deactivated" : "Status: Failed";
            }
            break;
        }
        
        case 3: { // Fast Fire (Double Patch)
            const char* s1_ON = "00 00 80 40 33 33 93 40 3D 0A F7 3F";
            const char* r1_ON = "00 00 80 40 00 00 80 40 CB D2 4D 3E";
            
            const char* s2_ON = "02 2B 07 3D 02 2B 07 3D 02 2B 07 3D";
            const char* r2_ON = "08 39 60 3B";
            
            static std::vector<uintptr_t> saved_addr_1;
            static std::vector<uintptr_t> saved_addr_2;

            if (enable) {
                saved_addr_1.clear();
                saved_addr_2.clear();
                
                bool foundAny = false;
                MP_LOGD("FastFire: scanning pattern 1...");
                auto results1 = MemScan_SearchHex(s1_ON);
                MP_LOGD("FastFire: found %zu results for pattern 1", results1.size());
                int count1 = 0;
                for (auto res : results1) {
                    if (MemScan_ReplaceHex(res.address, r1_ON)) {
                        saved_addr_1.push_back(res.address);
                        foundAny = true;
                        count1++;
                        MP_LOGD("FastFire: patched pattern 1 at %p", (void*)res.address);
                        if (count1 >= 50) break;
                    }
                }
                
                MP_LOGD("FastFire: scanning pattern 2...");
                auto results2 = MemScan_SearchHex(s2_ON);
                MP_LOGD("FastFire: found %zu results for pattern 2", results2.size());
                int count2 = 0;
                for (auto res : results2) {
                    if (MemScan_ReplaceHex(res.address, r2_ON)) {
                        saved_addr_2.push_back(res.address);
                        foundAny = true;
                        count2++;
                        MP_LOGD("FastFire: patched pattern 2 at %p", (void*)res.address);
                        if (count2 >= 50) break;
                    }
                }

                status = foundAny ? "Status: Fast Fire Activated" : "Status: Failed";
            } else {
                bool revertedAny = false;
                // Revert Part 1
                for (auto addr : saved_addr_1) {
                    if (MemScan_SafeRevertHex(addr, s1_ON, r1_ON)) {
                        revertedAny = true;
                    }
                }
                saved_addr_1.clear();
                
                // Revert Part 2
                for (auto addr : saved_addr_2) {
                    if (MemScan_SafeRevertHex(addr, s2_ON, r2_ON)) {
                        revertedAny = true;
                    }
                }
                saved_addr_2.clear();

                status = revertedAny ? "Status: Fast Fire Deactivated" : "Status: Failed";
            }
            break;
        }

        case 4: { // Speed Timer
            const char* s1_ON = "02 2B 07 3D 02 2B 07 3D 02 2B 07 3D 00 00 00 00 9B 6C F2 41";
            const char* r1_ON = "E3 A5 90 3C E3 A5 9B 3C 02 2B 07 3D 00 00 00 00 9B 6C F2 41";

            static std::vector<uintptr_t> saved_addr_speed;

            if (enable) {
                saved_addr_speed.clear();
                bool foundAny = false;
                auto results = MemScan_SearchHex(s1_ON);
                int count = 0;
                for (auto res : results) {
                    if (MemScan_ReplaceHex(res.address, r1_ON)) {
                        saved_addr_speed.push_back(res.address);
                        foundAny = true;
                        count++;
                        if (count >= 50) break;
                    }
                }
                status = foundAny ? "Status: Speed Timer Activated" : "Status: Failed";
            } else {
                bool revertedAny = false;
                for (auto addr : saved_addr_speed) {
                    if (MemScan_SafeRevertHex(addr, s1_ON, r1_ON)) {
                        revertedAny = true;
                    }
                }
                saved_addr_speed.clear();
                status = revertedAny ? "Status: Speed Timer Deactivated" : "Status: Failed";
            }
            break;
        }
    }

    MemScan_Detach();
    return status;
}
