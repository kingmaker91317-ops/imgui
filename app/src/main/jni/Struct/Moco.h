#pragma once
#include <cstdint>
#include <chrono>
#include <cmath>
#include "Struct/lion_Class.h"

namespace Moco {

typedef bool (*ClientMarkPlayerFn)(void*, uint32_t, bool, uint8_t);
typedef void (*ClearCommonMarkFn)(void*);

inline ClientMarkPlayerFn ClientMarkPlayer = nullptr;
inline ClearCommonMarkFn  ClearCommonMark  = nullptr;

inline void Resolve() {
    if (!ClientMarkPlayer) {
        ClientMarkPlayer = (ClientMarkPlayerFn)Il2CppGetMethodOffset(
            OBFUSCATE("Assembly-CSharp.dll"),
            OBFUSCATE("COW.GamePlay"),
            OBFUSCATE("Player"),
            OBFUSCATE("ClientMarkPlayer"), 3);
    }
    if (!ClearCommonMark) {
        ClearCommonMark = (ClearCommonMarkFn)Il2CppGetMethodOffset(
            OBFUSCATE("Assembly-CSharp.dll"),
            OBFUSCATE("COW.GamePlay"),
            OBFUSCATE("Player"),
            OBFUSCATE("ClearCommonMark"), 0);
    }
}

inline uint32_t GetPlayerID(void* player) {
    using fn = uint32_t(*)(void*);
    return ((fn)m_get_player_ID)(player);
}

inline void Tick() {
    if (!Sooo || !MocoMark) return;
    if (!ClientMarkPlayer) { Resolve(); if (!ClientMarkPlayer) return; }

    static std::chrono::steady_clock::time_point lastMark =
        std::chrono::steady_clock::now() - std::chrono::seconds(3);
    auto now = std::chrono::steady_clock::now();
    auto ms  = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMark).count();
    if (ms < 1500) return;
    lastMark = now;

    void* match = Curent_Match();
    if (!match) return;
    void* local = GetLocalPlayer(match);
    if (!local) return;

    MyDictionary* dict = *(MyDictionary**)((uintptr_t)match + ListPlayer);
    if (!dict || !dict->entries) return;

    int total = dict->count;
    if (total <= 0 || total > 128) return;

    Vector3 lp = getPosition(local);
    if (!std::isfinite(lp.x) || !std::isfinite(lp.y) || !std::isfinite(lp.z)) return;

    float lim = MocoRadius;
    if (!std::isfinite(lim) || lim < 20.0f) lim = 20.0f;
    if (lim > 800.0f) lim = 800.0f;

    for (int i = 0; i < total; i++) {
        void* e = dict->entries->vector[i].value;
        if (!e || e == local) continue;
        if (get_isLocalTeam(e)) continue;
        if (get_isLocalTeam(e, false)) continue;
        if (get_IsDieing(e)) continue;
        if (GetHp(e) <= 0) continue;

        Vector3 ep = getPosition(e);
        if (!std::isfinite(ep.x) || !std::isfinite(ep.y) || !std::isfinite(ep.z)) continue;
        if (Vector3::Distance(lp, ep) > lim) continue;

        uint32_t pid = GetPlayerID(e);
        ClientMarkPlayer(local, pid, true, 1);
    }
}

inline void ClearAll() {
    if (!ClearCommonMark) { Resolve(); if (!ClearCommonMark) return; }
    void* match = Curent_Match();
    if (!match) return;
    void* local = GetLocalPlayer(match);
    if (!local) return;
    ClearCommonMark(local);
}

} // namespace Moco
