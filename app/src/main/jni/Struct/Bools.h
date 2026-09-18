#pragma once
uintptr_t il2cpp_base = 0;
float HPFontSize = 13.0f;

// my bools
bool CameraFov = false;
bool AimbotRage = false;
bool Teleport = false;
bool TeleMark = false;
bool AimVisible = true;
bool IgnoreKnocked = true;
bool Sooo = true;
bool HideFov = false;
bool SpeedTimer = false;
bool ShowHP = false;
bool EnemyCount = false;
bool TargetLine = false;
bool CameraUp = false;
bool PCLogo = false;
bool FPS = false;
bool FPSS = false;
bool NoReload = false;
bool GhostHack = false;
bool AimbotLegit = false;
bool AimSilent = false;
bool AimSilent2 = false;
bool MagnetLite = false;
bool AimMagnet = false;
bool AutoFire = false;
bool FastW = false;
bool CamLeft = false;
bool Underground = false;
bool Bypass400 = false;
bool TPWall = false;
bool Rotatee = false;
bool Bypass2 = false;
bool Bypass600 = false;
bool TeleportCar = false;
bool UnderCar = false;
bool CoverKill = false;
bool FlySasta = false;
float FlySastaSpeed = 15.0f;
bool FlyHackOP = false;
bool TeleportRing = false;
float TeleportRingYOffset = 2.5f;
bool AutoRevive = false;
bool Rotate2 = false;
bool WinFlipPlayer = false;
bool FlipPlayerActive = false;
bool DownKill = false;
bool AutoFire2 = false;
bool TeleRevive = false;
bool ChestShot = false;
bool GameTimer = false;
bool PullKnocked = false;
bool FixDamage = false;
bool FastSwitch = false;

bool Test1 = false;
bool Test2 = false;

// ============================================================
// GLIDER & TELEPORT BOOLS
// ============================================================
bool autoglid      = false;
bool glidertp      = false;
bool infiniteFlyer = false;
bool gliderbac     = false;
bool gliderhold    = false;
bool flyMove       = false;
bool sequenceTP    = false;
int  gliderHeight  = 80;

// internal helpers (not exposed in menu)
bool autojump       = false;
bool flyJump        = false;
bool forceGlideTP   = false;


// ToggleWindows
bool ChamsMenu = false;
bool WinSpeed = false;
bool WinGhost = false;
bool WinTele = false;
bool WinMark = false;
bool WinFlyrun = false;
bool WinUnder = false;
bool WinTPWall = false;
bool WinSasta = false;
bool WinFlyHack = false;
bool WinTeleportRing = false;
bool WinTV = false;
bool WinEnable = false;
// others
float Fov_Aim = 360.0f;
float Aimdis = 360.0f;
float CamFovRate = 3.5f;

bool Enable;
int AimCheck = 0;
int AimType = 0;
int AimWhen = 3;
int AimTarget = 0;



bool AimActivar,AimCrouch;
float AimDistance;
bool esp;
float Size = 1000;
float AimDis;
float MoveSpeed;
bool Tele;
bool check_move = false;
bool AimKill = false;
bool AimKill360 = false;
bool AimKillSend = false;
bool SafeAimkill = false;
bool AutoKillV2 = false;
bool HideDamage = false;
bool AimKillCHM9M9 = false;
bool AimKillHitFly = false;
bool AutoSwitch = false;
int AutoSwitchSpeed = 150;
bool Headshot = false;
bool Autoswap;
bool AutoCharge;
bool ActiveFeature = true;
bool AimVisible2 = true;
int countEnemy = 0;
int SwapDelay = 200;
float AimFov2 = 360.0f;
float DistanceTele = 0;

bool isInsideFOV(int x, int y) {
    if (!Size)
        return true;

    int circle_x = g_GlWidth / 2;
    int circle_y = g_GlHeight / 2;
    int rad = Size;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

void *enemyPlayer = NULL;;
void *myPlayer = NULL;
bool aimskill;
            
ImColor Esp_Box = ImColor(255,255,255,229);
ImColor Esp_Grad1 = ImColor(255,255,255,229);
ImColor Esp_Grad2 = ImColor(255,255,255,229);
ImColor Esp_3DBox = ImColor(255,255,255,229);
ImColor Esp_Fled = ImColor(255,255,255,150);
ImColor Esp_Text = ImColor(255,255,255,229);
ImColor Esp_Dist = ImColor(255,255,255,229);
ImColor Esp_Filed = ImColor(255,255,255,150);
ImColor Esp_Skel = ImColor(0255,255,255,150);
ImColor Esp_He= ImColor(255,255,255,150);
ImColor Hp = ImColor(0, 255, 0); 
ImColor White = ImColor(255, 255, 255); 


ImColor die = ImColor(255,0,0);
ImColor hp = ImColor(0,255,0,255);




const char* dir[] = {"Lock","Fire","Scope","Fire&Scope"};

const char* AimPos[] = { "Head", "Neck", "Chest", "Hip", "Drag" };
float ChestRate = 80.0f; // For Drag

int is_SpeedTime;
float visual_circle_size,visual_circle_stroke,visual_lined_size,visual_lined_stroke,visual_esp_line = 1,visual_esp_box = 1,visual_esp_boxth = 0.8,visual_esp_box_filedth = 1,visual_esp_box_filed = 1,visual_esp_skel = 1;
int visual_esp_line_type = 0;

bool Aimbot;
std::string int_to_string(int num)
{
     std::string str = std::to_string(num);
     return str;
}


bool isFov(Vector3 vec1, Vector3 vec2, int radius) {
    int x = vec1.x;
    int y = vec1.y;

    int x0 = vec2.x;
    int y0 = vec2.y;
    if ((pow(x - x0, 2) + pow(y - y0, 2) ) <= pow(radius, 2)) {
        return true;
    } else {
        return false;
    }
}


// COLORS CONFIG
ImVec4 FovColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); 
ImVec4 EspLineColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
ImVec4 EspBoxColor = ImVec4(1.0f, 1.0f, 1.0f, 0.8f);
ImVec4 EspFullBoxColor = ImVec4(0.85f, 0.85f, 0.85f, 0.40f); 
ImVec4 TargetLineColor = ImVec4(255, 0, 0, 255);
ImVec4 ChamsColor = ImVec4(0, 255, 253, 255);

ImVec4 SkeletonColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


 // ESP CONFIG
int LineBaseMode = 0;
const char* LineBase[] = { "Top", "Bottom" };

int BoxStyleMode = 0;
const char* BoxStyle[] = { "NormalBox", "FullBox", "Both" };


int MagnetTarget = 1; // 0 Head | 1 Chest | 2 Hip
const char* MagnetPos[] = { "Head", "Chest", "Hip" };


int SilentTarget = 0;
const char* SilentPos[] = { "Head", "Chest", "Drag"};
float SilentChestRate = 150;

int FireRatee = 170;

// Real Invisible
bool RealInvisible = false;

bool WinNoClip = false;
bool NoClipActive = false;
float NoClipSpeed = 50.0f;

// 1. المتغير العام (Global) والمؤقت الزمني

bool MocoMark   = false;
float MocoRadius = 200.0f;
