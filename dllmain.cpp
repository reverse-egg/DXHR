#include "pch.h"

#include "DXHR.h"
#include <thread>
#include <atomic>

#define EXITTING 1
#define CHEAT_INVINCIBILITY 2
#define CHEAT_INFINITE_AMMO 3
#define CHEAT_NO_ENERGY_COST 4
#define CHEAT_KIT_OUT_CURRENT_GUN 5
#define CHEAT_SILENCER 6
#define CHEAT_LASER_SIGHT 7
#define CHEAT_DAMAGE 8
#define CHEAT_RATE_OF_FIRE 9

#define PIPE_NAME LR"(\\.\pipe\dxhr)"

std::atomic<bool> exitting{ false };
std::atomic<bool> infiniteAmmoExited{ false };

Cheats cheats;
bool infiniteAmmo = false;

void InfiniteAmmoLoop() {

    while (true) {

        if (exitting) {

            break;

        }

        if (infiniteAmmo) {

            cheats.SetAmmo(50);

        }

        Sleep(200);

    }

    infiniteAmmoExited = true;

}

void GameManagerLoop() {

    HANDLE hPipe = CreateFile(PIPE_NAME, GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hPipe == INVALID_HANDLE_VALUE) {

        MessageBoxA(NULL, "Failed to connect to named pipe", "Error", MB_OK);

    }

    HMODULE hDxhr = GetModuleHandleA("DXHR.dll");

    while (true) {

        int command;
        DWORD bytesRead;

        bool success = ReadFile(hPipe, &command, sizeof(command), &bytesRead, NULL);

        if(success) {

			switch (command) {

			case EXITTING:

                exitting = true;

                while (!infiniteAmmoExited) { Sleep(200); }

                if (hDxhr != NULL) {

                    FreeLibrary(hDxhr);
                    FreeLibraryAndExitThread(hDxhr, 0);

                }

                break;

			case CHEAT_INVINCIBILITY:

                cheats.SetHealth(200.0f);
				cheats.Invincible(true);

				break;

			case CHEAT_INFINITE_AMMO:

				infiniteAmmo = !infiniteAmmo;

				break;

			case CHEAT_NO_ENERGY_COST:

				cheats.NoEnergyCost(true);

				break;

			case CHEAT_KIT_OUT_CURRENT_GUN:

				cheats.SetWeaponSilencer(true);
				cheats.SetWeaponLaserSight(true);
				cheats.SetWeaponRateOfFire(0xF);
				cheats.SetWeaponDamage(0xF);

				break;

            case CHEAT_SILENCER:

                cheats.SetWeaponSilencer(true);

                break;

            case CHEAT_LASER_SIGHT:

                cheats.SetWeaponLaserSight(true);

                break;

            case CHEAT_DAMAGE:

                cheats.SetWeaponDamage(0xF);

                break;

            case CHEAT_RATE_OF_FIRE:

                cheats.SetWeaponRateOfFire(0xF);

                break;

			}

		}

        Sleep(200);

    }

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {

        std::thread gamemanagerloop(GameManagerLoop);
        std::thread infiniteammoloop(InfiniteAmmoLoop);

        gamemanagerloop.detach();
        infiniteammoloop.detach();

        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

