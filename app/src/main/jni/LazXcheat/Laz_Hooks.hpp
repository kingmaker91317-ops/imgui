#pragma once
enum Type {
    TYPE_DWORD,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_WORD,
    TYPE_BYTE,
    TYPE_QWORD,
};

struct Maps_t {
    uintptr_t start, end;
	Type type;
    struct Maps_t *next;
};

#define SIZE sizeof(struct Maps_t)

enum RegionType {
    ALL,
    JAVA_HEAP,
    C_HEAP,
    C_ALLOC,
    C_DATA,
    C_BSS,
    PPSSPP,
    ANONYMOUS,
    JAVA,
    STACK,
    ASHMEM,
    VIDEO,
    OTHER,
    BAD,
    CODE_APP,
    CODE_SYS
};

namespace kFox 
{

	const char *GetPackageName();
	

	extern Maps_t* GetResult();

	extern void ClearResult();

	extern void SetMaxResult(int max_result);

	extern int SetSearchRange(RegionType type);
	

    extern void MemorySearch(char* value, Type type);

	extern void MemoryOffset(char *value, long int offset, Type type);

	extern void MemoryWrite(char *value, long int offset, Type type);

	extern void WriteValues(uintptr_t address, void *value, ssize_t size);

	extern long ReadValues(uintptr_t address, void *buffer, ssize_t size);
}

