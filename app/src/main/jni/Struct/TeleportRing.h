#pragma once

// STROP RING = الطائرة الشراعية الحمراء
// Player field: BHJINKEDKGH (StropRing) @ 0xCA8 — dump.cs v7a
// StropRing.set_Position @ 0x790F5C0 — dump.cs v7a

#define OFFSET_PLAYER_STROPRING (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("BHJINKEDKGH"))
#define OFFSET_STROPRING_SETPOSITION (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("StropRing"), OBFUSCATE("set_Position"), 1)

typedef void (*t_StropRing_SetPosition)(void* instance, Vector3 position);
static t_StropRing_SetPosition StropRing_SetPosition = nullptr;

inline void InitStropRingAPI() {
    if (!StropRing_SetPosition && OFFSET_STROPRING_SETPOSITION) {
        StropRing_SetPosition = (t_StropRing_SetPosition)OFFSET_STROPRING_SETPOSITION;
    }
}

inline void RunTeleportRing()
{
    if (!Enable || !TeleportRing)
        return;

    InitStropRingAPI();

    void* match = Curent_Match();
    if (!match)
        return;

    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer)
        return;

    void* enemy = GetClosestEnemy();
    if (!enemy)
        return;

    void* localTF = Component_GetTransform(localPlayer);
    if (!localTF)
        return;

    Vector3 pos = getPosition(enemy);
    pos.y += TeleportRingYOffset;

    uintptr_t stropRingPtr = *(uintptr_t*)((uintptr_t)localPlayer + OFFSET_PLAYER_STROPRING);

    if (stropRingPtr != 0 && StropRing_SetPosition != nullptr) {
        StropRing_SetPosition((void*)stropRingPtr, pos);
    }

    SetPosition(localTF, pos);
}
