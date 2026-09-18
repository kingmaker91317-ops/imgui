#pragma once
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// MemScan - Modul Fast Memory Scan & Replace (0.1s Inject)
// Bekerja untuk sistem Root Android (menggunakan pembacaan procfs/syscall).
// Dapat juga diadaptasi untuk Linux PC.
// -----------------------------------------------------------------------

struct MemoryRegion {
    uintptr_t start;
    uintptr_t end;
    bool isReadable;
    bool isWritable;
};

// ==========================================
// Struktur Data Hasil Scan
// ==========================================
struct ScanResult {
    uintptr_t address;
    std::vector<uint8_t> originalValue;
};

// ==========================================
// Fungsi Utama Memory Scanner
// ==========================================

// 1. Inisialisasi proses target (misalnya berdasarkan package name)
bool MemScan_Attach(pid_t pid);

// 2. Scan memori berdasarkan pattern byte (contoh: "C0 3F 00 00 00 3F 00 00 80 3F 00 00")
// Fast scan menggunakan pattern matching dengan wildcard (??)
std::vector<ScanResult> MemScan_SearchPattern(const char* pattern, const char* mask);

// 3. Scan memori berdasarkan nilai spesifik (Float, Dword, Qword)
std::vector<ScanResult> MemScan_SearchFloat(float value, float tolerance = 0.001f);
std::vector<ScanResult> MemScan_SearchDword(uint32_t value);

// 4. Edit (Replace) hasil scan yang ditemukan
// Mengganti byte di address spesifik
bool MemScan_ReplaceBytes(uintptr_t address, const std::vector<uint8_t>& newBytes);
// Mengganti Float
bool MemScan_ReplaceFloat(uintptr_t address, float newValue);
// Mengganti Dword
bool MemScan_ReplaceDword(uintptr_t address, uint32_t newValue);

// -----------------------------------------------------------------------
// Helper: MemScan dengan GameGuardian format (contoh: "00 00 00 00 ?? ?? 80 3f")
// -----------------------------------------------------------------------
std::vector<ScanResult> MemScan_SearchHex(const char* hexPattern);
bool MemScan_ReplaceHex(uintptr_t address, const char* hexPattern);
bool MemScan_SafeRevertHex(uintptr_t address, const char* originalHex, const char* replacedHex);

// 5. Cleanup dan dettach
void MemScan_Detach();

// -----------------------------------------------------------------------
// Contoh Penggunaan Nanti di Menu UI:
//
// 1. User menekan tombol "Inject Magic Bullet" di Menu (Floater.java)
// 2. JNI Memanggil fungsi C++ yang memicu MemScan_SearchPattern()
// 3. Ditemukan 12 address dalam < 0.1 detik
// 4. MemScan_ReplaceBytes() langsung menimpa nilainya
// 5. Fitur aktif tanpa terdeteksi!
// -----------------------------------------------------------------------
