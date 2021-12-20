#include <stdio.h>
#include <stdbool.h>
#include "trainer/trainer.h"
#include "structs.h"


static void
toggle_health_godmode(bool * status, uintptr_t base)
{
    *status = !*status;

    uintptr_t address = base + 0x12153F + 0x1 + 0x21;

    if (*status) {
        // patch
        trainer_internal_memory_write_protect((uint8_t *)(address), (uint8_t[]) { 0x90, 0x90, 0x90, 0x90 }, 4);
    }
    else {
        // restore original
        trainer_internal_memory_write_protect((uint8_t *)(address), (uint8_t[]) { 0x85, 0xC0, 0x74, 0x05 }, 4);
    }
}


static void
get_keys(struct PLAYERstruct * player_struct)
{
    for (int i = 0; i < 8; ++i) {
        player_struct->HasKey[i] = 1;
    }
}


static void
get_weapons(struct PLAYERstruct * player_struct)
{
    player_struct->WpnFlags = 0xFFFFFFFF;
}


static void
set_all_ammo(struct PLAYERstruct * player_struct)
{
    for (int i = 0; i < 14; ++i) {
        player_struct->WpnAmmo[i] = 99;
    }
}


static void
set_health(int value, struct USER ** users, struct PLAYERstruct * player_struct)
{
    // Find the the correct struct USER to matches the player_struct pointer and set the health
    // Changes when a new level loads
    // Memory is not zeroed and multiple entries are valid so it's not obvious what the current one is,
    // so just use every match
    for (int i = 0; i < 0x4000; ++i) { // _User[0xFFFF]
        struct USER * user = users[i];
        if (user == NULL) {
            continue;
        }
        if (user->PlayerP == player_struct) {
            user->Health = value;
        }
    }
}


DWORD WINAPI
InjectThread(HMODULE hModule)
{
    /////////////////////////////////////////////////////////////////////////
    int key_stop = VK_END;
    int key_health = VK_F1;
    int key_armor = VK_F2;
    int key_ammo = VK_F3;
    int key_get_keys = VK_F4;
    int key_get_weapons = VK_F5;
    int key_health_godmode = VK_F6;

    bool health_god_status = false;
    bool health_status = false;
    bool armor_status = false;
    bool ammo_status = false;
    /////////////////////////////////////////////////////////////////////////

    AllocConsole();
    FILE * fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    uintptr_t base = trainer_internal_address_module_base();

    struct PLAYERstruct * player_struct = *(struct PLAYERstruct **)(base + 0x6EFD04);
    struct USER ** users = (struct USER *)(base + 0x6f0700);


    printf("Press 'End' to exit.\n\n");

    get_keys(player_struct);
    get_weapons(player_struct);

    while (true) {
        // quit
        if (GetAsyncKeyState(key_stop) & 1) {
            printf("\nStopping .. \n");
            Sleep(1000);
            break;
        }

        // health
        if (GetAsyncKeyState(key_health) & 1) {
           health_status = !health_status;
        }
        if (health_status) {
            set_health(77, users, player_struct);
        }

        // armor
        if (GetAsyncKeyState(key_armor) & 1) {
            armor_status = !armor_status;
        }
        if (armor_status) {
            player_struct->Armor = 88;
        }

        // ammo
        if (GetAsyncKeyState(key_ammo) & 1) {
            ammo_status = !ammo_status;
        }
        if (ammo_status) {
            set_all_ammo(player_struct);
        }

        // get keys
        if (GetAsyncKeyState(key_get_keys) & 1) {
            get_keys(player_struct);
        }

        // get weapons
        if (GetAsyncKeyState(key_get_weapons) & 1) {
            get_weapons(player_struct);
        }

        // health godmode
        if (GetAsyncKeyState(key_health_godmode) & 1) {
            toggle_health_godmode(&health_god_status, base);
        }

        // display status
        printf("\rHealth %3s (%s), Armor %3s (%s), Ammo %3s (%s), Get Keys (%s), Get Weapons (%s), God %3s (%s)",
            health_status ? "on" : "off", "F1",
            armor_status ? "on" : "off", "F2",
            ammo_status ? "on" : "off", "F3",
            "F4",
            "F5",
            health_god_status ? "on" : "off", "F6");

        Sleep(10);
    }

    fclose(fp);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    HANDLE th;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        th = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InjectThread, hModule, 0, NULL);
        if (th != NULL)
            CloseHandle(th);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
