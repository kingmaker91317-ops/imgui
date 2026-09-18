#pragma once 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <Il2Cpp.h>
#include <Tools.h>
#include <Vector3.hpp>
#include <Color.h>
#include <Struct/main.h>
#include "obfuscate.h"
#include "Unity/Unity.h"
#include "lion_Class.h"
#include "Rect.h"
#include <chrono>
#include <cmath>
inline static int g_GlHeight, g_GlWidth;
#include <KittyMemory/MemoryPatch.h>
#include "Bools.h"
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>
bool SpeedHack = false;

std::vector<std::string> Logs;


void LOGS(const char* fmt, ...)
{
    char buffer[512];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    Logs.push_back(buffer);

    if (Logs.size() > 200)
        Logs.erase(Logs.begin());
}


enum BoneID {
    B_Head = 0, B_Neck, B_Hip,
    B_LShoulder, B_RShoulder, B_LElbow, B_RElbow, B_LHand, B_RHand,
    B_LKnee, B_RKnee, B_LFoot, B_RFoot, B_Root,
    BONE_COUNT
};

uintptr_t gBoneOffsets[BONE_COUNT];
void InitBoneOffsets()
{
    gBoneOffsets[B_Head] = m_HeadNode;
    gBoneOffsets[B_Neck] = m_Neck;
    gBoneOffsets[B_Hip] = m_HipNode;
    gBoneOffsets[B_LShoulder] = m_LeftShoulder;
    gBoneOffsets[B_RShoulder] = m_RightShoulder;
    gBoneOffsets[B_LElbow] = m_LeftElbow;
    gBoneOffsets[B_RElbow] = m_RightElbow;
    gBoneOffsets[B_LHand] = m_LeftHand;
    gBoneOffsets[B_RHand] = m_RightHand;
    gBoneOffsets[B_LKnee] = m_LeftKnee;
    gBoneOffsets[B_RKnee] = m_RightKnee;
    gBoneOffsets[B_LFoot] = m_LeftFoot;
    gBoneOffsets[B_RFoot] = m_RightFoot;
    gBoneOffsets[B_Root] = m_Root;
}



bool EspSkeleton = false; 



float CarDropDistance = 4.0f;



typedef char PACKAGENAME;

//initHook Config
bool HooksInitialized = false;



//Memory Functions
bool Wallhack   = false;
bool Flyrun     = false;

MemoryPatch wall;
MemoryPatch fly;


uintptr_t unity_base   = 0;


void InitPatches() {

    // == libunity PATCH OFFSETS ==
    wall = MemoryPatch::createWithHex(
        unity_base + 0x0,
        "00 00 00 00 00 00 00 00"
    );

    fly = MemoryPatch::createWithHex(
        unity_base + 0x3AA680,
        "AC C5 A9 3F 10 B5 8A B0"
    );
}

void UpdatePatches() {

    // ===== Wallhack =====
    if (Wallhack)
        wall.Modify();
    else
        wall.Restore();

    // ===== Flyrun =====
    if (Flyrun)
        fly.Modify();
    else
        fly.Restore();

}





void Bypass400Internal()
{
    constexpr uintptr_t ROOT_OFFSET     = 0xAA0D678;
    constexpr uint32_t  STATE_CODE_ON   = 0x0001007B;
    constexpr uint32_t  STATE_CODE_OFF  = 0x0002007C;
    constexpr uint32_t  STATE_FLAG_ON   = 0x00000001;
    constexpr uint32_t  STATE_FLAG_OFF  = 0x0000000E;

    if (!Bypass400)
        return;

    uintptr_t root = *(uintptr_t*)(il2cpp_base + ROOT_OFFSET);
    if (!root)
        return;

    uintptr_t ptrA = *(uintptr_t*)(root + 0x20);
    if (!ptrA)
        return;

    uintptr_t ptrB = *(uintptr_t*)(ptrA + 0xC0);
    if (!ptrB)
        return;

    uintptr_t tagged = *(uintptr_t*)(ptrB + 0x10);
    if (!tagged)
        return;


    if (tagged & 1ULL)
    {
        tagged = *(uintptr_t*)(ptrB + 0x10);
        if (!tagged)
            return;
    }

    uintptr_t holderSlot = *(uintptr_t*)(tagged + 0xB8);
    if (!holderSlot)
        return;

    uintptr_t holder = *(uintptr_t*)holderSlot;
    if (!holder)
        return;

    uintptr_t target = *(uintptr_t*)(holder + 0x18);
    if (!target)
        return;

    *(uint32_t*)(target + 0x10) =
        Bypass400 ? STATE_CODE_ON : STATE_CODE_OFF;

    *(uint32_t*)(target + 0x14) =
        Bypass400 ? STATE_FLAG_ON : STATE_FLAG_OFF;
}


static bool undergroundHasBaseY = false;
static float undergroundBaseY = 0.0f;
float UndergroundDepth = 1.0f;

static bool tpWallHasBaseZ = false;
static float tpWallBaseZ = 0.0f;



struct sColor {
        
        float line[4] = {45 / 255.0f, 180 / 255.0f, 45 / 255.0f, 255 / 255.0f};
        float box[4] = {45 / 255.0f, 180 / 255.0f, 45 / 255.0f, 255 / 255.0f};
        
    };
    
    sColor Color;
    template <typename T>
   // struct UnityArray {
    void* klass;
    void* monitor;
    void* bounds;
    int max_length;
 //   T vector[64]; 
//};

struct Vector2 {
    float x, y;
};

//struct DictionaryEntry {
    int hashCode;
    int next;
    void* key;
    void* value;
//};

//struct MyDictionary {
 //   void* klass;
 //   void* monitor;
    void* buckets;
    UnityArray<DictionaryEntry>* entries;
    int count;
//};

bool isOutsideScreen(ImVec2 pos, ImVec2 screen) {
    if (pos.y < 0) {
        return true;
    }
    if (pos.x > screen.x) {
        return true;
    }
    if (pos.y > screen.y) {
        return true;
    }
    return pos.x < 0;
}

ImVec2 pushToScreenBorder(ImVec2 Pos, ImVec2 screen, int offset) {
    int x = (int) Pos.x;
    int y = (int) Pos.y;
    
    if (Pos.y < 0) {
        y = -offset;
    }
    
    if (Pos.x > screen.x) {
        x = (int) screen.x + offset;
    }
    
    if (Pos.y > screen.y) {
        y = (int) screen.y + offset;
    }
    
    if (Pos.x < 0) {
        x = -offset;
    }
    return ImVec2(x, y);
}

static float tmAlpha = 127 / 255.f;

void DrawCircleHealth(ImVec2 position, int health, int max_health, float radius) {
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(45, 180, 45, 255);
    if (health <= (max_health * 0.6)) {
        healthColor = IM_COL32(180, 180, 45, 255);
    }
    if (health < (max_health * 0.3)) {
        healthColor = IM_COL32(180, 45, 45, 255);
    }
    ImGui::GetForegroundDrawList()->PathArcTo(position, radius, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, 4);
}



void drawText2(int x, int y, long color, const char *str, float size) {
        ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x, y), color, str);
    }


void DrawRectFilled(int x, int y, int w, int h, ImColor color) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h),
                                               color, 0, 0);
}


void DrawRectFilledHealth(int x, int y, int w, int h, ImVec4 color) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h),
                                               ImGui::ColorConvertFloat4ToU32(color), 0, 0);
}


void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int T) {
    ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3),
                                                   color);
}


bool IsInDistance(void* localPlayer, void* player, float maxDistance = 114.0f) {

    if (!Enable) return false;

    if (!localPlayer || !player)
        return false;

    Vector3 myPos = getPosition(localPlayer);
    Vector3 enemyPos = getPosition(player);

    return Vector3::Distance(myPos, enemyPos) <= maxDistance;
}


void DrawHealths(Rect box, float entityHealth, float maxHealth, int TeamID, const char* name, long color) {
    float x = box.x - (140 - box.w) / 2;
    float y = box.y;
    char dis[20];
    char TeamText[20];
    sprintf(TeamText, "%d", (int)TeamID);
    ImVec4 HPColor = ImVec4{1, 1, 0, 127 / 255.f};

    if (entityHealth < maxHealth) {
        float healthPercentage = entityHealth / maxHealth;

        if (healthPercentage < 0.3f) {
            HPColor = ImVec4{0.5f, 0.0f, 0.0f, 127 / 255.f};
        } else if (healthPercentage < 0.6f) {
            HPColor = ImVec4{1, 0, 0, 127 / 255.f};
        }
    }
    tmAlpha = 100.f / 255.f;
    DrawRectFilled(x - strlen(name), y - 41, 120 + strlen(name) * 2, 20, color);
    tmAlpha = 255.f / 255.f;
    DrawRectFilled(x - strlen(name), box.y - 41, 25, 20, color);
    if (strlen(TeamText) < 2) {
        drawText2(x + 6 - strlen(name), box.y - 42, ImColor(255,255,255),
                       TeamText, 18.943);
    } else {
        drawText2(x - strlen(name), box.y - 42, ImColor(255,255,255),
                       TeamText, 18.943);
    }
    drawText2(x + 28 - strlen(name), y - 43,
                   ImColor(255,255,255), name, 18.943);
    float maxWidth = 120;
    float healthBarWidth = entityHealth * maxWidth / maxHealth;
    DrawRectFilledHealth(x - maxWidth / 2, y - 18, healthBarWidth, 8, HPColor);
    drawText2(x + 125 + strlen(name), y - 43, ImColor(255,255,255), dis,18.943);
    DrawTriangle(box.x + box.w / 2 - 10, y - 8, box.x + box.w / 2 + 15 - 10, y - 8,
                 box.x + box.w / 2 - 2, y, ImColor(255,255,255), 1);
}

bool IsVisible(void * player){
    if(player != NULL) {
        void *hitObj = NULL;
        

        
        Vector3 cameraLocation = Transform_GetPosition(Component_GetTransform(Camera_main()));
        Vector3 headLocation = Transform_GetPosition(Component_GetTransform(Player_GetHeadCollider(player)));
            return !Physics_Raycast(cameraLocation, headLocation, 12, &hitObj);
    }
    return false;
}


void *GetClosestEnemy() {
    float shortestDistance = 9999;
    void* closestEnemy = NULL;   
    void* get_MatchGame = Curent_Match();
    void* LocalPlayer = GetLocalPlayer(get_MatchGame);
    if (LocalPlayer != NULL && get_MatchGame != NULL && Enable) {
        MyDictionary* dict = *(MyDictionary**)((uintptr_t)get_MatchGame + ListPlayer);
        if (dict != nullptr && dict->entries != nullptr) {
            void* camera = Camera_main();
            int total = dict->count;
            for (int u = 0; u < total; u++) {
                void* Player = dict->entries->vector[u].value;       
                if (Player != NULL && Player != LocalPlayer && !get_isLocalTeam(Player) && !get_IsDieing(Player) && get_isVisible(Player) && get_MaxHP(Player)) {    
                    Vector3 PlayerPos = getPosition(Player);
                    Vector3 LocalPlayerPos = getPosition(LocalPlayer);
                    Vector3 pos2 = WorldToScreenPoint(camera, PlayerPos);
                    if (pos2.z < 1.0f)
    continue;   
                    bool isFov1 = isFov(Vector3(pos2.x, pos2.y), Vector3(g_GlWidth / 2, g_GlHeight / 2), Fov_Aim);
                    float distance = Vector3::Distance(LocalPlayerPos, PlayerPos);
                    if (distance < Aimdis) {
                        Vector3 targetDir = Vector3::Normalized(PlayerPos - LocalPlayerPos);
                        Vector3 forward = GetForward(Component_GetTransform(camera));



float dot = Vector3::Dot(forward, targetDir);

if (dot <= 0.02f)
    continue;
                        float angle = Vector3::Angle(targetDir, GetForward(Component_GetTransform(camera))) * 100.0;             
                    if (angle <= Fov_Aim && isFov1 && angle < shortestDistance) {                      shortestDistance = angle;
                    closestEnemy = Player;
                        }
                    }
                }
            }
        }
    }
    return closestEnemy;
} 





bool saved = false;
float savedScreenWidth = 0;
float savedScreenHeight = 0;
float active = 0.0f;
float desactive = 0.0f;

void UpdateSpeedhack() {
    if (Enable) {
        void* Simulation = GetSimulationTimer();
     if (Simulation != nullptr) {
   float FixedDeltaTime = GetTimer(Simulation);
            if(!saved) {
                active = FixedDeltaTime * 1.82f;
                desactive = FixedDeltaTime;
                saved = true;
            }
   if (SpeedHack) {
       if (FixedDeltaTime != active) {
                    SetTimer(Simulation, active);
    }
   }
   else {
       if (FixedDeltaTime != desactive) {
                    SetTimer(Simulation, desactive);
    }
   }
  }
 }
}



float (*get_deltaTime)();
float smoothSpeedAIM = 5; 
void *MyPlayer = NULL;
bool Drone;
const float RADAR_SIZE = 200.0f; 
const ImVec2 RADAR_CENTER(100.0f, 100.0f); 
float x,y;
float enemy1 = 2.0f;

ImVec4 colorHexagono = ImVec4(150 / 255.0f, 0, 255 / 255.0f, 1.0f);

void* CurrentMatch = nullptr;
void* closestEnemy = nullptr;
void* LocalPlayer = nullptr;
void* g_ClosestEnemy = nullptr;


float aimSmoothness = 0.1f;

inline void DrawAIMBOT(float screenWidth, float screenHeight) {
     
}



void DrawFastSkeleton(void* enemy, void* mainCamera, ImDrawList* drawList, float distance, float screenWidth, float screenHeight) {
	if (!Enable) return;
	
	
    
    
    if (!enemy || !mainCamera || !drawList || distance <= 0.0f) {
        return; 
    }
    
    if (distance > 120.f)
    return;

    ImVec2 boneScreen[BONE_COUNT];
    bool boneVisible[BONE_COUNT];


    for (int i = 0; i < BONE_COUNT; i++) {
        boneVisible[i] = false;
        boneScreen[i] = ImVec2(0, 0);
    }

    for (int i = 0; i < BONE_COUNT; i++) {

        if (gBoneOffsets[i] == 0) continue;

        uintptr_t nodeAddress = (uintptr_t)enemy + gBoneOffsets[i];
        
        if (!nodeAddress) continue;

        void* node = *(void**)nodeAddress;
        if (!node) continue;
        
        void* transform = get_itransform(node);
        if (!transform) continue;


        Vector3 worldPos = Transform_GetPosition(transform);
        
 
        Vector3 screenPos = WorldToScreenPoint(mainCamera, worldPos);


        if (!std::isfinite(screenPos.x) ||
    !std::isfinite(screenPos.y) ||
    !std::isfinite(screenPos.z))
    continue;

if (screenPos.z <= 0.01f)
    continue;
    
    if (screenPos.x < -1000 || screenPos.x > screenWidth + 1000)
    continue;

if (screenPos.y < -1000 || screenPos.y > screenHeight + 1000)
    continue;

boneScreen[i] = ImVec2(screenPos.x, screenHeight - screenPos.y);
boneVisible[i] = true;
    }

    float scaleFactor = std::max(0.35f, 30.f / distance);
    float lineThickness = 0.5f * scaleFactor;
    ImU32 boneColor = ImGui::ColorConvertFloat4ToU32(SkeletonColor);

    auto DrawBoneLine = [&](BoneID b1, BoneID b2) -> void {
        if (b1 >= BONE_COUNT || b2 >= BONE_COUNT) return;
        if (boneVisible[b1] && boneVisible[b2]) {
            drawList->AddLine(boneScreen[b1], boneScreen[b2], boneColor, lineThickness);
        }
    };


    DrawBoneLine(B_Head, B_Neck);
    DrawBoneLine(B_Neck, B_Hip);
    DrawBoneLine(B_Neck, B_LShoulder);
    DrawBoneLine(B_Neck, B_RShoulder);
    DrawBoneLine(B_LShoulder, B_LElbow);
    DrawBoneLine(B_RShoulder, B_RElbow);
    DrawBoneLine(B_LElbow, B_LHand);
    DrawBoneLine(B_RElbow, B_RHand);
    DrawBoneLine(B_Hip, B_LKnee);
    DrawBoneLine(B_Hip, B_RKnee);
    DrawBoneLine(B_LKnee, B_LFoot);
    DrawBoneLine(B_RKnee, B_RFoot);
    
    if (boneVisible[B_Head]) {
    drawList->AddCircle(
        boneScreen[B_Head],
        1.8f * scaleFactor,      // نصف القطر
        boneColor,               // نفس لون الهيكل
        10,                      // عدد القطاعات
        lineThickness            // نفس سماكة الخط
    );
}

}



static int g_CachedEnemyCount = 0;
static int g_CachedDeadCount  = 0;
static float g_LastUpdateTime  = 0.0f;

inline void DrawEnemiesCount(float screenWidth)
{
    if (!EnemyCount)
        return;

    float time = ImGui::GetTime();

    if (time - g_LastUpdateTime >= 0.2f)
    {
        g_LastUpdateTime = time;

        void* match = Curent_Match();
        if (!match) return;

        void* localPlayer = GetLocalPlayer(match);
        if (!localPlayer) return;

        MyDictionary* players = *(MyDictionary**)((uintptr_t)match + ListPlayer);
        if (!players || !players->entries) return;

        int count = players->count;
        if (count > 100) count = 100;

        int aliveCount = 0;
        int deadCount  = 0;

        for (int i = 0; i < count; i++)
        {
            void* enemy = players->entries->vector[i].value;
            if (!enemy || enemy == localPlayer) continue;
            if (get_isLocalTeam(enemy)) continue;
            if (get_MaxHP(enemy) <= 0.1f) continue;
            if (!IsInDistance(localPlayer, enemy)) continue;

            if (get_IsDieing(enemy))
                deadCount++;
            else
                aliveCount++;
        }

        g_CachedEnemyCount = aliveCount;
        g_CachedDeadCount  = deadCount;
    }

    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    if (!draw) return;

    ImFont* font = ImGui::GetFont();
    if (!font) return;

    // ─── Position: top-right corner (matches image) ───────────────────────
    // Image shows:  [person_icon] 35   [skull_icon] 8
    // Placed at top-right, approx screenWidth - 160, y=18
    float iconSize  = 38.0f;
    float numSize   = 38.0f;
    float rightX    = screenWidth - 10.0f;
    float topY      = 18.0f;

    // Format strings
    char aliveStr[8], deadStr[8];
    snprintf(aliveStr, sizeof(aliveStr), "%d", g_CachedEnemyCount);
    snprintf(deadStr,  sizeof(deadStr),  "%d", g_CachedDeadCount);

    ImVec2 aliveSize = font->CalcTextSizeA(numSize, FLT_MAX, 0.0f, aliveStr);
    ImVec2 deadSize  = font->CalcTextSizeA(numSize, FLT_MAX, 0.0f, deadStr);

    // Skull number (right side, like image shows "8" on right)
    float deadNumX = rightX - deadSize.x;
    // Skull icon to its left (unicode skull U+1F480 not avail in imgui — use solid circle as placeholder)
    float skullIconW = iconSize * 0.8f;
    float skullX     = deadNumX - skullIconW - 4.0f;

    // Alive number to the left of skull group
    float aliveNumX = skullX - aliveSize.x - 14.0f;
    // Person icon to left of alive number
    float personIconW = iconSize * 0.8f;
    float personX     = aliveNumX - personIconW - 4.0f;

    // Shadow helper
    auto DrawShadowText = [&](float x, float y, float sz, ImU32 col, const char* txt) {
        draw->AddText(font, sz, ImVec2(x+1,y+1), IM_COL32(0,0,0,160), txt);
        draw->AddText(font, sz, ImVec2(x,  y),   col,                  txt);
    };

    // ── Alive count (white) ────────────────────────────────────────────────
    // Person icon: draw a small filled circle + rectangle (head+body silhouette)
    {
        float cx = personX + personIconW * 0.5f;
        float headR  = iconSize * 0.14f;
        float bodyHH = iconSize * 0.22f;
        float bodyW  = iconSize * 0.20f;
        float headCY = topY + headR + iconSize * 0.02f;
        float bodyCY = headCY + headR + bodyHH * 0.5f + 1.0f;
        // shadow
        draw->AddCircleFilled(ImVec2(cx+1, headCY+1), headR, IM_COL32(0,0,0,140), 12);
        draw->AddRectFilled(ImVec2(cx-bodyW*0.5f+1, bodyCY-bodyHH*0.5f+1),
                            ImVec2(cx+bodyW*0.5f+1, bodyCY+bodyHH*0.5f+1), IM_COL32(0,0,0,140), 2.0f);
        // white icon
        draw->AddCircleFilled(ImVec2(cx, headCY), headR, IM_COL32(255,255,255,230), 12);
        draw->AddRectFilled(ImVec2(cx-bodyW*0.5f, bodyCY-bodyHH*0.5f),
                            ImVec2(cx+bodyW*0.5f, bodyCY+bodyHH*0.5f), IM_COL32(255,255,255,230), 2.0f);
    }

    DrawShadowText(aliveNumX, topY, numSize, IM_COL32(255,255,255,255), aliveStr);

    // ── Dead count (white) ─────────────────────────────────────────────────
    // Skull icon: circle with two small eye-holes
    {
        float cx   = skullX + skullIconW * 0.5f;
        float cy   = topY + iconSize * 0.3f;
        float r    = iconSize * 0.22f;
        float eyeR = r * 0.22f;
        // shadow
        draw->AddCircleFilled(ImVec2(cx+1, cy+1), r, IM_COL32(0,0,0,140), 16);
        // skull circle
        draw->AddCircleFilled(ImVec2(cx, cy), r, IM_COL32(255,255,255,220), 16);
        // eyes (dark holes)
        draw->AddCircleFilled(ImVec2(cx - r*0.32f, cy - r*0.10f), eyeR, IM_COL32(80,80,80,255), 8);
        draw->AddCircleFilled(ImVec2(cx + r*0.32f, cy - r*0.10f), eyeR, IM_COL32(80,80,80,255), 8);
        // jaw notch
        draw->AddRectFilled(ImVec2(cx-r*0.28f, cy+r*0.25f), ImVec2(cx+r*0.28f, cy+r*0.55f), IM_COL32(80,80,80,200), 1.0f);
    }

    DrawShadowText(deadNumX, topY, numSize, IM_COL32(255,255,255,255), deadStr);
}

// Screen Timer

static std::chrono::steady_clock::time_point timerStartTime;
static bool wasTimerRunning = false;
static float elapsedTimerSeconds = 0.0f;

inline void DrawGameTimer(ImDrawList* drawList, float screenWidth, float screenHeight) {
    if (!GameTimer || !drawList) return;

    // تشغيل وإيقاف العداد
    if (Enable) {
        if (!wasTimerRunning) {
            timerStartTime = std::chrono::steady_clock::now();
            wasTimerRunning = true;
        }

        auto now = std::chrono::steady_clock::now();
        elapsedTimerSeconds =
            std::chrono::duration<float>(now - timerStartTime).count();
    } else {
        elapsedTimerSeconds = 0.0f;
        wasTimerRunning = false;
    }

    // تحديد لون الوقت
    float elapsedMinutes = elapsedTimerSeconds / 60.0f;
    ImColor valueColor;

    if (!Enable) {
        valueColor = ImColor(0, 255, 0, 255);
    }
    else if (elapsedMinutes < 1.0f) {
        valueColor = ImColor(255, 0, 0, 255);
    }
    else if (elapsedMinutes < 2.0f) {
        valueColor = ImColor(255, 140, 0, 255);
    }
    else if (elapsedMinutes < 3.0f) {
        valueColor = ImColor(255, 255, 0, 255);
    }
    else {
        valueColor = ImColor(0, 255, 0, 255);
    }

    // مكان العداد (تم رفعه للأعلى)
    ImVec2 rectPos(30.0f, 30.0f);
    ImVec2 rectSize(160.0f, 35.0f);
    ImVec2 rectMax(rectPos.x + rectSize.x, rectPos.y + rectSize.y);

    float rounding = 6.0f;

    drawList->AddRect(
        rectPos,
        rectMax,
        ImColor(0, 255, 0, 255),
        rounding,
        0,
        1.5f
    );

    // نص الوقت
    int totalSeconds = static_cast<int>(elapsedTimerSeconds);

int minutes = totalSeconds / 60;
int seconds = totalSeconds % 60;

char timerBuffer[32];
snprintf(timerBuffer, sizeof(timerBuffer), "TIMER : %d:%02d", minutes, seconds);

    std::string labelText = "TIMER : ";
    std::string timeText = std::string(timerBuffer).substr(labelText.length());

    float textHeight = ImGui::GetTextLineHeight();
    ImVec2 textPos(
        rectPos.x + 12.0f,
        rectPos.y + (rectSize.y - textHeight) * 0.5f
    );

    float labelWidth = ImGui::CalcTextSize(labelText.c_str()).x;

    // ===== ظل النص =====

    // ظل TIMER :
    drawList->AddText(
        ImVec2(textPos.x + 2.0f, textPos.y + 2.0f),
        IM_COL32(0, 0, 0, 200),
        labelText.c_str()
    );

    // ظل الوقت
    drawList->AddText(
        ImVec2(textPos.x + labelWidth + 2.0f, textPos.y + 2.0f),
        IM_COL32(0, 0, 0, 200),
        timeText.c_str()
    );

    // ===== النص الحقيقي =====

    drawList->AddText(
        textPos,
        ImColor(255, 255, 255, 255),
        labelText.c_str()
    );

    drawList->AddText(
        ImVec2(textPos.x + labelWidth, textPos.y),
        valueColor,
        timeText.c_str()
    );
}


// ── AUTO SWITCH ──────────────────────────────────────────────────────
// يبدل بين slot 1 و slot 2 محلياً فقط (بدون إرسال للسيرفر)
// ─────────────────────────────────────────────────────────────────────
#include <chrono>

inline void AutoSwitchLoop()
{
    if (!Enable || !AutoSwitch) return;

    static auto lastSwitch = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSwitch).count();
    if (elapsed < AutoSwitchSpeed) return;
    lastSwitch = now;

    void* match = Curent_Match();
    if (!match) return;

    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer) return;

    // يبدل بين Slot 1 و Slot 2 مباشرة بدون فحص السلاح
    static int lastSlot = 2;
    int newSlot = (lastSlot == 1) ? 2 : 1;

    SwapWeapon(localPlayer, newSlot, 1);
    lastSlot = newSlot;
}
// ─────────────────────────────────────────────────────────────────────

// ── LAZ ESP NAME ─────────────────────────────────────────────────────
// تعرض اسم الشيت + اسم اللعبة + عدد الأعداء الأحياء أعلى الشاشة
// ─────────────────────────────────────────────────────────────────────
static int   s_lazEspLastCount     = -1;
static float s_lazEspLastTime      = 0.0f;
static char  s_lazEspTextBuffer[256] = {};

inline void DrawLazESPName(float screenWidth, float screenHeight)
{
    if (!Enable) return;

    float now = ImGui::GetTime();

    // تحديث كل 0.2 ثانية فقط (تخفيف الحِمل)
    if (now - s_lazEspLastTime >= 0.2f)
    {
        s_lazEspLastTime = now;

        int enemyCount = 0;

        void* match = Curent_Match();
        if (match)
        {
            void* localPlayer = GetLocalPlayer(match);
            if (localPlayer)
            {
                MyDictionary* players =
                    *(MyDictionary**)((uintptr_t)match + ListPlayer);

                if (players && players->entries)
                {
                    int total = players->count;
                    if (total > 100) total = 100;

                    for (int i = 0; i < total; i++)
                    {
                        void* enemy = players->entries->vector[i].value;
                        if (!enemy || enemy == localPlayer) continue;
                        if (get_isLocalTeam(enemy))           continue;
                        if (get_IsDieing(enemy))              continue;
                        if (get_MaxHP(enemy) <= 0)            continue;

                        enemyCount++;
                    }
                }
            }
        }

        s_lazEspLastCount = enemyCount;

        // تحديد اسم اللعبة من /proc/self/cmdline
        const char* gameName = "Free Fire";
        {
            char cmdline[256] = {};
            int fd = open("/proc/self/cmdline", O_RDONLY);
            if (fd >= 0) {
                read(fd, cmdline, sizeof(cmdline) - 1);
                close(fd);
                if (strstr(cmdline, "freefiremax"))
                    gameName = "Free Fire Max";
            }
        }

        snprintf(s_lazEspTextBuffer, sizeof(s_lazEspTextBuffer),
                 " LION CHEATS - %s [ %d ] ", gameName, s_lazEspLastCount);
    }

    if (s_lazEspTextBuffer[0] == '\0') return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    ImFont*  font     = ImGui::GetFont();
    float    fontSize = 28.0f;

    ImVec2 textSize = font
        ? font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, s_lazEspTextBuffer)
        : ImGui::CalcTextSize(s_lazEspTextBuffer);

    // توسيط النص أفقياً، 12px من الأعلى
    float textX = (screenWidth  - textSize.x) * 0.5f;
    float textY = 12.0f;

    // خلفية شبه شفافة
    float padX = 10.0f, padY = 4.0f;
    drawList->AddRectFilled(
        ImVec2(textX - padX,              textY - padY),
        ImVec2(textX + textSize.x + padX, textY + textSize.y + padY),
        IM_COL32(0, 0, 0, 140),
        6.0f
    );

    // ظل النص
    drawList->AddText(font, fontSize,
        ImVec2(textX + 1.5f, textY + 1.5f),
        IM_COL32(0, 0, 0, 200),
        s_lazEspTextBuffer);

    // النص الحقيقي (أبيض)
    drawList->AddText(font, fontSize,
        ImVec2(textX, textY),
        IM_COL32(255, 255, 255, 255),
        s_lazEspTextBuffer);
}
// ─────────────────────────────────────────────────────────────────────

inline void DrawESP(float screenWidth, float screenHeight) {
 ImDrawList*draw = ImGui::GetBackgroundDrawList();
 
 DrawGameTimer(draw, screenWidth, screenHeight);
// DrawLazESPName removed
 
    if (!draw) return;
    
    
// 


if (Enable) {

// IN DrawESP
DrawEnemiesCount(screenWidth);

    if (!HideFov) {
    draw->AddCircle(
        ImVec2(screenWidth * 0.5f, screenHeight * 0.5f),
        Fov_Aim,
        ImGui::ColorConvertFloat4ToU32(FovColor),
        (int)(Fov_Aim * 0.8f),
        1.8f
    );
}

// EnemyCountVoid();

    int enemyIndex = 0; 
    void* current_Match = Curent_Match();
    void* local_player = GetLocalPlayer(current_Match);
    if (local_player && current_Match) {
        MyDictionary* players = *(MyDictionary**)((uintptr_t)current_Match + ListPlayer);
        void* camera = Camera_main();
        if (players && players->entries && camera) {
            int total = players->count;
            for (int u = 0; u < total; u++) {
                void* closestEnemy = players->entries->vector[u].value;
                
if (closestEnemy &&
    closestEnemy != local_player &&
    !get_isLocalTeam(closestEnemy) &&
    IsInDistance(local_player, closestEnemy))
{enemyIndex++;
                
                
                
                    Vector3 Toepos = getPosition(closestEnemy);
                    Vector3 Toeposi = WorldToScreenPoint(camera, Toepos);
                    if (Toeposi.z < 1) continue;
                    Vector3 HeadPos = Toepos + Vector3(0, 1.9f, 0);
                    Vector3 HeadPosition = WorldToScreenPoint(camera, HeadPos);                     if (HeadPosition.z < 1) continue;
                    
                     float distance = Vector3::Distance(getPosition(local_player), Toepos);                     				 					 
					 float Height = abs(HeadPosition.y - Toeposi.y) * 1.09f;
                     float Width = Height * 0.55f;                                                    
				     Rect rect = Rect(HeadPosition.x - Width / 2.f, screenHeight - HeadPosition.y, Width, Height);																																	


                        
if (Config.ESP.Health)
{
    int currentHp = GetHp(closestEnemy);
    int maxHp = get_MaxHP(closestEnemy);

    if (maxHp <= 0)
        maxHp = 100;

    long clr = ImColor(0, 255, 0, 255);

    if (currentHp <= (maxHp * 0.6))
        clr = ImColor(255, 255, 0, 255);

    if (currentHp < (maxHp * 0.3))
        clr = ImColor(255, 0, 0, 255);

    int xx = rect.x + rect.w + 2;
    int yy = rect.y;

    draw->AddRectFilled(
        ImVec2(xx, yy),
        ImVec2(xx + 5, yy + rect.h),
        ImColor(0, 0, 0, 255)
    );

    draw->AddRectFilled(
        ImVec2(xx + 1,
               yy + rect.h - (rect.h * ((float)currentHp / maxHp))),
        ImVec2(xx + 4, yy + rect.h),
        clr
    );

if (ShowHP)
{
    char hpText[24];
    sprintf(hpText, "%d", currentHp);


    
    ImFont* font = ImGui::GetFont();

    ImVec2 textSize = font->CalcTextSizeA(HPFontSize, FLT_MAX, 0.0f, hpText);

    ImVec2 textPos(
        xx + 6,
        yy + (rect.h * 0.5f) - (textSize.y * 0.5f)
    );

    draw->AddText(
        font,
        HPFontSize,
        ImVec2(textPos.x + 1.0f, textPos.y + 1.0f),
        IM_COL32(0, 0, 0, 80),
        hpText
    );

    draw->AddText(
        font,
        HPFontSize,
        ImVec2(textPos.x + 1.0f, textPos.y),
        IM_COL32(0, 0, 0, 160),
        hpText
    );

    draw->AddText(
        font,
        HPFontSize,
        textPos,
        clr,
        hpText
        );
    }
}

        



static void* cachedTarget = nullptr;
static void* cachedCamera = nullptr;
static std::chrono::steady_clock::time_point lastSearchTime;

if (TargetLine)
{

    void* camera = Camera_main();
    if (camera) 
    {

        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastSearchTime).count();


        if (elapsedTime >= 70 || !cachedTarget) 
        {
            cachedTarget = GetClosestEnemy();
            lastSearchTime = currentTime;
        }


        if (cachedTarget)
        {
            Vector3 pos = GetHeadPosition(cachedTarget);
            Vector3 screenPos = WorldToScreenPoint(camera, pos);

 
            if (screenPos.z > 1.0f)
            {
                // مركز الشاشة
                ImVec2 start(screenWidth * 0.5f, screenHeight * 0.5f);

                // نهاية الخط
                ImVec2 end(screenPos.x, screenHeight - screenPos.y);

                // رسم الخط للهدف
                draw->AddLine(
                    start,
                    end,
                    ImColor(255, 0, 0, 255),
                    1.5f
                );
            }
        }
    }
}

             
if (Config.ESP.Line) {

    ImColor lineColor = get_IsDieing(closestEnemy)
        ? ImColor(255, 0, 0, 255)
        : ImColor(EspLineColor);


    ImVec2 startPoint;
    ImVec2 endPoint;
    
    if (LineBaseMode == 0) {
        startPoint = ImVec2(screenWidth / 2, 0);
        endPoint = ImVec2(rect.x + rect.w / 2, rect.y + rect.h / 35);
    } else {
        startPoint = ImVec2(screenWidth / 2, screenHeight);
        endPoint = ImVec2(rect.x + rect.w / 2, rect.y + rect.h);
    }

    draw->AddLine(
        startPoint,
        endPoint,
        lineColor,
        1.1f
    );
}

if (Config.ESP.Box)
{
int x = rect.x;
int y = rect.y;

ImColor boxColor = get_IsDieing(closestEnemy)  
    ? ImColor(255, 0, 0, 30)  
    : ImColor(EspBoxColor);  

if (BoxStyleMode == 0) {   
 
    draw->AddRect(  
        ImVec2(x, y),  
        ImVec2(x + rect.w, y + rect.h),  
        boxColor,  
        visual_esp_box, 0, visual_esp_boxth  
    );  

    
    for (int i = 0; i < 2; i++) {  
        float thickness = visual_esp_boxth + (i * 1.4f);  
        float alpha = 0.10f / (i + 1);  

        ImVec4 glow = get_IsDieing(closestEnemy)  
            ? ImVec4(1.0f, 0.0f, 0.0f, alpha)  
            : ImVec4(EspBoxColor.x, EspBoxColor.y, EspBoxColor.z, alpha);  

        draw->AddRect(  
            ImVec2(x, y),  
            ImVec2(x + rect.w, y + rect.h),  
            ImColor(glow),  
            visual_esp_box, 0, thickness  
        );  
    }  
}   
else if (BoxStyleMode == 1) {

    ImColor fullBoxColor = get_IsDieing(closestEnemy)
        ? ImColor(255, 0, 0, 30)
        : ImColor(EspFullBoxColor);

    draw->AddRectFilled(
        ImVec2(x, y),
        ImVec2(x + rect.w, y + rect.h),
        fullBoxColor,
        visual_esp_box, 0
    );
}
else {

    ImColor fullBoxColor = get_IsDieing(closestEnemy)
        ? ImColor(255, 0, 0, 30)
        : ImColor(EspFullBoxColor);

    draw->AddRectFilled(
        ImVec2(x, y),
        ImVec2(x + rect.w, y + rect.h),
        fullBoxColor,
        visual_esp_box, 0
    );

    draw->AddRect(
        ImVec2(x, y),
        ImVec2(x + rect.w, y + rect.h),
        boxColor, // يبقى EspBoxColor
        visual_esp_box, 0, visual_esp_boxth
    );

    for (int i = 0; i < 2; i++) {
        float thickness = visual_esp_boxth + (i * 1.4f);
        float alpha = 0.10f / (i + 1);

        ImVec4 glow = get_IsDieing(closestEnemy)
            ? ImVec4(1.0f, 0.0f, 0.0f, alpha)
            : ImVec4(EspBoxColor.x, EspBoxColor.y, EspBoxColor.z, alpha);

        draw->AddRect(
            ImVec2(x, y),
            ImVec2(x + rect.w, y + rect.h),
            ImColor(glow),
            visual_esp_box, 0, thickness
            );
        }
    }
}

if (EspSkeleton) {

    Vector3 myPos = getPosition(local_player);
    Vector3 enemyPos = getPosition(closestEnemy);
    float distance = Vector3::Distance(myPos, enemyPos);
    
    

    DrawFastSkeleton(closestEnemy, camera, draw, distance, screenWidth, screenHeight);
}

if (Config.ESP.Infos) {
    monoString* Nick = get_NickName(closestEnemy);
    std::string name = "Unknown";

    if (Nick != nullptr) {
        int len = Nick->getLength();

        if (len > 0) {
            name.clear();

            for (int i = 0; i < len; i++) {
                char c = get_Chars(Nick, i);
                name.push_back((isascii(c) && isprint(c)) ? c : '?');
            }
        }
    }

    std::string distText = std::to_string((int)distance) + " ";

    ImFont* font = ImGui::GetFont();

    float fontScale = 0.8f;
    float fontSize = font->FontSize * fontScale;

    ImVec2 nameSize = ImGui::CalcTextSize(name.c_str());
    nameSize.x *= fontScale;

    ImVec2 distSize = ImGui::CalcTextSize(distText.c_str());
    distSize.x *= fontScale;

    float centerX = rect.x + rect.w * 0.5f;
    float nameY = rect.y - fontSize - 8.0f;
    float distY = nameY - fontSize - 2.0f;

    ImVec2 namePos(centerX - nameSize.x * 0.5f, nameY);
    ImVec2 distPos(centerX - distSize.x * 0.5f, distY);

    ImU32 shadowColor = IM_COL32(0, 0, 0, 200);
    ImU32 nameColor = IM_COL32(240, 240, 240, 255);
    ImU32 distColor = IM_COL32(180, 180, 180, 255);

    // ظل المسافة
    draw->AddText(font, fontSize, ImVec2(distPos.x + 1.0f, distPos.y + 1.0f), shadowColor, distText.c_str());
    draw->AddText(font, fontSize, ImVec2(distPos.x - 1.0f, distPos.y + 1.0f), shadowColor, distText.c_str());
    draw->AddText(font, fontSize, ImVec2(distPos.x + 1.0f, distPos.y - 1.0f), shadowColor, distText.c_str());
    draw->AddText(font, fontSize, ImVec2(distPos.x - 1.0f, distPos.y - 1.0f), shadowColor, distText.c_str());

    // المسافة
    draw->AddText(font, fontSize, distPos, distColor, distText.c_str());

    // ظل الاسم
    draw->AddText(font, fontSize, ImVec2(namePos.x + 1.0f, namePos.y + 1.0f), shadowColor, name.c_str());
    draw->AddText(font, fontSize, ImVec2(namePos.x - 1.0f, namePos.y + 1.0f), shadowColor, name.c_str());
    draw->AddText(font, fontSize, ImVec2(namePos.x + 1.0f, namePos.y - 1.0f), shadowColor, name.c_str());
    draw->AddText(font, fontSize, ImVec2(namePos.x - 1.0f, namePos.y - 1.0f), shadowColor, name.c_str());

    // الاسم
    draw->AddText(font, fontSize, namePos, nameColor, name.c_str());
}

    
    
    
    }}}}}
}


void AimbotLegitVoid()
{
    if (!Enable || !AimbotLegit)
        return;



    void* match = Curent_Match();
    void* localPlayer = GetLocalPlayer(match);
    void* enemy = GetClosestEnemy();



    void* collider = *(void**)((uintptr_t)enemy + 0x78);
    void* head = Player_GetHeadCollider(enemy);
    if (head && collider != head)
        SetAimCollider(enemy, head);
}

// Aspect hack
float originalAspect;
float hackAspect = 2.0f;
bool isSavedAspect = false;
bool AspectHack = false;

void UpdateAspect() {
    void* cam = get_main();
    if (!cam) return;

    float currentAspect = GetAspect(cam);

    if (!isSavedAspect) {
        originalAspect = currentAspect;
        isSavedAspect = true;
    }

    if (AspectHack) {
        if (currentAspect != hackAspect) {
            SetAspect(cam, hackAspect);
        }
    } else {

        if (currentAspect != originalAspect) {
            SetAspect(cam, originalAspect);
        }
    }
}




    
    

// Auto Fire Config
bool isEnemyInRangeWeapon(void *player, void *enemy, void* weapon)
{
    if (player != nullptr && enemy != nullptr && weapon != nullptr)
    {
        Vector3 EnemyHeadPosition = GetHeadPosition(enemy);
        Vector3 PlayerHeadPosition = GetHeadPosition(player);
        float distance = Vector3::Distance(PlayerHeadPosition, EnemyHeadPosition);
        float range = get_Range(weapon);

        if (distance <= range) {
            return true;
        }
    }
    return false;
}

static void StartFiring2(void* weapon) {
    if (!weapon) return;
    auto fn = reinterpret_cast<void(*)(void*)>(offset_Weapon_StartFiring);
    fn(weapon);
}

static void StopFiring2(void* weapon) {
    if (!weapon) return;
    auto fn = reinterpret_cast<void(*)(void*)>(offset_Weapon_StopFiring);
    fn(weapon);
}



#include <map>
static std::chrono::steady_clock::time_point lastAutoShotTime;
static bool isAutoFiring = false;
bool ignoreFiring = AutoFire;

static bool isAutoFiring2 = false;

// Teleport Mark

// TeleMark Config
Vector3 SavedMapMarker = {0,0,0};
bool HasMapMarker = false;

// UPDATED ORIGINAL FUNCTION (4 parameters)
void (*orig_UpdateLocalMark)(
    void* _this,
    Vector3 p,
    uint32_t posType,
    Vector3 realPos,
    int bigMapType
);

// HOOK FUNCTION (UPDATED SIGNATURE)
void hook_UpdateLocalMark(
    void* _this,
    Vector3 p,
    uint32_t posType,
    Vector3 realPos,
    int bigMapType)
{
    SavedMapMarker = realPos;
    HasMapMarker = true;

    if (orig_UpdateLocalMark)
        orig_UpdateLocalMark(_this, p, posType, realPos, bigMapType);
}

float TeleportYOffset = 0.0f;





void TestTeleport()
{
    if (!Enable || !Teleport)
        return;

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
    pos.y += TeleportYOffset;

    SetPosition(
        localTF,
        pos
    );
}

void TeleReviveVoid()
{
    if (!Enable || !TeleRevive)
        return;

    void* match = Curent_Match();
    if (!match)
        return;

    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer)
        return;
        
    MyDictionary* players = *(MyDictionary**)((uintptr_t)match + ListPlayer);
    if (!players || !players->entries) return;

    

    for (int i = 0; i < players->count && i < 64; i++) {
        void* target = players->entries->vector[i].value;
        if (!target || target == localPlayer) continue;

        if (!get_isLocalTeam(target)) continue;
        if (!get_IsDieing(target)) continue;
        if (GetHp(target) < 0) continue;

    void* localTF = Component_GetTransform(localPlayer);
    if (!localTF)
        return;

    Vector3 pos = getPosition(target);
    pos.y += TeleportYOffset;

    SetPosition(
        localTF,
        pos
        );
    }
}

void TestTeleMark()
{
    if (!Enable || !TeleMark)
        return;

    if (!HasMapMarker)
        return;

    void* match = Curent_Match();
    if (!match)
        return;

    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer)
        return;

    void* localTF = Component_GetTransform(localPlayer);
    if (!localTF)
        return;

    Vector3 targetPos;
    targetPos.x = SavedMapMarker.x;
    targetPos.y = SavedMapMarker.y + 0.2f;
    targetPos.z = SavedMapMarker.z;

    SetPosition(
        localTF,
        targetPos
    );
}


void AimMagnetVoid()
{
    if (!Enable || !AimMagnet)
    return;


    void* camera = Camera_main();
    if (!camera) return;
    
    void* match = Curent_Match();
    if (!match)
        return;

    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer)
        return;



        void* Enemy = GetClosestEnemy();

        if (!Enemy)
            return;

        if (get_MaxHP(Enemy) <= 0.1f || get_IsDieing(Enemy))
            return;

void* enemyTransform = Component_GetTransform(Enemy);
void* camTransform = Component_GetTransform(camera);

if (!enemyTransform || !camTransform)
    return;

Vector3 camPos = GetPosition(camTransform);
Vector3 forward = GetForward(camTransform);
Vector3 enemyPos = GetPosition(enemyTransform);

float distance = Vector3::Distance(camPos, enemyPos);

float yOffset = -0.7f;

if (MagnetTarget == 0)
    yOffset = -1.27f;
else if (MagnetTarget == 1)
    yOffset = -1.0f;
else if (MagnetTarget == 2)
    yOffset = -0.80f;

Vector3 targetPos;

targetPos.x = camPos.x + forward.x * distance;
targetPos.y = camPos.y + forward.y * distance + yOffset;
targetPos.z = enemyPos.z;

const float maxMoveX = 1.5f;
const float maxMoveY = 0.5f;

float deltaX = targetPos.x - enemyPos.x;
float deltaY = targetPos.y - enemyPos.y;

if (deltaX > maxMoveX)
    targetPos.x = enemyPos.x + maxMoveX;
else if (deltaX < -maxMoveX)
    targetPos.x = enemyPos.x - maxMoveX;

if (deltaY > maxMoveY)
    targetPos.y = enemyPos.y + maxMoveY;
else if (deltaY < -maxMoveY)
    targetPos.y = enemyPos.y - maxMoveY;

            if (get_IsFiring(localPlayer) || get_IsSighting(localPlayer))
    {
        SetPosition(
            enemyTransform,
            targetPos);
            
            }

}

float CarY = -1.0f;

void TeleportCarVoid()
{
    if (!Enable || !TeleportCar) return;
    
    void* get_MatchGame = Curent_Match();
    void* LocalPlayer = GetLocalPlayer(get_MatchGame);
    
    if (LocalPlayer != NULL && get_MatchGame != NULL && Enable) {

        void* vehicle = GetVehicleIAmIn(LocalPlayer);  
        
        void* enemy = GetClosestEnemy();
        if (!enemy) return;
        

        void* tf = Component_GetTransform(vehicle);
        if (!tf) return;
        
        Vector3 pos = getPosition(enemy);
        pos.y += CarY;
        
        SetPosition(tf, pos);
    }
}

void RotateEnemyVoid() {
if (!Enable || !Rotatee)
        return;

    void* match = Curent_Match();
    if (!match)
        return;
    
    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer)
        return;


    MyDictionary* players = *(MyDictionary**)((uintptr_t)match + ListPlayer);  
    if (!players || !players->entries) 
        return;  

    static int rotateTick = 0;
    rotateTick++;

    for (int i = 0; i < players->count && i < 64; i++) 
    {  
        void* enemy = players->entries->vector[i].value;  
        if (!enemy || enemy == localPlayer) 
            continue; 

        if (get_isLocalTeam(enemy))
            continue;

        if (get_MaxHP(enemy) <= 0.1f)
            continue;

        if (get_IsDieing(enemy))
            continue;

        if (!IsInDistance(localPlayer, enemy))
            continue;
            
    void* tf = Component_GetTransform(enemy);
    if (!tf)
        return;

    Quaternion rot = GetRotation(tf);

    Quaternion flip = AngleAxis(
        180.0f,
        Vector3(0.0f, 0.0f, 1.0f)
    );

    rot = Quaternion_Multiply(rot, flip);

    SetRotation(tf, rot);
    }
}


static int currentStep = 0;
static float coverKillTimer = 0.0f;

void CoverKillVoid(float deltaTime)
{
    if (!Enable || !CoverKill)
        return;

    void* match = Curent_Match();
    if (!match)
        return;
    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer)
        return;

    MyDictionary* players = *(MyDictionary**)((uintptr_t)match + ListPlayer);  
    if (!players || !players->entries) 
        return;  


    coverKillTimer += deltaTime;
    if (coverKillTimer >= 0.18f)
    {
        currentStep = (currentStep + 1) % 4;
        coverKillTimer = 0.0f;
    }

    for (int i = 0; i < players->count && i < 64; i++) 
    {
        void* enemy = players->entries->vector[i].value;  
        if (!enemy || enemy == localPlayer) 
            continue; 

        if (get_isLocalTeam(enemy))
            continue;

        if (get_MaxHP(enemy) <= 0.1f)
            continue;

        if (get_IsDieing(enemy))
            continue;

        if (!IsInDistance(localPlayer, enemy))
            continue;

        void* enemyTransform = Component_GetTransform(enemy);
        if (!enemyTransform)
            continue;


        Vector3 basePos = GetPosition(enemyTransform);
        Vector3 targetPos = basePos;


        if (currentStep == 0) {
            targetPos.x += 2.0f;
            targetPos.z += 2.0f;
        }
        else if (currentStep == 1) {
            targetPos.x -= 2.0f;
            targetPos.z += 2.0f;
        }
        else if (currentStep == 2) {
            targetPos.x -= 2.0f;
            targetPos.z -= 2.0f;
        }
        else if (currentStep == 3) {
            targetPos.x += 2.0f;
            targetPos.z -= 2.0f;
        }


        SetPosition(enemyTransform, targetPos); 
    }
}


// Auto Revive

static void RequestRescueTargetV2(void* targetPlayer) {
    if (!targetPlayer) return;

    // Verify target is still knocked (IsDieing = true, HP > 0)
    if (!get_IsDieing(targetPlayer)) return;
    int hp = GetHp(targetPlayer);
    if (hp <= 0) return;  // fully dead, not knocked

    IHAAMHPPLMG pidRaw = Player_GetPlayerID(targetPlayer);
    uint32_t pid = PlayerID_ToUint(pidRaw);
    if (pid == 0) return;

    // Create message template at runtime
    void* msgTemplate = (void*)Il2CppCreateClassInstance(
        OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("COBFBHFCIPD"));
    if (!msgTemplate) return;

    uintptr_t offPID  = (uintptr_t)Il2CppGetFieldOffset(
        OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"),
        OBFUSCATE("COBFBHFCIPD"), OBFUSCATE("BAFEIAKDCEK"));
    uintptr_t offInt64 = (uintptr_t)Il2CppGetFieldOffset(
        OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"),
        OBFUSCATE("COBFBHFCIPD"), OBFUSCATE("OFAAFCOMJGJ"));
    if (!offPID || !offInt64) return;

    uint8_t msgBuf[64] = {};
    memcpy(msgBuf, (void*)msgTemplate, 64);
    *(uint32_t*)(msgBuf + offPID)  = pid;
    *(int64_t*)(msgBuf + offInt64) = 1;
    GameFacade_SendMsg(142, msgBuf, 2, 0);
}



float ReviveRadius = 9.0f;

void QuickReviveAll() {
    if (!Enable || !AutoRevive) return;

    static int skipFrames = 0;
    if (++skipFrames < 5) return;
    skipFrames = 0;

    void* match = Curent_Match();
    if (!match) return;

    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer) return;

    MyDictionary* players = *(MyDictionary**)((uintptr_t)match + ListPlayer);
    if (!players || !players->entries) return;

    Vector3 localPos = getPosition(localPlayer);

    for (int i = 0; i < players->count && i < 64; i++) {
        void* target = players->entries->vector[i].value;
        if (!target || target == localPlayer) continue;

        if (!get_isLocalTeam(target)) continue;
        if (!get_IsDieing(target)) continue;
        if (GetHp(target) <= 0) continue;  // fully dead, not knocked

        Vector3 teammatePos = getPosition(target);
        float distance = Vector3::Distance(localPos, teammatePos);

        if (distance <= ReviveRadius) {
            RequestRescueTargetV2(target);
            //break;  // one revive per 30-frame window
        }
    }
}

void PullKnockedVoid()
{
    if (!Enable || !PullKnocked) return; 
        
    void* match = Curent_Match();
    if (!match) return;

    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer) return;

    MyDictionary* players = *(MyDictionary**)((uintptr_t)match + ListPlayer);
    if (!players || !players->entries) return;

    Vector3 localPos = getPosition(localPlayer);

    for (int i = 0; i < players->count && i < 64; i++) {
        void* target = players->entries->vector[i].value;
        if (!target || target == localPlayer) continue;

        if (!get_isLocalTeam(target) || !get_IsDieing(target) || GetHp(target) <= 0) continue;

        Vector3 targetPos = getPosition(target);
        float distance = Vector3::Distance(localPos, targetPos);

        if (distance <= 12.0f && distance > 0.5f) {
            
            void* targetTransform = Component_GetTransform(target);
            if (targetTransform != nullptr) {
                

			Vector3 diff = localPos - targetPos;
			Vector3 direction = Vector3::Normalized(diff);



                
 
                Vector3 targetPointC = targetPos + (direction * 5.0f);
                
                SetPosition(targetTransform, targetPointC);
            }
        }
    }
}







static void FlipNearbyEnemies(void* player) {
    if (!FlipPlayerActive) return;
    if (!player) return;

    void* match = Curent_Match();
    if (!match) return;

    MyDictionary* dict = *(MyDictionary**)((uint64_t)match + ListPlayer);
    if (!dict || !dict->entries) return;

    for (int i = 0; i < dict->count && i < 64; i++) {
        void* p = dict->entries->vector[i].value;
        if (!p || p == player) continue;
        if (get_isLocalTeam(p)) continue;
        if (get_IsDieing(p)) continue;
        if ((float)GetHp(p) <= 0.0f) continue;

        void* tf = Component_GetTransform(p);
        if (!tf) continue;

        Vector3 sc = GetLocalScale(tf);
        if (sc.y > 0.0f) {
            sc.y = -sc.y;
            SetLocalScale(tf, sc);
        }
    }
}

static void RestoreFlipEnemies(void* player) {
    if (!player) return;

    void* match = Curent_Match();
    if (!match) return;

    MyDictionary* dict = *(MyDictionary**)((uint64_t)match + ListPlayer);
    if (!dict || !dict->entries) return;

    for (int i = 0; i < dict->count && i < 64; i++) {
        void* p = dict->entries->vector[i].value;
        if (!p || p == player) continue;
        if (get_isLocalTeam(p)) continue;

        void* tf = Component_GetTransform(p);
        if (!tf) continue;

        Vector3 sc = GetLocalScale(tf);
        if (sc.y < 0.0f) {
            sc.y = -sc.y;
            SetLocalScale(tf, sc);
        }
    }
}





// Fake Head


// Silent Kill

#define offset_BodyPart (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"), OBFUSCATE("DNFNNJMHNEK"))

struct HitObjectInfo {
    void *klass;
    void *monitor;
    bool m_IsInPool;
    void *HitObject;
    void *HitCollider;
    Vector3 HitLocation;
    Vector3 HitNormal;
    Vector3 RayDir;
    Vector3 StartPosition;
    int32_t Damage;
    float Distance;
    int32_t ActorLayer;
    int32_t HitGroup;
    void *HitPhysicMaterial;
    bool IgnoreHappens;
    bool ViewBlocked;
    struct Vector3 OrigStartPosition;
    uint8_t SpecialHitType;
    uint32_t SpecialHitLevelObjID;
};

struct DamageInfo2_o {
    void *klass;
    void *monitor;
    int32_t DBLBLKADCNP;
    int32_t KENBMOOEHBG;
    monoString* JANPNJIFOJJ;
    bool NNNADMOFPIE;
    void* GPBDEDFKJNA;
    int32_t PIAMIOFEBKF;
    Vector3 CNEICNJFGLM;
    Vector3 HECJHKEDFEB;
    Vector3 JNLGFLFLBHO;
    uint8_t ACAKHEABPEJ;
    bool MJIHLDJNHLF;
    int32_t LOKIMAEAPCB;
    monoDictionary<uint8_t*, void **> *FHLFLAHCIBN;
};

struct PlayerID_MKFEKBKJCKE_o;
struct PlayerID {
    uint32_t NBPDJAAAFBH;
    uint32_t JEDDPHIHGKL;
    uint8_t IOICFFEKAIL;
    uint8_t PHAFNFOFFDB;
    uint64_t BNFAIDHEHOM;
};

int (*orig_PlayerNetwork_TakeDamage)(void *ClosestEnemy, int baseDamage, PlayerID damager, DamageInfo2_o *damageInfo, int weaponDataID, Vector3 firePos, Vector3 hitPos, monoList<float> *checkParams, void *damagerWeaponDynamicInfo, uint32_t damagerVehicleID);



int hook_PlayerNetwork_TakeDamage(void *ClosestEnemy, int baseDamage, PlayerID damager, DamageInfo2_o *damageInfo, int weaponDataID, Vector3 firePos, Vector3 hitPos, monoList<float> *checkParams, void *damagerWeaponDynamicInfo, uint32_t damagerVehicleID) {

    if (!Enable) return orig_PlayerNetwork_TakeDamage(ClosestEnemy, baseDamage, damager, damageInfo, weaponDataID, firePos, hitPos, checkParams, damagerWeaponDynamicInfo, damagerVehicleID);

    void* CurrentMatch = Curent_Match();
    void* LocalPlayer = GetLocalPlayer(CurrentMatch);

    // Real Invisible - block damage to local player
    if (RealInvisible && ClosestEnemy && ClosestEnemy == LocalPlayer) {
        return 0;
    }
    
        
    
    if (LocalPlayer && ClosestEnemy) {
        firePos = GetHeadPosition(LocalPlayer);
        

        if (SilentTarget == 0) {
            hitPos = GetHeadPosition(ClosestEnemy);
        } 
        else if (SilentTarget == 1) {
            hitPos = GetHipPosition(ClosestEnemy);
        }
        else if (SilentTarget == 2) {
        hitPos = GetHeadPosition(ClosestEnemy);
        float enemyHP = GetHp(ClosestEnemy);
        if (enemyHP <= SilentChestRate) {
         hitPos = GetHipPosition(ClosestEnemy);
        }
        
        
        }
    }

    if (ClosestEnemy != NULL && damageInfo != NULL) {
        if (Headshot) {
            *(int *)((long) damageInfo + offset_BodyPart) = 1;
        } else if (SilentTarget == 1) {
            *(int *)((long) damageInfo + offset_BodyPart) = 2;
        }
        else if (SilentTarget == 2) {     
        float enemyHP = GetHp(ClosestEnemy);
        if (enemyHP <= SilentChestRate) {
        *(int *)((long) damageInfo + offset_BodyPart) = 2;        
            }
        }
    }
    
    return orig_PlayerNetwork_TakeDamage(ClosestEnemy, baseDamage, damager, damageInfo, weaponDataID, firePos, hitPos, checkParams, damagerWeaponDynamicInfo, damagerVehicleID);
}



int (*old_KOODEKEKFEK1)(void *, HitObjectInfo *);

int KOODEKEKFEK1(void *ist, HitObjectInfo *HitObject) {

    if (!Enable) return old_KOODEKEKFEK1(ist, HitObject);

    if (AimSilent2 && HitObject != nullptr) {
        void *current_match = Curent_Match();
        if (current_match != NULL) {
            void* local_player = GetLocalPlayer(current_match);
            if (local_player != NULL) {
                void* WeaponHand = GetWeaponOnHand(local_player);
                void* ClosestEnemy = g_ClosestEnemy;
                
                if (WeaponHand != nullptr && ClosestEnemy != nullptr) { 
                    Vector3 EnemyLocation;
                    void* ChosenCollider = nullptr;
                    int32_t ChosenGroup = 1;
                    if (SilentTarget == 0) {
                        EnemyLocation = GetHeadPosition(ClosestEnemy);
                        ChosenCollider = Player_GetHeadCollider(ClosestEnemy);
                        ChosenGroup = 1;
                    } 
                    else if (SilentTarget == 1) {
                        EnemyLocation = GetHipPosition(ClosestEnemy);
                        ChosenCollider = Player_GetHeadCollider(ClosestEnemy);
                        ChosenGroup = 2;
                    }         
                    else if (SilentTarget == 2) {  
                    EnemyLocation = GetHeadPosition(ClosestEnemy);
                        ChosenCollider = Player_GetHeadCollider(ClosestEnemy);
                        ChosenGroup = 1;
                    float enemyHP = GetHp(ClosestEnemy);
        if (enemyHP <= SilentChestRate) {
        EnemyLocation = GetHipPosition(ClosestEnemy);
                        ChosenCollider = Player_GetHeadCollider(ClosestEnemy);
                        ChosenGroup = 2;
                        }                    
                    }
                    
                    Vector3 PlayerLocation = CameraMain(local_player);                            
                    HitObject->HitObject = get_gameObject(ChosenCollider);
                    HitObject->HitCollider = ChosenCollider;                            
                    HitObject->HitLocation = EnemyLocation;
                    HitObject->HitNormal = EnemyLocation;
                    HitObject->RayDir = Vector3::Normalized(EnemyLocation - PlayerLocation);
                    HitObject->StartPosition = PlayerLocation;
                    HitObject->OrigStartPosition = PlayerLocation;
                    HitObject->SpecialHitType = 0;
                    HitObject->HitGroup = ChosenGroup;
                    HitObject->IgnoreHappens = false;
                    HitObject->ViewBlocked = false;
                }
            }
        }
    }
    return old_KOODEKEKFEK1(ist, HitObject);
}

#include "AimKill.h"
#include "TeleportRing.h"





// ============================================================
// GLIDER & TELEPORT IMPLEMENTATIONS
// ============================================================

// --- HELPER: get real function address ---
static void* getRealOffset(uintptr_t offset) {
    extern uintptr_t il2cpp_base;
    if (offset < 0x10000000)
        return reinterpret_cast<void*>(il2cpp_base + offset);
    return reinterpret_cast<void*>(offset);
}

// --- HELPER 1: OPEN GLIDER INSTANTLY (gliderbac) ---
void hilll_gliderbac(void* localPlayer) {
    if (!localPlayer) return;
    uintptr_t fnOffset = Offset_Startgliderbac;
    if (!fnOffset) return;
    typedef void (*gliderbac_t)(void*);
    gliderbac_t fn = (gliderbac_t)getRealOffset(fnOffset);
    if (fn) fn(localPlayer);
}

// --- HELPER 2: TRIGGER INFINITE GLIDE JUMP ---
void TriggerInfiniteGlide(void* localPlayer) {
    if (!localPlayer) return;
    uintptr_t fnOffset = Offset_StartSAPJumpBeforeGlid;
    if (!fnOffset) return;
    typedef void (*StartSAPJump_t)(void*);
    StartSAPJump_t fn = (StartSAPJump_t)getRealOffset(fnOffset);
    if (fn) fn(localPlayer);
}

// --- FEATURE 1: AUTO GLIDER (FLY X200) ---
void ApplyAutoGlider(void* localPlayer) {
    if (!localPlayer || !autoglid) return;
    TriggerInfiniteGlide(localPlayer);
}

// --- FEATURE 2: INFINITE FLYER ---
void ApplyInfiniteFlyer(void* localPlayer) {
    if (!localPlayer || !infiniteFlyer) return;
    TriggerInfiniteGlide(localPlayer);
    hilll_gliderbac(localPlayer);
}

// --- FEATURE 3: FLY + GLIDER (FLY MOVE) ---
void ApplyFlyMove(void* localPlayer) {
    static bool wasLaunched = false;
    static std::chrono::steady_clock::time_point flyStartTime{};

    if (!localPlayer || get_IsDieing(localPlayer) || !flyMove) {
        wasLaunched = false;
        flyStartTime = {};
        return;
    }

    void* transform = Component_GetTransform(localPlayer);
    if (!transform) return;

    Vector3 pos = GetPosition(transform);

    auto now = std::chrono::steady_clock::now();

    if (!wasLaunched) {
        TriggerInfiniteGlide(localPlayer);
        wasLaunched = true;
        flyStartTime = now;
    }

    Vector3 forwardDir = {0, 0, 0};
    void* mainCam = get_main();
    if (mainCam) {
        void* camTf = Component_GetTransform(mainCam);
        if (camTf) forwardDir = GetForward(camTf);
    }
    if (forwardDir.x == 0 && forwardDir.y == 0 && forwardDir.z == 0) {
        forwardDir = GetForward(transform);
    }

    float speed = 0.6f;
    pos.x += forwardDir.x * speed;
    pos.y += forwardDir.y * speed;
    pos.z += forwardDir.z * speed;

    SetPosition(transform, pos);

    if (flyStartTime.time_since_epoch().count() != 0) {
        long long elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - flyStartTime).count();
        if (elapsedMs >= 3000) {
            TriggerInfiniteGlide(localPlayer);
            hilll_gliderbac(localPlayer);
            flyStartTime = now;
        }
    }
}

// --- FEATURE 4: GLIDER HOLD (WITH GLIDER HEIGHT) ---
void ApplyGliderHold(void* localPlayer) {
    static int gliderHoldStep = 0;
    static std::chrono::steady_clock::time_point step1StartTime{};

    if (!localPlayer || get_IsDieing(localPlayer) || !gliderhold) {
        if (gliderHoldStep == 1) autojump = false;
        gliderHoldStep = 0;
        return;
    }

    auto now = std::chrono::steady_clock::now();

    if (gliderHoldStep == 0) {
        autojump = true;
        step1StartTime = now;
        gliderHoldStep = 1;
    } else if (gliderHoldStep == 1) {
        long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - step1StartTime).count();
        if (ms >= 300) {
            autojump = false;

            void* transform = Component_GetTransform(localPlayer);
            if (transform) {
                Vector3 pos = GetPosition(transform);
                int targetFeet = gliderHeight;
                if (targetFeet < 1)   targetFeet = 1;
                if (targetFeet > 200) targetFeet = 200;
                float meters = targetFeet * 0.3048f;

                pos.y += meters;
                SetPosition(transform, pos);

                TriggerInfiniteGlide(localPlayer);
                hilll_gliderbac(localPlayer);
            }
            gliderHoldStep = 2;
        }
    }
    // step 2 = done, stays until feature toggled off
}

// --- FEATURE 5: TELEPORT ANYWHERE (GLIDER) / SEQUENCE TP ---
static bool   isSequenceRunning = false;
static int    sequenceStep      = 0;
static std::chrono::steady_clock::time_point sequenceStartTime;

// cachedTarget360 — closest enemy used by sequenceTP
// We reuse g_ClosestEnemy which is already updated every frame in _LateUpdate
void ExecuteSequenceTP(void* LocalPlayer) {
    if (!LocalPlayer || !sequenceTP) {
        isSequenceRunning = false;
        sequenceStep = 0;
        return;
    }

    void* ClosestEnemy = g_ClosestEnemy;
    if (!ClosestEnemy) {
        sequenceTP = false;
        isSequenceRunning = false;
        sequenceStep = 0;
        return;
    }

    auto now = std::chrono::steady_clock::now();

    switch (sequenceStep) {
        case 0: // MINI JUMP START
            flyJump = true;
            TriggerInfiniteGlide(LocalPlayer);
            sequenceStartTime = now;
            sequenceStep = 1;
            break;

        case 1: // JUMP OFF + GLIDER ON
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - sequenceStartTime).count() >= 45) {
                flyJump = false;
                gliderbac = true;
                hilll_gliderbac(LocalPlayer);
                sequenceStartTime = now;
                sequenceStep = 2;
            }
            break;

        case 2: // INSTANT TP + AUTO RESET
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - sequenceStartTime).count() >= 70) {
                void* enemyTF = Component_GetTransform(ClosestEnemy);
                if (!enemyTF) {
                    gliderbac = false;
                    sequenceTP = false;
                    isSequenceRunning = false;
                    sequenceStep = 0;
                    return;
                }
                Vector3 enemyPos = GetPosition(enemyTF);

                Vector3 tpPos = enemyPos;
                tpPos.y += 2.2f;
                tpPos.z += 1.3f;

                void* localTF = Component_GetTransform(LocalPlayer);
                if (localTF) SetPosition(localTF, tpPos);

                gliderbac = false;
                sequenceTP = false;
                isSequenceRunning = false;
                sequenceStep = 0;
            }
            break;
    }
}

// --- FEATURE 6: GLIDER TP (TELEPORT TO MAP MARK USING GLIDER) ---
void StartGliderTP() {
    if (!glidertp) return;

    void* match = Curent_Match();
    if (!match) return;
    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer || get_IsDieing(localPlayer)) return;

    void* transform = Component_GetTransform(localPlayer);
    if (!transform) return;

    if (!HasMapMarker) return;

    forceGlideTP = true;

    Vector3 currentPos = GetPosition(transform);
    Vector3 upPos = currentPos;
    upPos.y += 50.0f;
    SetPosition(transform, upPos);

    Vector3 targetPos = SavedMapMarker;
    targetPos.y += 5.0f;
    SetPosition(transform, targetPos);

    forceGlideTP = false;
    glidertp = false;
}

// ============================================================

// Forward declaration
void InvisiblePlie();

// ---------------------------- isGrounded Hook --------------
static bool (*O_get_isGrounded)(void* instance);

bool Hook_get_isGrounded(void* instance) {
    if (Enable && TeleportRing) {
        return false;
    }
    if (FlyHackOP) {
        return true;
    }
    return O_get_isGrounded(instance);
}

// ---------------------------- LATE UPDATE --------------
void (*LateUpdate)(void *player, float gameTime, float deltaTime);


void _LateUpdate(void *player, float gameTime, float deltaTime)
{
    static bool inLateUpdate = false;

    if (inLateUpdate)
        return LateUpdate(player, gameTime, deltaTime);

    inLateUpdate = true;

    if (!Enable || !player)
    {
        inLateUpdate = false;
        LateUpdate(player, gameTime, deltaTime);
        return;
    }
    
    void* match = Curent_Match();
if (!match)
{
    inLateUpdate = false;
    LateUpdate(player, gameTime, deltaTime);
    return;
}

void* localPlayer = GetLocalPlayer(match);
if (!localPlayer)
{
    inLateUpdate = false;
    LateUpdate(player, gameTime, deltaTime);
    return;
}

if (Test1) {
LOGS("IsFootball = %d", get_IsFootball(localPlayer));
LOGS("Football = %p", get_CurFootball(localPlayer));
}

FlipNearbyEnemies(player);
if (!FlipPlayerActive) RestoreFlipEnemies(player);

// Real Invisible
InvisiblePlie();

TryShowEnableAllDialogOnce(Enable);

    {
        static float lastCreditTime = 0.0f;
        static float lastPopupTime = 0.0f;
        static float lastNickTime = 0.0f;
        static bool tipsShown = false;

        void* match = Curent_Match();
        if (match) {
            float now = get_realtimeSinceStartup();

            void* ui = GetUIInGameScene();
            if (ui) {
                if (!tipsShown) {
                    ShowCenterUpTeammateTips(U3DStr(OBFUSCATE("THE LION CHEATS")), 99999.0f);
                    tipsShown = true;
                }

                if (now - lastCreditTime >= 3.0f) {
                    ShowCreditPopup(U3DStr(OBFUSCATE("UPDATED BY LION CHEATS")));
                    lastCreditTime = now;
                }

                if (now - lastPopupTime >= 10.0f) {
                    ShowPopupMessageNoAnim(U3DStr(OBFUSCATE("[ff0000] THE LION [ffffff] CHEATS ")), 1.5f);
                    lastPopupTime = now;
                }
            }

            if (now - lastNickTime >= 2.0f) {
                void* closest = GetClosestEnemy();
                if (closest) {
                    RxmGetNickName(closest);
                }
                lastNickTime = now;
            }
        }
    }



    //================ Underground ================//

    if (Underground)
    {
        void* localTF = Component_GetTransform(localPlayer);

        if (localTF)
        {
            Vector3 localPos = getPosition(localPlayer);

            if (!undergroundHasBaseY)
            {
                undergroundBaseY = localPos.y;
                undergroundHasBaseY = true;
            }

            Transform_INTERNAL_SetPosition(
                localTF,
                Vvector3(
                    localPos.x,
                    undergroundBaseY - UndergroundDepth,
                    localPos.z
                )
            );
        }
    }
    else
    {
        if (undergroundHasBaseY)
        {
            void* localTF = Component_GetTransform(localPlayer);

            if (localTF)
            {
                Vector3 pos = getPosition(localPlayer);

                Transform_INTERNAL_SetPosition(
                    localTF,
                    Vvector3(pos.x, undergroundBaseY, pos.z)
                );
            }
        }

        undergroundHasBaseY = false;
        undergroundBaseY = 0.0f;
    }

    //================ TPWall ================//

    if (TPWall)
    {
        void* camera = Camera_main();

        if (camera)
        {
            void* camTransform = Component_GetTransform(camera);
            void* localTransform = Component_GetTransform(localPlayer);

            if (camTransform && localTransform)
            {
                Vector3 pos = GetPosition(localTransform);
                Vector3 forward = GetForward(camTransform);

                forward.y = 0.0f;
                forward = Vector3::Normalized(forward);

                pos.x += forward.x * 1.2f;
                pos.z += forward.z * 1.2f;

                SetPosition(localTransform, pos);
            }
        }

        TPWall = false;
    }

    //================ NoClip ================//

    if (NoClipActive)
    {
        void* localTF = Component_GetTransform(localPlayer);
        if (localTF)
        {
            void* camera = Camera_main();
            if (camera)
            {
                void* camTransform = Component_GetTransform(camera);
                if (camTransform)
                {
                    Vector3 forward = GetForward(camTransform);

                    float len = sqrtf(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
                    if (len > 0.001f) {
                        forward.x /= len;
                        forward.y /= len;
                        forward.z /= len;
                    } else {
                        forward = {0, 0, 1.0f};
                    }

                    Vector3 currentPos = getPosition(localPlayer);

                    Vector3 newPos = {
                        currentPos.x + forward.x * (NoClipSpeed * deltaTime),
                        currentPos.y + forward.y * (NoClipSpeed * deltaTime),
                        currentPos.z + forward.z * (NoClipSpeed * deltaTime)
                    };

                    Transform_INTERNAL_SetPosition(localTF, Vvector3(newPos.x, newPos.y, newPos.z));
                }
            }
        }
    }

    //================ Fly ================//

    if (FlySasta)
    {
        static auto lastTime = std::chrono::steady_clock::now();

        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - lastTime;

        float deltaTime = elapsedTime.count();
        lastTime = currentTime;

        if (deltaTime > 0.1f)
            deltaTime = 0.1f;

        void* camera = Camera_main();
        if (!camera)
    goto END;

        if (camera)
        {
            void* camTransform = Component_GetTransform(camera);
            void* localTransform = Component_GetTransform(localPlayer);

            if (camTransform && localTransform)
            {
                Vector3 currentPos = GetPosition(localTransform);

                Vector3 forward =
                    Vector3::Normalized(GetForward(camTransform));

                currentPos.x += forward.x * FlySastaSpeed * deltaTime;
                currentPos.y += forward.y * FlySastaSpeed * deltaTime;
                currentPos.z += forward.z * FlySastaSpeed * deltaTime;

                SetPosition(localTransform, currentPos);
            }
        }
    }
    else
    {
        static auto lastTime = std::chrono::steady_clock::now();
        lastTime = std::chrono::steady_clock::now();
    }

    //================ FlyHackOP ================//

    if (FlyHackOP)
    {
        void* transform = Component_GetTransform(localPlayer);
        if (transform)
        {
            Vector3 pos = GetPosition(transform);
            pos.y += 0.10f;
            SetPosition(transform, pos);
        }
    }

    //================ UnderCar ================//

    if (UnderCar)
    {
        void* vehicle = GetVehicleIAmIn(localPlayer);

        if (vehicle)
        {
            void* vehicleTransform = Component_GetTransform(vehicle);

            if (vehicleTransform)
            {
                Vector3 pos = GetPosition(vehicleTransform);

                pos.y -= CarDropDistance;

                SetPosition(vehicleTransform, pos);
            }
        }
    }

    //================ Misc ================//
    
    TestTeleport();
    TestTeleMark();
    RunTeleportRing();
    CoverKillVoid(deltaTime);
    AimMagnetVoid();
    QuickReviveAll();

    //================ GLIDER & TELEPORT ================//

    ApplyAutoGlider(localPlayer);
    ApplyInfiniteFlyer(localPlayer);
    ApplyFlyMove(localPlayer);
    ApplyGliderHold(localPlayer);
    if (gliderbac) hilll_gliderbac(localPlayer);
    ExecuteSequenceTP(localPlayer);
    StartGliderTP();

    //====================================================//

    

if (localPlayer)
{
    void* closestEnemy = nullptr;
    float shortestDistance = 9999.0f;

    MyDictionary* dict =
        *(MyDictionary**)((uintptr_t)match + ListPlayer);

    if (dict && dict->entries)
    {
        void* camera = Camera_main();
        if (!camera)
    goto END;
        
        if (camera)
        {
            void* camTransform = Component_GetTransform(camera);

            if (camTransform)
            {
                Vector3 cameraForward = GetForward(camTransform);

                int total = dict->count;
                if (total > 64)
                    total = 64;

                for (int u = 0; u < total; u++)
                {
                    void* Player = dict->entries->vector[u].value;

                    if (!Player)
                        continue;

                    if (Player == localPlayer)
                        continue;

                    if (get_isLocalTeam(Player))
                        continue;

                    if (IgnoreKnocked && get_IsDieing(Player))
                        continue;

if (!IsInDistance(localPlayer, Player))
                        continue;

                    if (!get_MaxHP(Player))
                        continue;

                    if (AimVisible && !IsVisible(Player))
                        continue;

                    Vector3 playerPos = getPosition(Player);
                    Vector3 localPos = getPosition(localPlayer);

                    Vector3 screenPos =
                        WorldToScreenPoint(camera, playerPos);

                    if (screenPos.z < 1.0f)
                        continue;

                    if (!isFov(
                            Vector3(screenPos.x, screenPos.y),
                            Vector3(g_GlWidth / 2, g_GlHeight / 2),
                            Fov_Aim))
                        continue;

                    float distance =
                        Vector3::Distance(localPos, playerPos);

                    if (distance >= Aimdis)
                        continue;

                    Vector3 targetDir =
                        Vector3::Normalized(playerPos - localPos);

                    float dot =
                        Vector3::Dot(cameraForward, targetDir);

                    if (dot <= 0.02f)
                        continue;

                    float angle =
                        Vector3::Angle(targetDir, cameraForward) * 100.0f;

                    if (angle <= Fov_Aim &&
                        angle < shortestDistance)
                    {
                        shortestDistance = angle;
                        closestEnemy = Player;
                    }
                }
            }
        }
    }
    
    g_ClosestEnemy = closestEnemy;

        if (closestEnemy != nullptr)
        {
        
if (AimbotRage)
{

    void* WeaponHand = GetWeaponOnHand(localPlayer);
    

    if (WeaponHand && closestEnemy)
    {
        if (!isEnemyInRangeWeapon(localPlayer, closestEnemy, WeaponHand))
        {
 
            if (isAutoFiring)
            {
                StopFiring2(WeaponHand);
                isAutoFiring = false;
            }

            goto SKIP_AIMBOT; 
        }
    }


    Vector3 enemyPos = GetHeadPosition(closestEnemy);

    if (AimTarget == 1)
        enemyPos.y -= 0.14f;
    else if (AimTarget == 2)
        enemyPos.y -= 0.25f;
    else if (AimTarget == 3)
        enemyPos.y -= 0.35f;
    else if (AimTarget == 4)
    {
        float enemyHP = GetHp(closestEnemy);
        enemyPos.y -= 0.13f;
        if (enemyHP <= ChestRate) { enemyPos.y -= 0.16f; }
    }

    Vector3 PlayerLocation = CameraMain(localPlayer);

    Quaternion rot = GetRotationToLocation(enemyPos, 0.1f, PlayerLocation);

    bool scope  = get_IsSighting(localPlayer);
    bool firing = get_IsFiring(localPlayer);


    if (AimWhen == 0)
    {
        set_aim(localPlayer, rot);
    }
    else if (AimWhen == 1 && (ignoreFiring || firing))
    {
        set_aim(localPlayer, rot);
    }
    else if (AimWhen == 2 && scope)
    {
        set_aim(localPlayer, rot);
    }
    else if (AimWhen == 3 && (AutoFire || firing || scope))
    {
        set_aim(localPlayer, rot);
    }
}

SKIP_AIMBOT:


if (AimbotRage && AutoFire)
{
    void* target = closestEnemy;

    if (target != nullptr && !get_IsDieing(localPlayer))
    {
        void* WeaponHand = GetWeaponOnHand(localPlayer);
        if (!WeaponHand) goto END;
        
        

 
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - lastAutoShotTime
        ).count();

        if (elapsed >= FireRatee)
        {
            StartFiring2(WeaponHand);
            StartWholeBodyFiring(localPlayer, WeaponHand);

            lastAutoShotTime = now;
            isAutoFiring = true;
        }
    }
}


if (AutoFire2)
{
        void* target = closestEnemy;

        if (target != nullptr && !get_IsDieing(localPlayer))
        {
        
            void* WeaponHand = GetWeaponOnHand(localPlayer);
            if (!WeaponHand)
            goto END;

            if (WeaponHand)
            {
                if (isEnemyInRangeWeapon(localPlayer, target, WeaponHand))
                {
                    auto now = std::chrono::steady_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                        now - lastAutoShotTime
                    ).count();

                    if (elapsed >= FireRatee)
                    {
                    
            StartFiring2(WeaponHand);
                        StartWholeBodyFiring(localPlayer, WeaponHand);

                        lastAutoShotTime = now;
                        isAutoFiring = true;
                    }
                }
                else
                {
                    if (isAutoFiring)
                    {
                        StopFiring2(WeaponHand);
                        isAutoFiring = false;
                    }
                }
            }
        }
    }


    
        }
    }

    // AimKill methods (from Aimkill-Max, lazsource Il2Cpp logic)
    if (Enable && (AimKill || AimKill360 || AimKillSend || SafeAimkill || AutoKillV2 || AimKillCHM9M9))
        RunAimKillMethods(localPlayer, g_ClosestEnemy, match);


END:
    inLateUpdate = false;
    LateUpdate(player, gameTime, deltaTime); 
    return;
}




// Function hooks |-------------------------


// Camera Up
Vector3 (*orig_MKKAFNCNELO)(void* _this, void* player, bool flag);

Vector3 hook_MKKAFNCNELO(void* _this, void* player, bool flag)
{
    Vector3 pos = orig_MKKAFNCNELO(_this, player, flag);

    if (Enable && CameraUp)
    {
        pos.y += 0.5f;
        
    }

    return pos;
}

// Camera Fov Hook
float (*GetCameraHeightRateValue)(void *player);
float _GetCameraHeightRateValue(void *player) { 
    if (player != nullptr) { 
    if (Enable && CameraFov) {
    return CamFovRate;
        }
    }
return GetCameraHeightRateValue(player);
}

// FAST RELOAD
float (*FastReload)(void *instance);

float _FastReload(void *instance) {
    if (instance != NULL) {
        if (Enable && NoReload) {
            return 20.0f;
       }
    }
    return FastReload(instance);
}

// Fast Weapon
bool (*orig_FastWeapon)();

bool hook_FastWeapon()
{
    if (FastW) {
        return false;
    }

    return orig_FastWeapon();
}

// Fast Weapon 2
bool (*get_InSwapWeaponCD)(void* thiz);
bool _get_InSwapWeaponCD(void* thiz) {
    if (FastSwitch) {
        return false;  // bypass swap cooldown
    }
    return get_InSwapWeaponCD(thiz);
}

//GHOST SIMPLE HOOK
bool (*orig_NeedSendMessage)(void* _this, int Value);

bool hook_NeedSendMessage(void* _this, int Value) {
    if (_this != nullptr) {
        if (Enable && GhostHack) {
            return false; 
        }
    }
    return orig_NeedSendMessage(_this, Value);
}


// PC LOGO
void* (*orig_PDJBHMNNOFO)(void* str);

void* hook_PDJBHMNNOFO(void* str)
{
    if (PCLogo) {
        return nullptr;
    }

    return orig_PDJBHMNNOFO(str);
}

bool (*orig_GKCOOPMPOAD)();

bool hook_GKCOOPMPOAD()
{
    if (PCLogo) {
        return true;
    }

    return orig_GKCOOPMPOAD();
}

// 120 FPS
// 120 FPS
bool (*orig_IsHighFPS120Open)(void* _this);

bool hook_IsHighFPS120Open(void* _this) {
    if (FPS) return true;
    return orig_IsHighFPS120Open(_this);  // fix UB sekalian
}


// 144 FPS
bool (*orig_IsHighFPS144Open)(void* _this);

bool hook_IsHighFPS144Open(void* _this) {
    if (FPSS) return true;
    return orig_IsHighFPS144Open(_this);  // fix UB sekalian
}

void UnlockFps() {
    DobbyHook(Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), 
        OBFUSCATE("COW"), 
        OBFUSCATE("GameSettingData"), 
        OBFUSCATE("IsHighFPS120Open"), 0), 
        (void *) hook_IsHighFPS120Open, 
        (void **) &orig_IsHighFPS120Open);

    DobbyHook(Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), 
        OBFUSCATE("COW"), 
        OBFUSCATE("GameSettingData"), 
        OBFUSCATE("IsHighFPS144Open"), 0), 
        (void *) hook_IsHighFPS144Open, 
        (void **) &orig_IsHighFPS144Open);
}

void (*original_CreateLoginReq)(void*, void**);
void Hook_CreateLoginReq(void* _this, void** reqPtr) {
    original_CreateLoginReq(_this, reqPtr);
    if (!Bypass2) return;
    
    
    if (!reqPtr || !*reqPtr) return;

    void* req = *reqPtr;

    void* verStr = *(void**)((uintptr_t)req + 0x24);
    if (verStr) {
        Il2CppString* s = (Il2CppString*)verStr;
        int32_t len = s->length;
        uint16_t* chars = (uint16_t*)((uintptr_t)s + 0x0C);

        int dot1 = -1, dot2 = -1;
        for (int32_t i = 0; i < len; i++) {
            if (chars[i] == '.') {
                if (dot1 == -1) dot1 = i;
                else { dot2 = i; break; }
            }
        }
        if (dot1 >= 0 && dot2 > dot1 + 1) {
            int midVal = 0;
            for (int32_t i = dot1 + 1; i < dot2; i++)
                midVal = midVal * 10 + (chars[i] - '0');
            if (midVal > 0) {
                midVal--;

                int32_t pos = dot2 - 1;
                do {
                    chars[pos--] = '0' + (midVal % 10);
                    midVal /= 10;
                } while (midVal > 0 && pos > dot1);
                while (pos > dot1) chars[pos--] = '0'; // zero-pad: 100→99 → 099
            }
        }
    }

    // ═══ SPOOF: client_version_code (0x108) → "2019118044" ═══
    *(void**)((uintptr_t)req + 0x108) = Il2CppString::Create(OBFUSCATE("2019118045"));

    
}


// ══════════════════════════════════════════════════════════════════
// REAL INVISIBLE (Football exploit)
// ══════════════════════════════════════════════════════════════════
void (*orig_SendFootball)(void*) = nullptr;
void (*orig_CancelFootball)(void*) = nullptr;
static bool resolvedFootball = false;

void InvisiblePlie() {
    if (!RealInvisible) return;

    void* match = Curent_Match();
    if (!match) return;
    void* Local_Player = GetLocalPlayer(match);
    if (!Local_Player) return;

    if (!resolvedFootball) {
        orig_SendFootball = (void(*)(void*))Il2CppGetMethodOffset(
            OBFUSCATE("Assembly-CSharp.dll"),
            OBFUSCATE("COW.GamePlay"),
            OBFUSCATE("PlayerNetwork"),
            OBFUSCATE("SendChangeToGBFootBall"), 0
        );
        orig_CancelFootball = (void(*)(void*))Il2CppGetMethodOffset(
            OBFUSCATE("Assembly-CSharp.dll"),
            OBFUSCATE("COW.GamePlay"),
            OBFUSCATE("PlayerNetwork"),
            OBFUSCATE("SendCancelGBFootBall"), 0
        );
        resolvedFootball = true;
    }

    static bool wasCancelled = false;

    if (RealInvisible) {
        wasCancelled = false;
        if (orig_SendFootball) orig_SendFootball(Local_Player);
    } else {
        if (!wasCancelled) {
            if (orig_CancelFootball) orig_CancelFootball(Local_Player);
            wasCancelled = true;
        }
    }
}


// Load Hooks Memory
// ── HideDamage ─────────────────────────────────────────────────────
void (*orig_ShowDamage)(void* thiz, int damage, void* colliderT, void* p, int shieldDamage, int weaponID, float delay);
void hook_ShowDamage(void* thiz, int damage, void* colliderT, void* p, int shieldDamage, int weaponID, float delay) {
    if (HideDamage) {
        return;
    }
    orig_ShowDamage(thiz, damage, colliderT, p, shieldDamage, weaponID, delay);
}

bool (*orig_get_ShowDamageNum)(void* thiz);
bool hook_get_ShowDamageNum(void* thiz) {
    if (HideDamage) {
        return false;
    }
    return orig_get_ShowDamageNum(thiz);
}

void InitAllHooks()
{
    if (HooksInitialized)
        return; 
        
        // Late Update
        DobbyHook(Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"),
        OBFUSCATE("COW.GamePlay"),
        OBFUSCATE("Player"),
        OBFUSCATE("UpdateBehavior"), 2),
        (void *) _LateUpdate,
        (void **) &LateUpdate);

        // isGrounded Hook (FlyHackOP)
        DobbyHook((void*) Il2CppGetMethodOffset(
        OBFUSCATE("UnityEngine.PhysicsModule.dll"),
        OBFUSCATE("UnityEngine"),
        OBFUSCATE("CharacterController"),
        OBFUSCATE("get_isGrounded"), 0),
        (void*)Hook_get_isGrounded,
        (void**)&O_get_isGrounded);
        
        // CAMERA FOV HOOK
        DobbyHook(Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), 
        OBFUSCATE("COW.GamePlay"), 
        OBFUSCATE("FollowCamera"), 
        OBFUSCATE("get_OffsetForNormal"), 0),
        (void *)_GetCameraHeightRateValue, 
        (void **)&GetCameraHeightRateValue);
        
            // NoReload Hook
        DobbyHook(
        (void*)Il2CppGetMethodOffset(
            OBFUSCATE("Assembly-CSharp.dll"),
            OBFUSCATE("COW.GamePlay"),
            OBFUSCATE("FDAEPHMIEPC"),
            OBFUSCATE("JOEKFHCNHCL"),
            0
        ),
        (void*)_FastReload,
        (void**)&FastReload
    );
            
            // Fast Weapon
        DobbyHook(
        (void*)Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"),
        OBFUSCATE("COW.GamePlay"),
        OBFUSCATE("Player"),
        OBFUSCATE("get_IsDuringSkyDivingSwitch"),
            0
        ),
        (void*)hook_FastWeapon,
        (void**)&orig_FastWeapon
    );
    
            // Camera XYZ (Up)
        DobbyHook(
            (void*)offset_MKKAFNCNELO,
            (void*)hook_MKKAFNCNELO,
            (void**)&orig_MKKAFNCNELO
        );
        

               // PC LOGO
        if (offset_PDJBHMNNOFO != 0) {
        DobbyHook(
            (void*)offset_PDJBHMNNOFO,
            (void*)hook_PDJBHMNNOFO,
            (void**)&orig_PDJBHMNNOFO
        );
    }

    if (offset_GKCOOPMPOAD != 0) {
        DobbyHook(
            (void*)offset_GKCOOPMPOAD,
            (void*)hook_GKCOOPMPOAD,
            (void**)&orig_GKCOOPMPOAD
        );
    }
    

        
        // Ghost HOOK
        if (offset_NeedSendMessage != 0) {
        DobbyHook(
            (void *)offset_NeedSendMessage,
            (void *)hook_NeedSendMessage,
            (void **)&orig_NeedSendMessage
        );
    }
    
        // MARK ON MAP POSITION  
        DobbyHook(
            (void*)offset_UpdateLocalMark,
            (void*)hook_UpdateLocalMark,
            (void**)&orig_UpdateLocalMark
        );
        
        // SWAP WEAPON
        DobbyHook(
    (void*)Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"),
        OBFUSCATE("COW.GamePlay"),
        OBFUSCATE("Player"),
        OBFUSCATE("get_InSwapWeaponCD"),
        0),
    (void*)_get_InSwapWeaponCD,
    (void**)&get_InSwapWeaponCD);
    
    
    // Silent Kill
    
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("KOODEKEKFEK"), 1), (void *) KOODEKEKFEK1,(void **) &old_KOODEKEKFEK1);
        
        
        
        DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("TakeDamage"), 9), (void *) &hook_PlayerNetwork_TakeDamage, (void **) &orig_PlayerNetwork_TakeDamage);
        
        
        // HideDamage Hooks
        DobbyHook((void*)Il2CppGetMethodOffset(
            OBFUSCATE("Assembly-CSharp.dll"),
            OBFUSCATE("COW.GamePlay"),
            OBFUSCATE("Player"),
            OBFUSCATE("get_ShowDamageNum"), 0),
            (void*)hook_get_ShowDamageNum,
            (void**)&orig_get_ShowDamageNum);

        DobbyHook((void*)Il2CppGetMethodOffset(
            OBFUSCATE("Assembly-CSharp.dll"),
            OBFUSCATE("COW.HUD"),
            OBFUSCATE("UIHudNameController"),
            OBFUSCATE("ShowDamage"), 6),
            (void*)hook_ShowDamage,
            (void**)&orig_ShowDamage);

        // L0GIN BlPASS

		
		if (OFFSET_CreateLoginReq != 0) {
            DobbyHook((void*)OFFSET_CreateLoginReq, (void*)Hook_CreateLoginReq, (void**)&original_CreateLoginReq);
     }
     
        
        InitBoneOffsets();
        
        


    HooksInitialized = true;
}
bool Guest = false;
bool (*ResetGuest)(void* _this);
bool _ResetGuest(void* _this) {
    if (Guest) {return true;}
    return ResetGuest(_this);
}
