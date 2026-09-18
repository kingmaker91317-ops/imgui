#ifndef MAIN_H
#define MAIN_H

#include <map>
#include <string>
#include <Struct/tools.hpp>

struct cfg {
    bool aimbot;
    int aim_type = 0;
    int aim_target = 1;
    struct _esp {
        bool Box;
        bool Line = true;
        bool Health = true;
        bool Infos;
        bool LineRgb;
        bool Hexagono;
        bool Distancia;
        bool Skeleton;
        bool Grenade;
        bool IsName;
        bool Path;       
        bool Esp360;
        bool Target;
    }ESP;
}inline Config;

inline std::map < std::string, void*> _methods;
inline std::map < std::string, size_t > _fields;

template<typename T>
inline T getFieldValue(void *instance,ulong offset) {
    return *(T*)((uintptr_t)instance + offset);
}

template<typename T>
inline T setFieldValue(void *instance,ulong offset, T value) {
    *(T*)((uintptr_t)instance + offset) = value;
}

void menu();
void *getRealAddr(ulong offset);

#endif
