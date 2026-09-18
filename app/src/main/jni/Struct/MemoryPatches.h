#pragma once
#include <string>

// Menerapkan memory patch berdasarkan ID (contoh: 1 = Camera Left)
// Mengembalikan string status seperti "Success: 12 replaced", "Failed: Target not found", dll.
std::string ApplyMemoryPatch(int patchId, bool enable);
