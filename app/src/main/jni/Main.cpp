#include <android/log.h>
#include <unistd.h>
#include <thread>
#include <limits>
#include <xdl.h>
#include <KittyUtils.h>
#include <KittyMemory.h>
#include <Il2Cpp.h>
#include <SubstrateHook.h>
#include <CydiaSubstrate.h>
#include "Struct/Gui.hpp"
#include "Struct/MemoryPatches.h"
#include <Struct/main.h>
#include "fonts/FontAwesome6_solid.h"
#include "zygisk.hpp"
#include <jni.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/lion.h"
#include "Chams.h"
#include "Struct/Moco.h"
#include "exptime.h"
#include "imGui/stb_image.h"

// ZYGISK CONFIG
void (*OpenURL)(String *url);
void hack();

extern JavaVM* jvm;
extern JNIEnv* genv;

#include <pthread.h>
#include <signal.h>

void* safe_hack_thread(void* arg) {
    sleep(4);
    try {
        hack();
    } catch (...) {}
    return nullptr;
}

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void *reserved) {
    jvm = vm;
    JNIEnv* env = nullptr;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) == JNI_OK)
        genv = env;

    pthread_t t;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&t, &attr, safe_hack_thread, nullptr);
    pthread_attr_destroy(&attr);

    return JNI_VERSION_1_6;
}

static double TeleportTime = 0.0;
int TeleportOffTimer = 0;

GLuint LazTexture = 0;
bool LazTextureLoaded = false;

void LoadLazTexture() {
    if (LazTextureLoaded) return;
    int width, height, channels;
    glGenTextures(1, &LazTexture);
    glBindTexture(GL_TEXTURE_2D, LazTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    LazTextureLoaded = true;
}

static bool HideFullMenu = false;
static bool fourFingerPressed = false;
static bool CloseGui = false;
static bool HideGui = false;
bool BlockUnityTouch = false;

// Custom UI Theme Configurator
void ApplyCyberpunkDarkTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    
    style.WindowPadding     = ImVec2(14, 12);
    style.FramePadding      = ImVec2(10, 6);
    style.ItemSpacing       = ImVec2(10, 8);
    style.WindowRounding    = 12.0f;
    style.FrameRounding     = 6.0f;
    style.GrabRounding      = 6.0f;
    style.ScrollbarRounding = 8.0f;
    style.WindowBorderSize  = 1.0f;
    style.FrameBorderSize   = 1.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]           = ImVec4(0.07f, 0.08f, 0.12f, 0.95f);
    colors[ImGuiCol_Border]             = ImVec4(0.00f, 0.80f, 1.00f, 0.35f);
    colors[ImGuiCol_FrameBg]            = ImVec4(0.12f, 0.14f, 0.20f, 0.80f);
    colors[ImGuiCol_FrameBgHovered]     = ImVec4(0.18f, 0.22f, 0.32f, 0.90f);
    colors[ImGuiCol_FrameBgActive]      = ImVec4(0.24f, 0.28f, 0.40f, 1.00f);
    colors[ImGuiCol_TitleBg]            = ImVec4(0.05f, 0.06f, 0.09f, 1.00f);
    colors[ImGuiCol_TitleBgActive]      = ImVec4(0.08f, 0.10f, 0.15f, 1.00f);
    colors[ImGuiCol_Button]             = ImVec4(0.00f, 0.60f, 0.90f, 0.35f);
    colors[ImGuiCol_ButtonHovered]      = ImVec4(0.00f, 0.70f, 1.00f, 0.65f);
    colors[ImGuiCol_ButtonActive]       = ImVec4(0.00f, 0.85f, 1.00f, 0.90f);
    colors[ImGuiCol_Header]             = ImVec4(0.00f, 0.60f, 0.90f, 0.25f);
    colors[ImGuiCol_HeaderHovered]      = ImVec4(0.00f, 0.70f, 1.00f, 0.45f);
    colors[ImGuiCol_HeaderActive]       = ImVec4(0.00f, 0.80f, 1.00f, 0.70f);
    colors[ImGuiCol_SliderGrab]         = ImVec4(0.00f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]   = ImVec4(0.30f, 0.90f, 1.00f, 1.00f);
    colors[ImGuiCol_Text]               = ImVec4(0.92f, 0.95f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]       = ImVec4(0.45f, 0.50f, 0.60f, 1.00f);
}

// Custom Toggle Switch (Replaces regular Checkbox)
bool CustomToggle(const char* label, bool* v) {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight();
    float width = height * 1.8f;
    float radius = height * 0.5f;

    ImGui::InvisibleButton(label, ImVec2(width + ImGui::CalcTextSize(label).x + 10.0f, height));
    bool clicked = ImGui::IsItemClicked();
    if (clicked) *v = !*v;

    float t = *v ? 1.0f : 0.0f;
    ImU32 bg_col = *v ? IM_COL32(0, 195, 255, 255) : IM_COL32(40, 45, 60, 255);

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), bg_col, radius);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 2.0f, IM_COL32(255, 255, 255, 255));
    draw_list->AddText(ImVec2(p.x + width + 10.0f, p.y + (height - ImGui::GetFontSize()) * 0.5f), IM_COL32(230, 235, 245, 255), label);

    return clicked;
}

UnityEngine_Touch_Fields (*old_GetTouch)(int index);

UnityEngine_Touch_Fields hook_GetTouch(int index) {
    if (BlockUnityTouch) {
        UnityEngine_Touch_Fields fake{};
        fake.m_Phase = TouchPhase::Canceled;
        return fake;
    }
    return old_GetTouch(index);
}

void *getRealAddr(ulong offset) {
    return reinterpret_cast<void*>(il2cpp_base + offset);
}

namespace Settings {
    static int Tab = 1;
}

bool clearMousePos = true;
bool initImGui = false;

inline EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &g_GlWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &g_GlHeight);

    if (!g_IsSetup) {
        prevWidth = g_GlWidth;
        prevHeight = g_GlHeight;
        SetupImgui();
        g_IsSetup = true;
    }
    
    static bool LastUnderground = false;
    static bool LastAutoFire = false;
    static bool LastAutoFire2 = false;

    if (LastUnderground != Underground) {
        Rotate2 = Underground;
        LastUnderground = Underground;
    }

    if (AutoFire && !LastAutoFire) AutoFire2 = false;
    else if (AutoFire2 && !LastAutoFire2) AutoFire = false;

    LastAutoFire = AutoFire;
    LastAutoFire2 = AutoFire2;

    static bool LastAimKill = false, LastAimKill360 = false, LastAimKillSend = false;
    static bool LastSafeAimkill = false, LastAimKillCHM = false, LastAutoKillV2 = false;
    if (AimKill && !LastAimKill) { AimKill360 = AimKillSend = SafeAimkill = AimKillCHM9M9 = AutoKillV2 = false; }
    else if (AimKill360 && !LastAimKill360) { AimKill = AimKillSend = SafeAimkill = AimKillCHM9M9 = AutoKillV2 = false; }
    else if (AimKillSend && !LastAimKillSend) { AimKill = AimKill360 = SafeAimkill = AimKillCHM9M9 = AutoKillV2 = false; }
    else if (SafeAimkill && !LastSafeAimkill) { AimKill = AimKill360 = AimKillSend = AimKillCHM9M9 = AutoKillV2 = false; }
    else if (AutoKillV2 && !LastAutoKillV2) { AimKill = AimKill360 = AimKillSend = SafeAimkill = AimKillCHM9M9 = false; }
    else if (AimKillCHM9M9 && !LastAimKillCHM) { AimKill = AimKill360 = AimKillSend = SafeAimkill = AutoKillV2 = false; }
    LastAimKill = AimKill; LastAimKill360 = AimKill360; LastAimKillSend = AimKillSend;
    LastSafeAimkill = SafeAimkill; LastAimKillCHM = AimKillCHM9M9; LastAutoKillV2 = AutoKillV2;

    ImGuiIO &io = ImGui::GetIO();
    ApplyCyberpunkDarkTheme();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(g_GlWidth, g_GlHeight);
    ImGui::NewFrame();

    int touchCount = (((int (*)())(Class_Input__get_touchCount))());
    if (touchCount >= 4) {
        if (!fourFingerPressed) {
            HideFullMenu = !HideFullMenu;
            fourFingerPressed = true;
        }
    } else {
        fourFingerPressed = false;
    }

    if (touchCount > 0) {
        UnityEngine_Touch_Fields touch = old_GetTouch(0);
        float reverseY = io.DisplaySize.y - touch.m_Position.fields.y;

        if (touch.m_Phase == TouchPhase::Began ||
            touch.m_Phase == TouchPhase::Moved ||
            touch.m_Phase == TouchPhase::Stationary) {
            io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
            io.MouseDown[0] = true;
        } else {
            UpdateSpeedhack();
            io.MouseDown[0] = false;
        }
    } else {
        io.MouseDown[0] = false;
    }

    BlockUnityTouch = io.WantCaptureMouse;
    DrawESP(g_GlWidth, g_GlHeight);

    // Dynamic UI State Variables
    static bool isCollapsed = false;

    if (!HideFullMenu) {
        ExpireDate exp;
        exp.setExpirationDate(25, 9, 2030);

        if (exp.isExpired()) {
            ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
            ImGui::Begin("EXPIRATION NOTICE", nullptr, ImGuiWindowFlags_NoCollapse);
            ImGui::Text(ICON_FA_USER_SECRET " MODE EXPIRED");
            ImGui::Separator();
            ImGui::Text("Join channel for latest updates.");
            if (ImGui::Button(ICON_FA_EYE " JOIN TELEGRAM", ImVec2(-1, 45))) {
                OpenURL(Il2CppString::Create(OBFUSCATE("https://t.me/PRABIRLIVE")));
            }
            ImGui::End();
        } else {
            ImGui::SetNextWindowSize(ImVec2(520, isCollapsed ? 52 : 360), ImGuiCond_Always);
            
            // MAIN ENGINE MENU WINDOW (Direct ImGui::Begin without titlebar)
            ImGui::Begin(OBFUSCATE("THE LION CHEATS V1"), nullptr, 
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoScrollbar);

            // HEADER ROW (TITLE + RIGHT ALIGNED COLLAPSE BUTTON)
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
            ImGui::TextColored(ImVec4(0.0f, 0.82f, 1.0f, 1.0f), "THE LION CHEATS");

            ImGui::SameLine(ImGui::GetContentRegionAvail().x - 24);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2);
            if (ImGui::Button(isCollapsed ? "+" : "-", ImVec2(28, 24))) {
                isCollapsed = !isCollapsed;
            }

            // MAIN CONTENT (Renders when Expanded)
            if (!isCollapsed) {
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                if (ImGui::BeginTabBar("MainTabs", ImGuiTabBarFlags_FittingPolicyResizeDown)) {
                    
                    // AIM MENU
                    if (ImGui::BeginTabItem(" AIMBOT ")) {
                        ImGui::Spacing();
                        CustomToggle("Enable Aimbot System", &Aimbot);
                        CustomToggle("Aimbot Rage Mode", &AimbotRage);
                        CustomToggle("Visibility Check", &AimVisible);
                        ImGui::Spacing();
                        ImGui::PushItemWidth(-1);
                        ImGui::SliderFloat("##AimFov", &Fov_Aim, 0.0f, 360.0f, "FOV: %.0f°");
                        ImGui::PopItemWidth();
                        ImGui::EndTabItem();
                    }

                    // ESP MENU
                    if (ImGui::BeginTabItem(" VISUALS ")) {
                        ImGui::Spacing();
                        CustomToggle("ESP Line", &Config.ESP.Line);
                        CustomToggle("ESP Box", &Config.ESP.Box);
                        CustomToggle("ESP Info", &Config.ESP.Infos);
                        CustomToggle("Target Distance", &TargetLine);
                        CustomToggle("ESP Health Bar", &Config.ESP.Health);
                        CustomToggle("Show HP Text", &ShowHP);
                        CustomToggle("ESP Skeleton", &EspSkeleton);
                        CustomToggle("Enemy Counter", &EnemyCount);
                        ImGui::EndTabItem();
                    }

                    // CHAMS MENU
                    if (ImGui::BeginTabItem(" CHAMS ")) {
                        ImGui::Spacing();
                        CustomToggle("Wireframe View", &wireframe);
                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }
            }

            ImGui::End();
        }
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return old_eglSwapBuffers(dpy, surface);
}

typedef unsigned long DWORD;
static uintptr_t libBase;

inline void StartGUI() {
    void *ptr_eglSwapBuffer = DobbySymbolResolver("/system/lib/libEGL.so", "eglSwapBuffers");
    if (ptr_eglSwapBuffer != nullptr) {
        DobbyHook((void *)ptr_eglSwapBuffer, (void *)hook_eglSwapBuffers, (void **)&old_eglSwapBuffers);
        LOGD("GUI started successfully");
    }
}

bool (*old_SendMessageToLobby)(void* instance, int cmdType, uint32_t subCmdType, void* message, uint8_t regionID, bool ignoreDisconnetWnd);

bool hook_SendMessageToLobby(void* instance, int cmdType, uint32_t subCmdType, void* message, uint8_t regionID, bool ignoreDisconnetWnd) {
    if (cmdType == 29 || cmdType == 40 || cmdType == 52 || cmdType == 24) {
        LOGD("[LUNAR] Blocked Anti-Cheat / Telemetry Packet cmdType: %d", cmdType);
        return true; 
    }
    return old_SendMessageToLobby(instance, cmdType, subCmdType, message, regionID, ignoreDisconnetWnd);
}

void hack_thread(pid_t pid) {
    LOGD("Hack Thread initiated for PID: %i", pid);

    for (int i = 0; i < 10; i++) {
        il2cpp_base = get_module_base(pid, "libil2cpp.so");
        if (il2cpp_base != 0) break;
        sleep(9);
    }

    if (il2cpp_base == 0) {
        LOGE("libil2cpp.so not found in thread %d", pid);
        std::terminate();
    }

    LOGD("IL2CPP base address: 0x%" PRIxPTR, il2cpp_base);
    sleep(9);

    Il2CppAttach();

    if (Class_Input__GetTouch) {
        DobbyHook(
            (void *)Class_Input__GetTouch,
            (void *)hook_GetTouch,
            (void **)&old_GetTouch
        );
    }

    void* glesHandle = nullptr;
    while (!glesHandle) {
        glesHandle = dlopen("libGLESv2.so", RTLD_LAZY);
        sleep(1);
    }

    handle = glesHandle;

    static bool chamsInit = false;
    if (!chamsInit && mlovinit()) {
        LogShaders();
        WallhackChams();
        chams_ready = true;
        chamsInit = true;
    }
    InitAllHooks();

    void* method_SendMessageToLobby = (void*)Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"),
        OBFUSCATE("COW"),
        OBFUSCATE("ServiceConnectionManager"),
        OBFUSCATE("SendMessageToLobby"),
        5
    );
    if (method_SendMessageToLobby) {
        DobbyHook(
            method_SendMessageToLobby,
            (void*)hook_SendMessageToLobby,
            (void**)&old_SendMessageToLobby
        );
        LOGD("[LUNAR] SendMessageToLobby hook installed successfully!");
    }

    StartGUI();

    OpenURL = (void (*)(String *))Il2CppGetMethodOffset("UnityEngine.CoreModule.dll","UnityEngine","Application","OpenURL",1);

    while (true) {
        UpdateSpeedhack();
        AutoSwitchLoop();
        Moco::Tick();

        if (AspectHack) UpdateAspect();

        static bool fpsHooked = false;
        if (FPS && !fpsHooked) {
            UnlockFps();
            fpsHooked = true;
        }

        usleep(14000);
    }
}

void hack() {
    LOGD("Inject Ok");
    std::thread thread_hack(hack_thread, getpid());
    thread_hack.detach();
}
