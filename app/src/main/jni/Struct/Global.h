#pragma once
namespace Global {
    uintptr_t U3DStr;
    uintptr_t get_Chars;
}

Global.U3DStr   = Il2CppGetMethodOffset("mscorlib.dll", "System", "String", "CreateString", 2);
Global.get_Chars = Il2CppGetMethodOffset("mscorlib.dll", "System", "String", "get_Chars", 1);

static char get_Chars(monoString* str, int index) {
    char (*func)(monoString*, int) = (char(*)(monoString*, int))getRealOffset(Global.get_Chars);
    return func(str, index);
}
