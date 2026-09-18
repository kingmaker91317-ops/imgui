#pragma once
class Vvector3 {
public:
    float X;
    float Y;
    float Z;
    Vvector3() : X(0), Y(0), Z(0) {}
    Vvector3(float x1, float y1, float z1) : X(x1), Y(y1), Z(z1) {}
    Vvector3(const Vvector3 &v);
    ~Vvector3();
};

Vvector3::Vvector3(const Vvector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
Vvector3::~Vvector3() {}

#define Class_Camera__get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"))


#define Class_Input__get_touchCount (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_touchCount"))
#define Class_Input__GetTouch (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("GetTouch"), 1)
#define Class_Input__get_mousePosition (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_mousePosition"))

//Class Screen -> UnityEngine.dll
#define Class_Screen__get_width (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_width"))
#define Class_Screen__get_height (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_height"))
#define Class_Screen__get_density (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_dpi"))


#define ForWard (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)

#define Class_Transform__GetPosition Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position_Injected"), 1)

#define Class_Transform__SetPosition Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_position_Injected"), 1)

#define Class_Camera__get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"))
#define Class_Camera__WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)

#define Class_Component__get_transform (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
#define Class_Transform__get_position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)


#define Class_Transform__Rotation Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_rotation"), 0)


#define Class_Compent__Transform Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
//Class Player

 #define Camera_get_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", "get_fieldOfView")
#define Camera_set_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", "set_fieldOfView", 1)

void *get_main() {
    return reinterpret_cast<void *(__fastcall *)()>(Class_Camera__get_main)();
}


float get_fieldOfView() {
    return reinterpret_cast<float(__fastcall *)(void *)>(Camera_get_fieldOfView)(get_main());
}

void *set_fieldOfView(float value) {
    return reinterpret_cast<void *(__fastcall *)(void *, float)>(Camera_set_fieldOfView)(get_main(), value);
}

static void Transform_INTERNAL_SetPosition(void *player, Vvector3 inn) {
    void (*Transform_INTERNAL_SetPosition)(void *transform, Vvector3 in) = (void (*)(void *, Vvector3))(Class_Transform__SetPosition);
    Transform_INTERNAL_SetPosition(player, inn);
}

static Quaternion GetRotation(void* player) {
    Quaternion (*_GetRotation)(void* players) = (Quaternion(*)(void *))(Class_Transform__Rotation);
    return _GetRotation(player);
}


#define Class_Camera__WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)

#define Class_Component__get_transform (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
#define Class_Transform__get_position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)

#define Class_Transform__Position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)

#define Class_Compent__Transform Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)


//Class Player Need Update
#define ListPlayer (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("JMAGGLCNGIG"), OBFUSCATE("DKCLHINMMFO")) 


// EMKJHAJNPDH
// MMECELKLHFC


#define EnemyUpdate (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("LateUpdate"), 0)


#define m_Timer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentGameSimulationTimer"), 0)
static void* GetSimulationTimer() {
    void* (*_GetSimulationTimer) () = reinterpret_cast<void* (*)()>(m_Timer);
    return _GetSimulationTimer();
}

// ============================================================
// GLIDER & TELEPORT OFFSETS
// ============================================================
#define Offset_StartSAPJumpBeforeGlid (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("StartSAPJumpBeforeGlid"), 0)
#define Offset_StartInSAPFlyJumping   Offset_StartSAPJumpBeforeGlid
#define Offset_Startgliderbac         (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("StartSAPGlid"), 0)

#define m_GetTimer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TimeService"), OBFUSCATE("get_FixedDeltaTime"), 0)
static float GetTimer(void* timeServiceInstance) {
    using fnGetFixedDelta = float(*)(void*);
    auto _GetTimer = reinterpret_cast<fnGetFixedDelta>(m_GetTimer);
    return _GetTimer(timeServiceInstance);
}

#define m_SetTimer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TimeService"), OBFUSCATE("UseFixedDeltaTime"), 1)
static void SetTimer(void* timeServiceInstance, float fixedDelta) {
    using fnSetFixed = void(*)(void*, float);
    auto _set_fixed = reinterpret_cast<fnSetFixed>(m_SetTimer);
    _set_fixed(timeServiceInstance, fixedDelta);
}




#define MainCam (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("MainCameraTransform"))


#define Match (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentMatch"), 0)

#define Local (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudDetectorController"), OBFUSCATE("GetLocalPlayer"), 0)


#define Visible (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsVisible"), 0)

#define Team (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsLocalTeammate"), 1)

// before 	public virtual Boolean IsLocalTeammate(Boolean BMEJMCHBLDA) { }
// after 	public virtual bool IsLocalTeammate(bool EPNFBEJFGPE = false) { }


#define Die (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsDieing"), 0)

#define CurHP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_CurHP"), 0)


#define MaxHP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_MaxHP"), 0)

#define Name (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_NickName"), 0)

#define Aim (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("PNODBGHFBOF"), 1) // updated

// ADHOBODJNED


#define Scope (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsSighting"),0 )

#define Fire (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsFiring"), 0)

#define LocalBool (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsLocalPlayer"), 0)

#define CarLocal (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("VehicleIAmIn"), 0)

#define GetCar (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsDriver"), 0)

#define Head (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetHeadTF"), 0)

#define ForWard (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)


#define CharGet (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("mscorlib.dll"), OBFUSCATE("System"), OBFUSCATE("String"), OBFUSCATE("get_Chars"), 1)

#define Team (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "COW.GamePlay", "Player", "IsLocalTeammate", 1)
#define m_ShortIDToPlayers (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "COW.GamePlay", "EMKJHAJNPDH", "MMECELKLHFC")

// EMKJHAJNPDH
// MMECELKLHFC

#define Raycast (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("IPBGFJNGLOH"), OBFUSCATE("FFLLOGJDGOJ"), 4)


// HPFKOGPDBBE
// FOHHPOKDOND

#define Hip (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetHipTF"), 0)

#define HeadColider (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_HeadCollider"), 0)

#define Time (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Time"), OBFUSCATE("get_deltaTime"), 0)
static void *GetHipPositions(void *player) {
    void *(*_GetHipPositions)(void *players) = (void*(*)(void *))(Hip);
     return _GetHipPositions(player);
}
 Vector3 get_position(void *player) {
    Vector3 (*_get_position)(void *players) = (Vector3 (*)(void *))(Class_Transform__Position);
    return _get_position(player);
}

static Vector3 GetHipPosition(void* player) {
    return get_position(GetHipPositions(player));
}

static void *Player_GetHeadCollider(void *player) {
    void *(*_Player_GetHeadCollider)(void *players) = (void *(*)(void *))(HeadColider);
    return _Player_GetHeadCollider(player);
}

#define LAimCollider (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("AttackableEntity"), OBFUSCATE("set_LockedAimingCollider"), 1)
static void SetAimCollider(void* enemy, void* collider) {
    using fnSetCollider = void(*)(void*, void*);
    auto _set_collider = reinterpret_cast<fnSetCollider>(LAimCollider);
    _set_collider(enemy, collider);
}


static void *GetLocalPlayer(void* Game) {
    void *(*_GetLocalPlayer)(void *match) = (void *(*)(void *))(Local);
    return _GetLocalPlayer(Game);
}

static Vector3 Transform_GetPosition(void *player) {
    Vector3 out = Vector3::zero();
    void (*_Transform_GetPosition)(void *transform, Vector3 * out) = (void (*)(void *, Vector3 *))(Class_Transform__GetPosition);
    _Transform_GetPosition(player, &out);
    return out;
}


static void *Curent_Match() {
    void *(*_Curent_Match) (void *nuls) = (void *(*)(void *))(Match);
    return _Curent_Match(NULL);
}


static void *GetHeadPositions(void *player) {
    void *(*_GetHeadPositions)(void *players) = (void*(*)(void *))(Head);
     return _GetHeadPositions(player);
}

static void *Component_GetTransform(void *player) {
    void *(*_Component_GetTransform)(void *component) = (void *(*)(void *))(Class_Compent__Transform);
    return _Component_GetTransform(player);
}

static Vector3 WorldToScreenPoint(void *WorldCam, Vector3 WorldPos) {
    Vector3 (*_WorldToScreenScene)(void* Camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) (Class_Camera__WorldToScreenPoint);
    return _WorldToScreenScene(WorldCam, WorldPos);
}


static void *Camera_main() {
    void *(*_Camera_main)(void *nuls) = (void *(*)(void *))(Class_Camera__get_main);
    return _Camera_main(nullptr);
}


static bool get_isVisible(void *player) {
    bool (*_get_isVisible)(void *players) = (bool (*)(void *))(Visible);
    return _get_isVisible(player);
}

static bool get_isLocalTeam(void *player) {
    bool (*_get_isLocalTeam)(void *players) = (bool (*)(void *))(Team);
    return _get_isLocalTeam(player);
}

static bool get_IsDieing(void *player) {
    bool (*_get_die)(void *players) = (bool (*)(void *))(Die);
    return _get_die(player);
}

static int GetHp(void* player) {
    int (*_GetHp)(void* players) = (int(*)(void *))(CurHP);
    return _GetHp(player);
}

static int get_MaxHP(void* enemy) {
    int (*_get_MaxHP)(void* player) = (int(*)(void *))(MaxHP);
    return _get_MaxHP(enemy);
}

static monoString* get_NickName(void *player) {
    monoString* (*_get_NickName)(void *players) = (monoString * (*)(void *))(Name);
    return _get_NickName(player);
}

static Vector3 GetForward(void *player) {
    Vector3 (*_GetForward)(void *players) = (Vector3 (*)(void *))(ForWard);
    return _GetForward(player);
}


static bool IsLocal(void *player) {
    bool (*_isMe)(void *players) = (bool (*)(void *))(LocalBool);
    return _isMe(player);
}
   
 static void *GetLocalCar(void *playerCar) {
    void *(*_Player_get_local)(void *Player) = (void *(*)(void *))(CarLocal);
    return _Player_get_local(playerCar);
    
    
}
static bool IsDriver(void *player) {
    bool (*_IsDriver)(void *players) = (bool (*)(void *))(GetCar);
    return _IsDriver(player);
}        
           


static void set_aim(void *player, Quaternion look) {
    void (*_set_aim)(void *players, Quaternion lock) = (void (*)(void *, Quaternion))(Aim);
    _set_aim(player, look);
}

char get_Chars(monoString *str, int index){
    char (*_get_Chars)(monoString *str, int index) = (char (*)(monoString *, int))(CharGet);
    return _get_Chars(str, index);
}

static bool get_IsSighting(void *player) {
    bool (*_get_IsSighting)(void *players) = (bool (*)(void *))(Scope);
    return _get_IsSighting(player);
}

static bool get_IsFiring(void *player) {
    bool (*_get_IsFiring)(void *players) = (bool (*)(void *))(Fire);
    return _get_IsFiring(player);
}


static bool get_isLocalTeam(void *player, bool isCheckSocial3pEffect) {
    bool (*_get_isLocalTeam)(void *, bool) = (bool (*)(void *, bool))(Team);
    return _get_isLocalTeam(player, isCheckSocial3pEffect);
}

static bool Physics_Raycast(Vector3 camLocation, Vector3 headLocation, unsigned int LayerID, void* collider) {
    bool (*_Physics_Raycast)(Vector3 camLocation, Vector3 headLocation, unsigned int LayerID, void* collider) = (bool(*)(Vector3, Vector3, unsigned int, void*))(Raycast);
    return _Physics_Raycast(camLocation, headLocation, LayerID, collider);
}

Vector3 getPosition(void *transform) {
    return get_position(Component_GetTransform(transform));
}   

static Vector3 GetHeadPosition(void* player) {
    return get_position(GetHeadPositions(player));
}

static Vector3 CameraMain(void* player){
    return get_position(*(void**) ((uint64_t) player + MainCam));
}


Vector3 get_mousePosition(void *_this) {
	Vector3 (*_get_mousePosition)(void *_this) = (Vector3 (*)(void *)) (Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_mousePosition"), 0));
	return _get_mousePosition(_this);
}



int get_width() {
    return reinterpret_cast<int(__fastcall *)()>(Class_Screen__get_width)();
}

int get_height() {
    return reinterpret_cast<int(__fastcall *)()>(Class_Screen__get_height)();
}

float get_density() {
    return reinterpret_cast<float(__fastcall *)()>(Class_Screen__get_density)();
}


// Camera XYZ
#define offset_MKKAFNCNELO Il2CppGetMethodOffset( \
    OBFUSCATE("Assembly-CSharp.dll"), \
    OBFUSCATE("COW.GamePlay"), \
    OBFUSCATE("FollowCamera"), \
    OBFUSCATE("ALHGMLGMNDP"), 2)
    
    // AHCBLOCABDP

// Aspect Hack

#define Camera_get_aspect (uintptr_t)Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "get_aspect", 0)

float GetAspect(void* cameraInstance) {
    using fnGet = float (*)(void*);
    auto _Get = reinterpret_cast<fnGet>(Camera_get_aspect);
    return _Get(cameraInstance);
}

#define Camera_set_aspect (uintptr_t)Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "set_aspect", 1)

void SetAspect(void* cameraInstance, float value) {
    using fnSet = void (*)(void*, float);
    auto _Set = reinterpret_cast<fnSet>(Camera_set_aspect);
    _Set(cameraInstance, value);
}

// GHOST HACK NEED UPDATE
#define offset_NeedSendMessage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("EPPMGCJDEDC"), OBFUSCATE("NFNJLPDJBNG"), 2)

// PNCPKGJGBPP
// EFJEIMIIEJO


// PC LOGO
#define offset_PDJBHMNNOFO (uintptr_t) Il2CppGetMethodOffset( \
    OBFUSCATE("Assembly-CSharp.dll"), \
    OBFUSCATE("ffantihack"), \
    OBFUSCATE("PCNABJAFBDO"), \
    OBFUSCATE("DOMEDHEFGHJ"), 1)
    
    // PCNABJAFBDO
    // DOMEDHEFGHJ

#define offset_GKCOOPMPOAD (uintptr_t) Il2CppGetMethodOffset( \
    OBFUSCATE("Assembly-CSharp.dll"), \
    OBFUSCATE("ffantihack"), \
    OBFUSCATE("PCNABJAFBDO"), \
    OBFUSCATE("PMAJKEKHKKB"), 0)
    
    // PCNABJAFBDO
    // PMAJKEKHKKB
    
// Transform position

#define Transform_get_position \
    ((uintptr_t)Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Transform", "get_position", 0))

#define Transform_set_position \
    ((uintptr_t)Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Transform", "set_position", 1))

Vector3 GetPosition(void* transform) {
    using fn = Vector3 (*)(void*);
    return ((fn)Transform_get_position)(transform);
}

void SetPosition(void* transform, Vector3 pos) {
    using fn = void (*)(void*, Vector3);
    ((fn)Transform_set_position)(transform, pos);
}

// Auto Fire
#define offset_GetWeaponOnHand (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetWeaponOnHand"), 0)

static void *GetWeaponOnHand(void *local)
{
    void *(*_GetWeaponOnHand)(void *local) = (void *(*)(void *))(offset_GetWeaponOnHand);
    return _GetWeaponOnHand(local);
}


#define m_get_player_ID (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_PlayerID"), 0)
#define offset_get_gameObject (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_gameObject"), 0)

// ── Auto Revive ──────────────────────────────────────────────────────
#define OFFSET_PlayerID_ToUint  (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("JAOECECKADN"), OBFUSCATE("DEIPJDIGKIP"), 1)
#define OFFSET_GameFacade_Send   (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("Send"), 4)

struct IHAAMHPPLMG { uint32_t _0; uint32_t _1; uint32_t _2; uint32_t _3; };

static IHAAMHPPLMG Player_GetPlayerID(void* p) {
    if (!p || !m_get_player_ID) return {0,0,0,0};
    auto fn = (IHAAMHPPLMG(*)(void*))m_get_player_ID;
    return fn(p);
}

static uint32_t PlayerID_ToUint(IHAAMHPPLMG id) {
    if (!OFFSET_PlayerID_ToUint) return 0;
    auto fn = (uint32_t(*)(IHAAMHPPLMG))OFFSET_PlayerID_ToUint;
    return fn(id);
}

static bool GameFacade_SendMsg(uint32_t mid, void* msg, uint8_t opt, bool cache) {
    if (!OFFSET_GameFacade_Send) return false;
    auto fn = (bool(*)(uint32_t,void*,uint8_t,bool))OFFSET_GameFacade_Send;
    return fn(mid, msg, opt, cache);
}

#define offset_StartWholeBodyFiring (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StartWholeBodyFiring"), 1)
#define offset_Weapon_StartFiring (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HBIBDMMOOOK"), OBFUSCATE("ALJMFCJMDCF"), 0)
#define offset_Weapon_StopFiring (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HBIBDMMOOOK"), OBFUSCATE("NFFJEBKJCAK"), 0)

#define m_DamageRange (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HBIBDMMOOOK"), OBFUSCATE("OEOBPHDFJMO"), 0)

static float get_Range(void* pthis)
{
    return ((float (*)(void*))(m_DamageRange))(pthis);
}

static void StartWholeBodyFiring(void* player, void* weapon) {
    if (!player || !weapon) return;
    auto fn = reinterpret_cast<void(*)(void*, void*)>(offset_StartWholeBodyFiring);
    fn(player, weapon);
}

void *get_gameObject(void *Pthis)
{
    return ((void* (*)(void *))(offset_get_gameObject))(Pthis);
}


#define SwapWeapon11234 Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("SwapWeapon"), 2)

static void SwapWeapon11(void* player, int POFFNNMOOBM, bool GDKLMFLNNGM) {
    void (*_SwapWeapon11)(void* player, int POFFNNMOOBM, bool GDKLMFLNNGM) = (void (*)(void *, int, bool))(SwapWeapon11234);
     _SwapWeapon11(player, POFFNNMOOBM, GDKLMFLNNGM);
}

// Teleport Mark
#define offset_UpdateLocalMark Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapContentController"), OBFUSCATE("UpdateLocalMark"), 4)



#define Class_Quaternion__AngleAxis Il2CppGetMethodOffset( \
    OBFUSCATE("UnityEngine.dll"), \
    OBFUSCATE("UnityEngine"), \
    OBFUSCATE("Quaternion"), \
    OBFUSCATE("AngleAxis"), 2)

static Quaternion AngleAxis(float angle, Vector3 axis)
{
    Quaternion (*_AngleAxis)(float, Vector3) =
        (Quaternion(*)(float, Vector3))(Class_Quaternion__AngleAxis);
    return _AngleAxis(angle, axis);
}

#define Class_Quaternion__Multiply Il2CppGetMethodOffset( \
    OBFUSCATE("UnityEngine.dll"), \
    OBFUSCATE("UnityEngine"), \
    OBFUSCATE("Quaternion"), \
    OBFUSCATE("op_Multiply"), 2)

static Quaternion Quaternion_Multiply(Quaternion lhs, Quaternion rhs)
{
    Quaternion (*_Multiply)(Quaternion, Quaternion) =
        (Quaternion(*)(Quaternion, Quaternion))(Class_Quaternion__Multiply);
    return _Multiply(lhs, rhs);
}




#define Class_Transform__SetRotation Il2CppGetMethodOffset( \
    OBFUSCATE("UnityEngine.dll"), \
    OBFUSCATE("UnityEngine"), \
    OBFUSCATE("Transform"), \
    OBFUSCATE("set_rotation_Injected"), 1)

static void Transform_SetRotation(void* transform, Quaternion rot)
{
    void (*_setRot)(void*, Quaternion*) =
        (void(*)(void*, Quaternion*))(Class_Transform__SetRotation);
    _setRot(transform, &rot);
}

#define Class_SetRotation Il2CppGetMethodOffset( \
    OBFUSCATE("UnityEngine.dll"), \
    OBFUSCATE("UnityEngine"), \
    OBFUSCATE("Transform"), \
    OBFUSCATE("set_localRotation_Injected"), 1)
    
static void SetRotation(void* transform, Quaternion rot)
{
    void (*_setRot)(void*, Quaternion*) =
        (void(*)(void*, Quaternion*))(Class_SetRotation);
    _setRot(transform, &rot);
}

#define OFFSET_CreateLoginReq Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIModelLogin"), OBFUSCATE("CreateLoginReqInfoData"), 1)



// تعريف Hook لـ GetVehicleIAmIn
#define Player__GetVehicleIAmIn (uintptr_t) Il2CppGetMethodOffset( \
    OBFUSCATE("Assembly-CSharp.dll"), \
    OBFUSCATE("COW.GamePlay"), \
    OBFUSCATE("Player"), \
    OBFUSCATE("GetVehicleIAmIn"))

// دالة لاستدعاء GetVehicleIAmIn
void* GetVehicleIAmIn(void* player) {
    // الـ method يأخذ parameter واحد (this)
    typedef void* (*GetVehicleIAmIn_t)(void*);
    return reinterpret_cast<GetVehicleIAmIn_t>(Player__GetVehicleIAmIn)(player);
}


// Auto Revive
#define offset_RequestRescureTar (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("COBFBHFCIPD"))
#define offset_PJKBDOJLDNN (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("COBFBHFCIPD"), OBFUSCATE("BAFEIAKDCEK"))
#define offset_GMOHIILGMGM (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("COBFBHFCIPD"), OBFUSCATE("OFAAFCOMJGJ"))

#define _GameFacade (uintptr_t) Il2CppGetClassType(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"))


#define offset_PlayerID (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_PlayerID"), 0)
IHAAMHPPLMG GetplayerID(void *p) {
    return ((IHAAMHPPLMG(*)(void*))offset_PlayerID)(p);
}
                                               
#define offset_CFFPIACECIG (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("JAOECECKADN"), OBFUSCATE("DEIPJDIGKIP"), 1)

uint32_t CFFPIACECIG(IHAAMHPPLMG id) {
    return ((uint32_t(*)(IHAAMHPPLMG))offset_CFFPIACECIG)(id);
}

#define offset_GameFacade_Send (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("Send"), 4)
bool GameFacade_Send(uint32_t mid, void *msg, uint8_t opt, bool cache) { return ((bool(*)(uint32_t,void*,uint8_t,bool))offset_GameFacade_Send)(mid,msg,opt,cache); }

#define m_HeadNode      (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GBKFHDFCPMD"))  // was PEMOFNFCLFB
#define m_Neck          (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("FFFPCADFFGA"))  // was KAKOKIHEPCF
#define m_HipNode       (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("COBFGNOIPMF"))  // was DIDHPFKMJJE
#define m_LeftShoulder  (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("FFDPGNIKAEK"))  // was NBHOEOOCIIG
#define m_RightShoulder (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("FOELKAHABCD"))  // was OEJFBHIIBBG
#define m_LeftElbow     (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IMLDFGHNLBP"))  // was KNBJLEHOPIL
#define m_RightElbow    (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("DJAOGHBOBOJ"))  // was KMIANNCLNOJ
#define m_LeftHand      (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("ONEIIEEJLOC"))  // was OEHAGFIGILO
#define m_RightHand     (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("JLAECGNPCHC"))  // was DIHJDDNIJHP
#define m_LeftKnee      (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GPIBDOCMHBE"))  // was BOHFCEHMJBD
#define m_RightKnee     (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("EMNIJJCEKDD"))  // was BIPBNNIFCNO
#define m_LeftFoot      (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GMJLIMFHMAE"))  // was JLLMBADGKJP
#define m_RightFoot     (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("JMHBBGIKBNO"))  // was INHGPBHOKPF
#define m_Root          (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IIPBIDIBJDK"))  // was KNFKIDHJCCO

#define m_itransformNode (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TransformNode"), OBFUSCATE("get_transform"), 0)

static auto get_itransform(void* player) {
    auto (*_get_itransform)(void*) = (void* (*)(void*))(m_itransformNode);
    return _get_itransform(player);
}


#define Class_GetLocalScale Il2CppGetMethodOffset( \
    OBFUSCATE("UnityEngine.dll"), \
    OBFUSCATE("UnityEngine"), \
    OBFUSCATE("Transform"), \
    OBFUSCATE("get_localScale_Injected"), 1)

#define Class_SetLocalScale Il2CppGetMethodOffset( \
    OBFUSCATE("UnityEngine.dll"), \
    OBFUSCATE("UnityEngine"), \
    OBFUSCATE("Transform"), \
    OBFUSCATE("set_localScale_Injected"), 1)

static Vector3 GetLocalScale(void* transform)
{
    if (!transform) return Vector3(1.0f, 1.0f, 1.0f);

    void (*_getScale)(void*, Vector3*) =
        (void(*)(void*, Vector3*))(Class_GetLocalScale);

    Vector3 result;
    _getScale(transform, &result);
    return result;
}

static void SetLocalScale(void* transform, Vector3 scale)
{
    if (!transform) return;

    void (*_setScale)(void*, Vector3*) =
        (void(*)(void*, Vector3*))(Class_SetLocalScale);

    _setScale(transform, &scale);
}

#define CurFootball (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_CurFootball"), 0)

#define IsFootball (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsFootball"), 0)

static void* get_CurFootball(void* player) {
    void* (*_get_CurFootball)(void*) =
        (void* (*)(void*))(CurFootball);
    return _get_CurFootball(player);
}

static bool get_IsFootball(void *player) {
    bool (*_get_foot)(void *players) = (bool (*)(void *))(IsFootball);
    return _get_foot(player);
}

// ── Cover pull (SilentGhostPullV2 from aim kill — hits behind cover) ──
static inline bool IsPullTargetValid(void *enemy) {
    if (!enemy) return false;
    if (GetHp(enemy) <= 0) return false;
    if (get_IsDieing(enemy)) return false;
    if (!GetHeadPositions(enemy)) return false;
    if (!Component_GetTransform(enemy)) return false;
    return true;
}

static inline void *GetPlayerHeadTransform(void *player) {
    if (!player) return nullptr;
    return GetHeadPositions(player);
}

static bool IsVisibleForCoverPull(void *player) {
    if (!IsPullTargetValid(player)) return false;
    void *hitObj = nullptr;
    void *headTF = GetPlayerHeadTransform(player);
    if (!headTF) return false;
    void *match = Curent_Match();
    if (!match) return false;
    void *local = GetLocalPlayer(match);
    if (!local) return false;
    Vector3 enemyHead = GetPosition(headTF);
    Vector3 camPos = CameraMain(local);
    return !Physics_Raycast(camPos, enemyHead, 12, &hitObj);
}

static bool SilentGhostPullV2(void *enemy, float *outBestXZRadius = nullptr, bool apply = true) {
    if (!IsPullTargetValid(enemy)) return false;

    if (IsVisibleForCoverPull(enemy)) {
        if (outBestXZRadius) *outBestXZRadius = 0.0f;
        return true;
    }

    void *enemyTF = Component_GetTransform(enemy);
    if (!enemyTF) return false;

    Vector3 enemyRoot = GetPosition(enemyTF);

    void *headTF = GetPlayerHeadTransform(enemy);
    if (!headTF) return false;

    Vector3 enemyHead = GetPosition(headTF);
    Vector3 headOffset = {
        enemyHead.x - enemyRoot.x,
        enemyHead.y - enemyRoot.y,
        enemyHead.z - enemyRoot.z
    };

    void *match = Curent_Match();
    if (!match) return false;
    void *lp = GetLocalPlayer(match);
    if (!lp) return false;

    void *lpHeadTF = GetPlayerHeadTransform(lp);
    if (!lpHeadTF) return false;

    Vector3 lpHead = GetPosition(lpHeadTF);

    auto testPull = [&](float dx, float dy, float dz) -> bool {
        if (!IsPullTargetValid(enemy)) return false;

        Vector3 newRoot = enemyRoot;
        newRoot.x += dx;
        newRoot.y += dy;
        newRoot.z += dz;

        Vector3 newHead = {
            newRoot.x + headOffset.x,
            newRoot.y + headOffset.y,
            newRoot.z + headOffset.z
        };

        void *hitObj = nullptr;
        if (Physics_Raycast(lpHead, newHead, 12, &hitObj))
            return false;

        if (outBestXZRadius)
            *outBestXZRadius = sqrtf(dx * dx + dz * dz);

        if (apply) {
            void *tf = Component_GetTransform(enemy);
            if (!tf) return false;
            SetPosition(tf, newRoot);
        }
        return true;
    };

    static const float zForward[] = {1.5f, 3.0f, 4.5f, -1.5f, -3.0f, -4.5f};
    for (float z : zForward)
        if (testPull(0, 0, z)) return true;

    static const float xSide[] = {-2.0f, -0.8f, 0.8f, 2.0f, -3.2f, 3.2f};
    for (float x : xSide)
        if (testPull(x, 0, 0)) return true;

    for (float z : zForward) {
        for (float x : xSide) {
            if (testPull(x, 0, z)) return true;
        }
    }

    for (int i = 0; i < 30; i++) {
        float dy = -1.4f - 0.015f * i;
        if (testPull(0, dy, 0)) return true;
    }

    return false;
}

// ── AimKill helpers (Il2Cpp only, no hardcoded RVA) ─────────────────
#define offset_getdamage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("BAPINEFALEM"), 0)
#define offset_itemid (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("LGMNCCAPNHJ"), OBFUSCATE("LJIPAJAMCKK"), 0)
#define offset_LAEMLAPIAFD (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("DJMMOHAJFPB"))
#define offset_POBGKMDJMDC (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("AGACNOCEEFP"), OBFUSCATE("FPANKJIJBIH"))
#define uniqueid_weapon (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("LGMNCCAPNHJ"), OBFUSCATE("DEGODFCOKGC"))
#define offset_GKHECDLGAJA (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("KNBEPECEJEP"), 1)
#define offset_LCLHHHKFCFP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("LKHKGOFALIB"), 4)
#define offset_Player_TakeDamage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("TakeDamage"), 9)
#define offset_StartFiring_PN (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StartFiring"), 1)
#define offset_StopFire_PN (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StopFire"), 1)
#define get_timeV (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Time"), OBFUSCATE("get_time"), 0)
#define offset_SyncSwapWeapon_AK (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"))
#define offset_IHAAMHPPLMG_s (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"), OBFUSCATE("BHGGAEEHJCO"))
#define offset_DGLCOGJJFMI_s (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"), OBFUSCATE("DBPPPOBFJNP"))

// SwapWeapon - resolved once at startup
static void* ptr_SwapWeapon3 = nullptr;
static void* ptr_SwapWeapon2 = nullptr;
static bool swapResolved = false;

static void SwapWeapon(void *player, int slot, bool animate) {
    if (!player) return;

    if (!swapResolved) {
        ptr_SwapWeapon3 = (void*)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("SwapWeapon"), 3);
        ptr_SwapWeapon2 = (void*)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("SwapWeapon"), 2);
        swapResolved = true;
    }

    if (ptr_SwapWeapon3) {
        ((void (*)(void*, int, bool, void*))ptr_SwapWeapon3)(player, slot, animate, nullptr);
    } else if (ptr_SwapWeapon2) {
        ((void (*)(void*, int, bool))ptr_SwapWeapon2)(player, slot, animate);
    }
}

#define Dmg_BaseDamage   (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HNLIMBLIANL"), OBFUSCATE("KOPMDJJKLKH")) //
#define Dmg_ColliderType (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HNLIMBLIANL"), OBFUSCATE("BGMOAOCFPGM")) //
#define Dmg_PlayerID     (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HNLIMBLIANL"), OBFUSCATE("BIHCFIINIBK")) //
#define Dmg_WeaponOnHand (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HNLIMBLIANL"), OBFUSCATE("HBIBDMMOOOK")) //
#define Dmg_FirePos      (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HNLIMBLIANL"), OBFUSCATE("HOOMBLGOEPL")) //
#define Dmg_HitPos       (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HNLIMBLIANL"), OBFUSCATE("KEOAMDFAOLM")) //
#define Dmg_WeaponDataId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HNLIMBLIANL"), OBFUSCATE("NEGABPENICF")) //

static int GetDamage(void *weapon) {
    if (!weapon || !offset_getdamage) return 0;
    return ((int (*)(void *))offset_getdamage)(weapon);
}

static int GetWeaponID(void *weapon) {
    if (!weapon || !offset_itemid) return 0;
    return ((int (*)(void *))offset_itemid)(weapon);
}

static uintptr_t GetWeaponDataId(void *weapon) {
    if (!weapon || !offset_LAEMLAPIAFD || !offset_POBGKMDJMDC) return 0;
    void *inner = *(void **)((uintptr_t)weapon + offset_LAEMLAPIAFD);
    if (!inner) return 0;
    return *(int *)((uintptr_t)inner + offset_POBGKMDJMDC);
}

static uint32_t GetUniqueID(void *weapon) {
    if (!weapon || !uniqueid_weapon) return 0;
    return *(uint32_t *)((uintptr_t)weapon + uniqueid_weapon);
}

static void *GKHECDLGAJA(void *player, void *hitInfo) {
    if (!player || !hitInfo || !offset_GKHECDLGAJA) return nullptr;
    return ((void *(*)(void *, void *))offset_GKHECDLGAJA)(player, hitInfo);
}

static void *LCLHHHKFCFP(void *weapon, void *hitObj, void *collider, bool flag, void *dmgInfo) {
    if (!weapon || !offset_LCLHHHKFCFP) return nullptr;
    return ((void *(*)(void *, void *, void *, bool, void *))offset_LCLHHHKFCFP)(weapon, hitObj, collider, flag, dmgInfo);
}

static int Call_Player_TakeDamage(void *enemy, int damage, IHAAMHPPLMG pid, void *dmgInfo, int weaponID, Vector3 firePos, Vector3 hitPos, void *params, void *wdi, uint32_t veh) {
    if (!enemy || !offset_Player_TakeDamage) return 0;
    return ((int (*)(void *, int, IHAAMHPPLMG, void *, int, Vector3, Vector3, void *, void *, uint32_t))offset_Player_TakeDamage)(
        enemy, damage, pid, dmgInfo, weaponID, firePos, hitPos, params, wdi, veh);
}

static void StartFiring_PN(void *player, void *weapon) {
    if (!player || !weapon || !offset_StartFiring_PN) return;
    ((void (*)(void *, void *))offset_StartFiring_PN)(player, weapon);
}

static void StopFire_PN(void *player, void *weapon) {
    if (!player || !weapon || !offset_StopFire_PN) return;
    ((void (*)(void *, void *))offset_StopFire_PN)(player, weapon);
}

static float get_time() {
    if (!get_timeV) return 0.f;
    return ((float (*)())get_timeV)();
}

static void Syns_SwapWeapon_Impl(void *localPlayer, void *weapon) {
    if (!localPlayer || !weapon) return;
    void *msg = (void *)offset_SyncSwapWeapon_AK;
    if (!msg || !offset_IHAAMHPPLMG_s || !offset_DGLCOGJJFMI_s) return;
    *(uint32_t *)((uintptr_t)msg + offset_IHAAMHPPLMG_s) = CFFPIACECIG(GetplayerID(localPlayer));
    *(uint32_t *)((uintptr_t)msg + offset_DGLCOGJJFMI_s) = GetUniqueID(weapon);
    GameFacade_Send(108, msg, 2, 0);
}

struct WeaponDynamicInfo2_o {
    void *klass;
    void *monitor;
    float BiteArmor;
    int32_t ContinuousFireDamage;
    int32_t DynamicChangeDamage;
    float DynamicDamageRatioBody;
    float DynamicDamageRatioHead;
    float DynamicDamageRatioLimb;
    float BoostDamage;
    float ShieldDamageRatioWeapon;
    float ShieldDamageRatioBody;
    float ShieldDamageRatioHead;
    float ShieldDamageRatioLimb;
};

static float get_realtimeSinceStartup() {
    void* fn = (void*)Il2CppGetMethodOffset(
        OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"),
        OBFUSCATE("Time"), OBFUSCATE("get_realtimeSinceStartup"), 0);
    if (fn) return ((float(*)())fn)();
    return 0.0f;
}

static monoString* U3DStr(const char* text) {
    return (monoString*)Il2CppString::Create(text);
}


static monoString* U3DStrFormat(float distance, int hp) {
    char buffer[128] = {0};
    sprintf(buffer, " LION CHEATS| HP: %d | DISTANCE: %.f M", hp, distance);
    return U3DStr(buffer);
}

static void* GetUIInGameScene() {
    void* (*fn)() = (void*(*)())Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"),
        OBFUSCATE("GameFacade"), OBFUSCATE("CurrentInGameUIScene"), 0);
    if (fn) return fn();
    return nullptr;
}

static void ShowCenterUpTeammateTips(monoString* message, float duration = 3.0f) {
    void* off = Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"),
        OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowCenterUpTeammateTips"), 2);
    if (!off) return;
    void (*_Show)(void*, monoString*, float) = (void(*)(void*, monoString*, float))(off);
    void* ui = GetUIInGameScene();
    if (ui) _Show(ui, message, duration);
}

static void ShowPopupMessageNoAnim(monoString* message, float duration = 2.0f) {
    void* off = Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"),
        OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowPopupMessageNoAnim"), 2);
    if (!off) return;
    void (*_Show)(void*, monoString*, float) = (void(*)(void*, monoString*, float))(off);
    void* ui = GetUIInGameScene();
    if (ui) _Show(ui, message, duration);
}

static void ShowCreditPopup(monoString* message) {
    void* off = Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"),
        OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowCreditBehaviorPopupMessage"), 1);
    if (!off) return;
    void (*_Show)(void*, monoString*) = (void(*)(void*, monoString*))(off);
    void* ui = GetUIInGameScene();
    if (ui) _Show(ui, message);
}

#define offset_ShowPaymentMessageBoxNotUseSpecialDepth (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("PayUtility"), OBFUSCATE("ShowPaymentMessageBoxNotUseSpecialDepth"), 7)

// PayUtility.ShowPaymentMessageBoxNotUseSpecialDepth — dump.cs v7a @ 0x5C9C13C
// UIPopupMessageBox2Controller.EButtonStyle: None=0, OKOnly=1, OKCancel=2, OKClose=3
static void ShowPaymentCreditDialog(monoString* message, monoString* title, int buttonStyle = 2) {
    if (!offset_ShowPaymentMessageBoxNotUseSpecialDepth) return;
    void (*_Show)(monoString*, monoString*, monoString*, void*, void*, monoString*, int) =
        (void (*)(monoString*, monoString*, monoString*, void*, void*, monoString*, int))(offset_ShowPaymentMessageBoxNotUseSpecialDepth);
    _Show(message, title, nullptr, nullptr, nullptr, nullptr, buttonStyle);
}

static void ShowCheatOussamaDialog2(monoString* message, monoString* title) {
    ShowPaymentCreditDialog(message, title, 2);
}



static void ShowCreditDialog1() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}


static void ShowCreditDialog2() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}


static void ShowCreditDialog3() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}

static void ShowCreditDialog4() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}


static void ShowCreditDialog5() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}


static void ShowCreditDialog6() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}


static void ShowCreditDialog7() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}


static void ShowCreditDialog8() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}

static void ShowCreditDialog9() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}

static void ShowCreditDialog10() {
    ShowPaymentCreditDialog(
        U3DStr(OBFUSCATE("[ff0000]MADE BY @THE_LION_CHEATS")),
        U3DStr(OBFUSCATE("")), 2);
}
static void ShowCreditDialogByIndex(int index) {
    switch (index % 10) {
        case 0: ShowCreditDialog1(); break;
        case 1: ShowCreditDialog2(); break;
        case 2: ShowCreditDialog3(); break;
        case 3: ShowCreditDialog4(); break;
        case 4: ShowCreditDialog5(); break;
        case 5: ShowCreditDialog6(); break;
        case 6: ShowCreditDialog7(); break;
        case 7: ShowCreditDialog8(); break;
        case 8: ShowCreditDialog9(); break;
        default: ShowCreditDialog10(); break;
    }
}

static void TryShowEnableAllDialogOnce(bool enabled) {
    static bool dialogShown = false;
    if (!enabled || dialogShown) return;
    if (!GetUIInGameScene()) return;

    ShowCreditDialog1();
    dialogShown = true;
}

static void AddTeammateHud(monoString* nick, monoString* info) {
    void* off = Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"),
        OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowAssistantText"), 2);
    if (!off) return;
    void (*_Add)(void*, monoString*, monoString*) = (void(*)(void*, monoString*, monoString*))(off);
    void* ui = GetUIInGameScene();
    if (ui) _Add(ui, nick, info);
}

static void RxmGetNickName(void* targetEnemy) {
    if (!targetEnemy) return;
    if (get_IsDieing(targetEnemy)) return;
    if (GetHp(targetEnemy) <= 0) return;

    void* match = Curent_Match();
    if (!match) return;
    void* localPlayer = GetLocalPlayer(match);
    if (!localPlayer) return;

    void* camera = Camera_main();
    if (!camera) return;
    void* camTF = Component_GetTransform(camera);
    if (!camTF) return;

    Vector3 camPos = getPosition(camTF);
    Vector3 enemyHeadPos = GetHeadPosition(targetEnemy);
    if (enemyHeadPos.x == 0 && enemyHeadPos.y == 0 && enemyHeadPos.z == 0) return;

    float distance = sqrtf(
        (camPos.x - enemyHeadPos.x) * (camPos.x - enemyHeadPos.x) +
        (camPos.y - enemyHeadPos.y) * (camPos.y - enemyHeadPos.y) +
        (camPos.z - enemyHeadPos.z) * (camPos.z - enemyHeadPos.z)
    );

    monoString* nick = get_NickName(targetEnemy);
    if (!nick) return;
    int enemyHp = GetHp(targetEnemy);
    monoString* distances = U3DStrFormat(distance, enemyHp);
    if (!distances) return;
    AddTeammateHud(nick, distances);
}
