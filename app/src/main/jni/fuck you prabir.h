// NoDamage fuck
bool (*orig_TakeDamage)(void* __this, void* avatar, void* local, void* WeaponData, const void* method);

bool hook_TakeDamage(void* __this, void* avatar, void* local, void* WeaponData, const void* method) {

    if (!Enable) return orig_TakeDamage(__this, avatar, local, WeaponData, method);

    if (NoDamage) {
		
		void* match = Curent_Match();
		if (!match) return orig_TakeDamage(__this, avatar, local, WeaponData, method);

	    void* localPlayerc = GetLocalPlayer(match);
	    if (!localPlayerc) return orig_TakeDamage(__this, avatar, local, WeaponData, method);


        if (local == localPlayerc) {  

            return false;

        }

    }

    return orig_TakeDamage(__this, avatar, local, WeaponData, method);

}

DobbyHook((void*)(TakeDamage), (void*)hook_TakeDamage, (void**)&orig_TakeDamage);

