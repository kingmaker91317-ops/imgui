#pragma once
// AimKill methods ported from Aimkill-Max → lazsource logic (Il2Cpp only, HitObjectInfo struct)

#define _HitObjectInfoWp (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("FDMIEDDNCEC"))

static float TimerTakeDamageinit = 0.0f;
static float TimerTakeDamageEnd = 0.05f;

static HitObjectInfo *GetPlayerHitInfo(void *local)
{
    if (!local || !_HitObjectInfoWp) return nullptr;
    return *(HitObjectInfo **)((uintptr_t)local + _HitObjectInfoWp);
}

static void FillHitInfoDirectly(HitObjectInfo *hitInfo, void *headCollider,
                                Vector3 enemyHeadPos, Vector3 localHeadPos, Vector3 direction,
                                float dist, int baseDamage, int bodyPart = 1)
{
    if (!hitInfo || !headCollider) return;
    void *go = get_gameObject(headCollider);
    if (!go) return;

    hitInfo->HitObject = go;
    hitInfo->HitCollider = headCollider;
    hitInfo->HitLocation = enemyHeadPos;
    hitInfo->HitNormal = direction;
    hitInfo->RayDir = direction;
    hitInfo->StartPosition = localHeadPos;
    hitInfo->OrigStartPosition = localHeadPos;
    hitInfo->HitGroup = bodyPart;
    hitInfo->IgnoreHappens = false;
    hitInfo->ViewBlocked = false;
    hitInfo->SpecialHitType = 0;
    hitInfo->Distance = dist;
    hitInfo->Damage = baseDamage;
}

static bool AimkillMethodPull(void *enemy, void **outTf, Vector3 *outOriginal)
{
    if (!enemy || !outTf || !outOriginal) return false;
    if (IsVisible(enemy)) return false;

    void *tf = Component_GetTransform(enemy);
    if (!tf) return false;

    void *camera = Camera_main();
    if (!camera) return false;
    void *camTf = Component_GetTransform(camera);
    if (!camTf) return false;

    *outTf = tf;
    *outOriginal = GetPosition(tf);

    Vector3 camPos = GetPosition(camTf);
    Vector3 forward = GetForward(camTf);
    Vector3 enemyPos = *outOriginal;
    float distance = Vector3::Distance(camPos, enemyPos);

    Vector3 targetPos;
    targetPos.x = camPos.x + forward.x * distance;
    targetPos.y = camPos.y + forward.y * distance - 1.0f;
    targetPos.z = camPos.z + forward.z * distance;

    const float maxMove = 2.5f;
    float dx = targetPos.x - enemyPos.x;
    float dy = targetPos.y - enemyPos.y;
    float dz = targetPos.z - enemyPos.z;
    if (dx > maxMove) targetPos.x = enemyPos.x + maxMove;
    else if (dx < -maxMove) targetPos.x = enemyPos.x - maxMove;
    if (dy > maxMove) targetPos.y = enemyPos.y + maxMove;
    else if (dy < -maxMove) targetPos.y = enemyPos.y - maxMove;
    if (dz > maxMove) targetPos.z = enemyPos.z + maxMove;
    else if (dz < -maxMove) targetPos.z = enemyPos.z - maxMove;

    SetPosition(tf, targetPos);
    return true;
}

static bool AimkillMethodPullV2(void *enemy, void **outTf, Vector3 *outOriginal)
{
    if (!enemy || !outTf || !outOriginal) return false;
    if (!IsPullTargetValid(enemy)) return false;
    if (IsVisible(enemy)) return false;

    void *tf = Component_GetTransform(enemy);
    if (!tf) return false;

    *outTf = tf;
    *outOriginal = GetPosition(tf);
    return SilentGhostPullV2(enemy, nullptr, true);
}

static void AimkillMethodRestore(void *enemy, void *tf, const Vector3 &original)
{
    if (enemy && tf) SetPosition(tf, original);
}

static void StartEnemyHitFly(void *enemyPlayer, Vector3 *restorePos)
{
    if (!AimKillHitFly || !enemyPlayer) return;
    void *tf = Component_GetTransform(enemyPlayer);
    if (!tf) return;
    Vector3 pos = GetPosition(tf);
    pos.y += 8.0f;
    SetPosition(tf, pos);
    if (restorePos) restorePos->y = pos.y;
}

static void *EnsureDamageInfo()
{
    static void *dmgInfo = nullptr;
    if (!dmgInfo)
        dmgInfo = Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HNLIMBLIANL"));
    return dmgInfo;
}

static WeaponDynamicInfo2_o *EnsureWeaponDynamicInfo()
{
    static WeaponDynamicInfo2_o *wdi = nullptr;
    if (!wdi) {
        wdi = (WeaponDynamicInfo2_o *)Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PIAEKELILCJ"));
        if (wdi) {
            memset((void *)((uintptr_t)wdi + sizeof(void *) * 2), 0, sizeof(WeaponDynamicInfo2_o) - sizeof(void *) * 2);
            wdi->DynamicDamageRatioBody = 1.0f;
            wdi->DynamicDamageRatioHead = 1.0f;
            wdi->DynamicDamageRatioLimb = 1.0f;
            wdi->ShieldDamageRatioWeapon = 1.0f;
            wdi->ShieldDamageRatioBody = 1.0f;
            wdi->ShieldDamageRatioHead = 1.0f;
            wdi->ShieldDamageRatioLimb = 1.0f;
        }
    }
    return wdi;
}

static void FillDamageInfoFields(void *dmgInfo, IHAAMHPPLMG pid, int colliderType, int baseDamage,
                                 void *weapon, Vector3 firePos, Vector3 hitPos, int weaponDataId)
{
    if (!dmgInfo) return;
    if (Dmg_PlayerID) *(IHAAMHPPLMG *)((uintptr_t)dmgInfo + Dmg_PlayerID) = pid;
    if (Dmg_ColliderType) *(int *)((uintptr_t)dmgInfo + Dmg_ColliderType) = colliderType;
    if (Dmg_BaseDamage) *(int *)((uintptr_t)dmgInfo + Dmg_BaseDamage) = baseDamage;
    if (Dmg_WeaponOnHand) *(void **)((uintptr_t)dmgInfo + Dmg_WeaponOnHand) = weapon;
    if (Dmg_FirePos) *(Vector3 *)((uintptr_t)dmgInfo + Dmg_FirePos) = firePos;
    if (Dmg_HitPos) *(Vector3 *)((uintptr_t)dmgInfo + Dmg_HitPos) = hitPos;
    if (Dmg_WeaponDataId) *(int *)((uintptr_t)dmgInfo + Dmg_WeaponDataId) = weaponDataId;
}

static void *GetClosestEnemy360(void *localPlayer, void *match)
{
    if (!localPlayer || !match) return nullptr;
    MyDictionary *dict = *(MyDictionary **)((uintptr_t)match + ListPlayer);
    if (!dict || !dict->entries) return nullptr;

    void *best = nullptr;
    float bestDist = 99999.0f;
    int total = dict->count;
    if (total > 64) total = 64;

    for (int i = 0; i < total; i++) {
        void *p = dict->entries->vector[i].value;
        if (!p || p == localPlayer) continue;
        if (get_isLocalTeam(p)) continue;
        if (IgnoreKnocked && get_IsDieing(p)) continue;
        if (get_IsDieing(p)) continue;
        if (!get_MaxHP(p)) continue;
        if (!IsInDistance(localPlayer, p)) continue;

        float d = Vector3::Distance(getPosition(localPlayer), getPosition(p));
        if (d < Aimdis && d < bestDist) {
            bestDist = d;
            best = p;
        }
    }
    return best;
}

// [3] AimKill / AimKill360 — TakeDamage path
void StartAimKillV2(void *enemy)
{
    if (!(AimKill || AimKill360)) return;
    if (!enemy) return;

    void *match = Curent_Match();
    if (!match) return;
    void *local = GetLocalPlayer(match);
    if (!local || local == enemy) return;
    if (get_IsDieing(local) || get_IsDieing(enemy)) return;

    HitObjectInfo stackHit = {};
    HitObjectInfo *hitInfo = GetPlayerHitInfo(local);
    if (!hitInfo) hitInfo = &stackHit;

    void *headCollider = Player_GetHeadCollider(enemy);
    if (!headCollider) return;
    void *headGO = get_gameObject(headCollider);
    if (!headGO) return;

    Vector3 localHead = GetHeadPosition(local);
    Vector3 enemyHead = GetHeadPosition(enemy);
    Vector3 dir = Vector3::Normalized(enemyHead - localHead);
    float dist = Vector3::Distance(localHead, enemyHead);

    FillHitInfoDirectly(hitInfo, headCollider, enemyHead, localHead, dir, dist, 999, 1);

    void *weapon = GetWeaponOnHand(local);
    if (!weapon) return;
    if (!isEnemyInRangeWeapon(local, enemy, weapon)) return;

    void *enemyTf = nullptr;
    Vector3 originalPos = Vector3(0, 0, 0);
    bool wasPulled = AimkillMethodPull(enemy, &enemyTf, &originalPos);
    bool visible = IsVisible(enemy);
    if (!visible && !wasPulled) return;

    if (!get_IsFiring(local)) {
        StartFiring2(weapon);
        StartFiring_PN(local, weapon);
        StartWholeBodyFiring(local, weapon);
    }

    int baseDamage = GetDamage(weapon);
    if (baseDamage <= 0) baseDamage = 99;
    int weaponID = GetWeaponID(weapon);

    void *dmgInfo = EnsureDamageInfo();
    if (dmgInfo)
        memset((void *)((uintptr_t)dmgInfo + sizeof(void *) * 2), 0, 64);

    WeaponDynamicInfo2_o *wdi = EnsureWeaponDynamicInfo();
    auto playerID = GetplayerID(local);
    FillDamageInfoFields(dmgInfo, playerID, 1, baseDamage, weapon, localHead, enemyHead, (int)GetWeaponDataId(weapon));

    void *params = LCLHHHKFCFP(weapon, GKHECDLGAJA(local, hitInfo), headCollider, false, nullptr);

    float now = get_time();
    if (now >= TimerTakeDamageinit) {
        TimerTakeDamageinit = now + TimerTakeDamageEnd;

        if (params && dmgInfo && wdi) {
            Call_Player_TakeDamage(enemy, baseDamage, playerID, dmgInfo, weaponID,
                                   localHead, enemyHead, params, wdi, 0);
        }

        if (old_KOODEKEKFEK1)
            old_KOODEKEKFEK1(weapon, hitInfo);

        if (AimKillHitFly) StartEnemyHitFly(enemy, &originalPos);
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        StopFiring2(weapon);
        StopFire_PN(local, weapon);
        Syns_SwapWeapon_Impl(local, weapon);
    }
}

// [4] AimKill Send — WeaponFire path
void StartAimKillSend(void *ClosestEnemy)
{
    if (!AimKillSend) return;
    if (!ClosestEnemy || get_IsDieing(ClosestEnemy) || GetHp(ClosestEnemy) <= 0) return;

    void *match = Curent_Match();
    if (!match) return;
    void *localPlayer = GetLocalPlayer(match);
    if (!localPlayer || localPlayer == ClosestEnemy || get_IsDieing(localPlayer)) return;

    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand) return;
    if (!old_KOODEKEKFEK1) return;

    void *enemyTf = nullptr;
    Vector3 originalPos = Vector3(0, 0, 0);
    bool wasPulled = AimkillMethodPull(ClosestEnemy, &enemyTf, &originalPos);
    bool visible = IsVisible(ClosestEnemy);
    if (!visible && !wasPulled) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    void *headColliderEnemy = Player_GetHeadCollider(ClosestEnemy);
    if (!headColliderEnemy) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    HitObjectInfo stackHit = {};
    HitObjectInfo *hitInfo = GetPlayerHitInfo(localPlayer);
    if (!hitInfo) hitInfo = &stackHit;

    Vector3 firePos = GetHeadPosition(localPlayer);
    Vector3 hitPos = GetHeadPosition(ClosestEnemy);
    Vector3 dir = Vector3::Normalized(hitPos - firePos);
    float dist = Vector3::Distance(firePos, hitPos);

    FillHitInfoDirectly(hitInfo, headColliderEnemy, hitPos, firePos, dir, dist, 999, 1);
    GKHECDLGAJA(localPlayer, hitInfo);

    if (!get_IsFiring(localPlayer))
        StartFiring_PN(localPlayer, weaponOnHand);

    if (ClosestEnemy && !get_IsDieing(ClosestEnemy) && GetHp(ClosestEnemy) > 0)
        old_KOODEKEKFEK1(weaponOnHand, hitInfo);

    if (AimKillHitFly) StartEnemyHitFly(ClosestEnemy, &originalPos);
    AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
}

// [5] Dual-Path Kill (WeaponFire + TakeDamage loop)
void StartAimKillCHM9M9(void *ClosestEnemy)
{
    if (!AimKillCHM9M9) return;
    if (!ClosestEnemy || get_IsDieing(ClosestEnemy) || GetHp(ClosestEnemy) <= 0) return;

    void *match = Curent_Match();
    if (!match) return;
    void *localPlayer = GetLocalPlayer(match);
    if (!localPlayer || localPlayer == ClosestEnemy || get_IsDieing(localPlayer)) return;

    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand) return;
    if (!isEnemyInRangeWeapon(localPlayer, ClosestEnemy, weaponOnHand)) return;
    if (!old_KOODEKEKFEK1) return;

    void *enemyTf = nullptr;
    Vector3 originalPos = Vector3(0, 0, 0);
    bool wasPulled = AimkillMethodPull(ClosestEnemy, &enemyTf, &originalPos);
    bool visible = IsVisible(ClosestEnemy);
    if (!visible && !wasPulled) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    void *headColliderEnemy = Player_GetHeadCollider(ClosestEnemy);
    if (!headColliderEnemy) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    HitObjectInfo stackHit = {};
    HitObjectInfo *hitInfo = GetPlayerHitInfo(localPlayer);
    if (!hitInfo) hitInfo = &stackHit;

    Vector3 firePos = GetHeadPosition(localPlayer);
    Vector3 hitPos = GetHeadPosition(ClosestEnemy);
    Vector3 dir = Vector3::Normalized(hitPos - firePos);
    float dist = Vector3::Distance(firePos, hitPos);

    FillHitInfoDirectly(hitInfo, headColliderEnemy, hitPos, firePos, dir, dist, 999, 1);
    if (!GKHECDLGAJA(localPlayer, hitInfo)) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    if (!get_IsFiring(localPlayer)) {
        StartFiring2(weaponOnHand);
        StartFiring_PN(localPlayer, weaponOnHand);
        StartWholeBodyFiring(localPlayer, weaponOnHand);
    }

    int baseDamage = GetDamage(weaponOnHand);
    if (baseDamage <= 0) baseDamage = 99;
    int weaponID = GetWeaponID(weaponOnHand);

    void *dmgInfo = EnsureDamageInfo();
    WeaponDynamicInfo2_o *wdi = EnsureWeaponDynamicInfo();
    auto playerID = GetplayerID(localPlayer);
    FillDamageInfoFields(dmgInfo, playerID, 1, baseDamage, weaponOnHand, firePos, hitPos, (int)GetWeaponDataId(weaponOnHand));

    void *enemyTransform = enemyTf ? enemyTf : Component_GetTransform(ClosestEnemy);
    Vector3 bodyPos = enemyTransform ? GetPosition(enemyTransform) : hitPos;

    int superDamage = 999;
    for (int i = 0; i < 25; i++) {
        if (!ClosestEnemy || get_IsDieing(ClosestEnemy) || GetHp(ClosestEnemy) <= 0) break;

        int partIdx = i % 4;
        Vector3 targetPos = hitPos;
        if (partIdx == 1 || partIdx == 3) {
            targetPos = bodyPos;
            targetPos.y += (partIdx == 1) ? 0.15f : -0.1f;
        } else if (partIdx == 2) {
            targetPos = bodyPos;
            targetPos.y -= 0.4f;
        }

        targetPos.x += ((float)(rand() % 100) - 50.0f) * 0.001f;
        targetPos.y += ((float)(rand() % 100) - 50.0f) * 0.001f;
        targetPos.z += ((float)(rand() % 100) - 50.0f) * 0.001f;

        Vector3 fireDir = Vector3::Normalized(targetPos - firePos);
        FillHitInfoDirectly(hitInfo, headColliderEnemy, targetPos, firePos, fireDir, dist, superDamage, partIdx);
        old_KOODEKEKFEK1(weaponOnHand, hitInfo);

        if (ClosestEnemy && !get_IsDieing(ClosestEnemy) && GetHp(ClosestEnemy) > 0) {
            void *params = LCLHHHKFCFP(weaponOnHand, GKHECDLGAJA(localPlayer, hitInfo), headColliderEnemy, false, nullptr);
            if (dmgInfo && wdi && params) {
                FillDamageInfoFields(dmgInfo, playerID, partIdx, superDamage, weaponOnHand, firePos, targetPos, (int)GetWeaponDataId(weaponOnHand));
                if (wdi) {
                    wdi->DynamicDamageRatioHead = (partIdx == 0) ? 1.0f : 0.8f;
                    wdi->DynamicDamageRatioBody = (partIdx == 1 || partIdx == 3) ? 1.0f : 0.8f;
                    wdi->DynamicDamageRatioLimb = (partIdx == 2) ? 1.0f : 0.8f;
                }
                Call_Player_TakeDamage(ClosestEnemy, superDamage, playerID, dmgInfo, weaponID, firePos, targetPos, params, wdi, 0);
            }
        }
        Syns_SwapWeapon_Impl(localPlayer, weaponOnHand);
    }

    if (AimKillHitFly) StartEnemyHitFly(ClosestEnemy, &originalPos);
    AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
}

// [6] Safe Aimkill — rate-limited WeaponFire
static const int kSafeMaxPacketsPerEnemy = 15;
static const int kSafeBurstPacketMax = 8;
static const int kSafeMinPacketGapMs = 20;
static const int kSafeMaxPacketGapMs = 80;
static const int kSafeBurstResetMs = 2000;

struct SafeAimkillTracker {
    void *trackedEnemy = nullptr;
    int packetsToEnemy = 0;
    int burstPackets = 0;
    long long nextRequiredGapMs = 200;
    std::chrono::steady_clock::time_point lastPacketAt{};
    std::chrono::steady_clock::time_point burstWindowStart{};
};
static SafeAimkillTracker g_safeAimkill;

static long long SafeAimkillNextGapMs() {
    return kSafeMinPacketGapMs + (rand() % (kSafeMaxPacketGapMs - kSafeMinPacketGapMs + 1));
}

static void SafeAimkillResetBurstWindow(std::chrono::steady_clock::time_point now) {
    g_safeAimkill.burstPackets = 0;
    g_safeAimkill.burstWindowStart = now;
}

static bool SafeAimkillCanSendPacket(void *enemy) {
    auto now = std::chrono::steady_clock::now();
    if (g_safeAimkill.trackedEnemy != enemy) {
        g_safeAimkill.trackedEnemy = enemy;
        g_safeAimkill.packetsToEnemy = 0;
        SafeAimkillResetBurstWindow(now);
    }
    if (g_safeAimkill.packetsToEnemy >= kSafeMaxPacketsPerEnemy) return false;

    if (g_safeAimkill.burstWindowStart.time_since_epoch().count() == 0)
        SafeAimkillResetBurstWindow(now);
    else {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - g_safeAimkill.burstWindowStart).count();
        if (elapsed >= kSafeBurstResetMs) SafeAimkillResetBurstWindow(now);
    }
    if (g_safeAimkill.burstPackets >= kSafeBurstPacketMax) return false;

    if (g_safeAimkill.lastPacketAt.time_since_epoch().count() != 0) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - g_safeAimkill.lastPacketAt).count();
        if (elapsed < g_safeAimkill.nextRequiredGapMs) return false;
    }
    return true;
}

static void SafeAimkillRecordPacketSent() {
    auto now = std::chrono::steady_clock::now();
    if (g_safeAimkill.burstWindowStart.time_since_epoch().count() == 0)
        SafeAimkillResetBurstWindow(now);
    g_safeAimkill.packetsToEnemy++;
    g_safeAimkill.burstPackets++;
    g_safeAimkill.lastPacketAt = now;
    g_safeAimkill.nextRequiredGapMs = SafeAimkillNextGapMs();
}

void StartSafeAimkill(void *enemy)
{
    if (!SafeAimkill) return;
    if (!enemy || get_IsDieing(enemy) || GetHp(enemy) <= 0) return;
    if (!SafeAimkillCanSendPacket(enemy)) return;

    void *match = Curent_Match();
    if (!match) return;
    void *localPlayer = GetLocalPlayer(match);
    if (!localPlayer || localPlayer == enemy || get_IsDieing(localPlayer)) return;

    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand || !isEnemyInRangeWeapon(localPlayer, enemy, weaponOnHand)) return;
    if (!old_KOODEKEKFEK1) return;

    static bool s_inSafeAimkill = false;
    if (s_inSafeAimkill) return;
    s_inSafeAimkill = true;

    void *enemyTf = nullptr;
    Vector3 originalPos = Vector3(0, 0, 0);
    bool wasPulled = AimkillMethodPull(enemy, &enemyTf, &originalPos);
    bool visible = IsVisible(enemy);
    if (!visible && !wasPulled) {
        s_inSafeAimkill = false;
        return;
    }

    void *headColliderEnemy = Player_GetHeadCollider(enemy);
    if (!headColliderEnemy) {
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inSafeAimkill = false;
        return;
    }

    HitObjectInfo stackHit = {};
    HitObjectInfo *hitInfo = GetPlayerHitInfo(localPlayer);
    if (!hitInfo) hitInfo = &stackHit;

    int baseDamage = GetDamage(weaponOnHand);
    if (baseDamage <= 0) baseDamage = 99;

    Vector3 firePos = GetHeadPosition(localPlayer);
    Vector3 hitPos = GetHeadPosition(enemy);
    Vector3 direction = Vector3::Normalized(hitPos - firePos);
    float dist = Vector3::Distance(firePos, hitPos);

    FillHitInfoDirectly(hitInfo, headColliderEnemy, hitPos, firePos, direction, dist, baseDamage, 1);
    if (!GKHECDLGAJA(localPlayer, hitInfo)) {
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inSafeAimkill = false;
        return;
    }

    if (!get_IsFiring(localPlayer))
        StartFiring_PN(localPlayer, weaponOnHand);

    bool fired = false;
    if (enemy && !get_IsDieing(enemy) && GetHp(enemy) > 0) {
        old_KOODEKEKFEK1(weaponOnHand, hitInfo);
        fired = true;
    }
    if (fired) SafeAimkillRecordPacketSent();

    StopFire_PN(localPlayer, weaponOnHand);
    Syns_SwapWeapon_Impl(localPlayer, weaponOnHand);
    AimkillMethodRestore(enemy, enemyTf, originalPos);
    s_inSafeAimkill = false;
}

// [7] Auto Kill V2 — Safe Aimkill + SilentGhostPullV2 (cover kill)
static const int kAutoKillV2MaxPacketsPerEnemy = 15;
static const int kAutoKillV2BurstPacketMax = 8;
static const int kAutoKillV2MinPacketGapMs = 20;
static const int kAutoKillV2MaxPacketGapMs = 80;
static const int kAutoKillV2BurstResetMs = 2000;

struct AutoKillV2Tracker {
    void *trackedEnemy = nullptr;
    int packetsToEnemy = 0;
    int burstPackets = 0;
    long long nextRequiredGapMs = 200;
    std::chrono::steady_clock::time_point lastPacketAt{};
    std::chrono::steady_clock::time_point burstWindowStart{};
};
static AutoKillV2Tracker g_autoKillV2;

static long long AutoKillV2NextGapMs() {
    return kAutoKillV2MinPacketGapMs + (rand() % (kAutoKillV2MaxPacketGapMs - kAutoKillV2MinPacketGapMs + 1));
}

static void AutoKillV2ResetBurstWindow(std::chrono::steady_clock::time_point now) {
    g_autoKillV2.burstPackets = 0;
    g_autoKillV2.burstWindowStart = now;
}

static bool AutoKillV2CanSendPacket(void *enemy) {
    auto now = std::chrono::steady_clock::now();
    if (g_autoKillV2.trackedEnemy != enemy) {
        g_autoKillV2.trackedEnemy = enemy;
        g_autoKillV2.packetsToEnemy = 0;
        AutoKillV2ResetBurstWindow(now);
    }
    if (g_autoKillV2.packetsToEnemy >= kAutoKillV2MaxPacketsPerEnemy) return false;

    if (g_autoKillV2.burstWindowStart.time_since_epoch().count() == 0)
        AutoKillV2ResetBurstWindow(now);
    else {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - g_autoKillV2.burstWindowStart).count();
        if (elapsed >= kAutoKillV2BurstResetMs) AutoKillV2ResetBurstWindow(now);
    }
    if (g_autoKillV2.burstPackets >= kAutoKillV2BurstPacketMax) return false;

    if (g_autoKillV2.lastPacketAt.time_since_epoch().count() != 0) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - g_autoKillV2.lastPacketAt).count();
        if (elapsed < g_autoKillV2.nextRequiredGapMs) return false;
    }
    return true;
}

static void AutoKillV2RecordPacketSent() {
    auto now = std::chrono::steady_clock::now();
    if (g_autoKillV2.burstWindowStart.time_since_epoch().count() == 0)
        AutoKillV2ResetBurstWindow(now);
    g_autoKillV2.packetsToEnemy++;
    g_autoKillV2.burstPackets++;
    g_autoKillV2.lastPacketAt = now;
    g_autoKillV2.nextRequiredGapMs = AutoKillV2NextGapMs();
}

void StartAutoKillV2(void *enemy)
{
    if (!AutoKillV2) return;
    if (!enemy || !IsPullTargetValid(enemy)) return;
    if (get_IsDieing(enemy) || GetHp(enemy) <= 0) return;
    if (!AutoKillV2CanSendPacket(enemy)) return;

    void *match = Curent_Match();
    if (!match) return;
    void *localPlayer = GetLocalPlayer(match);
    if (!localPlayer || localPlayer == enemy || get_IsDieing(localPlayer)) return;

    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand || !isEnemyInRangeWeapon(localPlayer, enemy, weaponOnHand)) return;
    if (!old_KOODEKEKFEK1) return;

    static bool s_inAutoKillV2 = false;
    if (s_inAutoKillV2) return;
    s_inAutoKillV2 = true;

    void *enemyTf = nullptr;
    Vector3 originalPos = Vector3(0, 0, 0);
    bool wasPulled = AimkillMethodPullV2(enemy, &enemyTf, &originalPos);
    bool visible = IsVisible(enemy);
    if (!visible && !wasPulled) {
        s_inAutoKillV2 = false;
        return;
    }

    void *headColliderEnemy = Player_GetHeadCollider(enemy);
    if (!headColliderEnemy) {
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inAutoKillV2 = false;
        return;
    }

    HitObjectInfo stackHit = {};
    HitObjectInfo *hitInfo = GetPlayerHitInfo(localPlayer);
    if (!hitInfo) hitInfo = &stackHit;

    int baseDamage = GetDamage(weaponOnHand);
    if (baseDamage <= 0) baseDamage = 99;

    Vector3 firePos = GetHeadPosition(localPlayer);
    Vector3 hitPos = GetHeadPosition(enemy);
    Vector3 direction = Vector3::Normalized(hitPos - firePos);
    float dist = Vector3::Distance(firePos, hitPos);

    FillHitInfoDirectly(hitInfo, headColliderEnemy, hitPos, firePos, direction, dist, baseDamage, 1);
    if (!GKHECDLGAJA(localPlayer, hitInfo)) {
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inAutoKillV2 = false;
        return;
    }

    if (!get_IsFiring(localPlayer))
        StartFiring_PN(localPlayer, weaponOnHand);

    bool fired = false;
    if (enemy && !get_IsDieing(enemy) && GetHp(enemy) > 0) {
        old_KOODEKEKFEK1(weaponOnHand, hitInfo);
        fired = true;
    }
    if (fired) AutoKillV2RecordPacketSent();

    StopFire_PN(localPlayer, weaponOnHand);
    Syns_SwapWeapon_Impl(localPlayer, weaponOnHand);
    AimkillMethodRestore(enemy, enemyTf, originalPos);
    s_inAutoKillV2 = false;
}

// Dispatcher — call from LateUpdate with closest / 360 target
static void RunAimKillMethods(void *localPlayer, void *closestEnemy, void *match)
{
    if (!Enable || !localPlayer) return;

    void *target = closestEnemy;
    if (AimKill360) {
        void *t360 = GetClosestEnemy360(localPlayer, match);
        if (t360) target = t360;
    }

    if (!target) return;

    if (AimKill || AimKill360)
        StartAimKillV2(target);
    if (AimKillSend)
        StartAimKillSend(target);
    if (SafeAimkill)
        StartSafeAimkill(target);
    if (AutoKillV2)
        StartAutoKillV2(target);
    if (AimKillCHM9M9)
        StartAimKillCHM9M9(target);
}

