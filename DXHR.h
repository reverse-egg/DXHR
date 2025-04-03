#pragma once

#include <Windows.h>
#include <string>
#include <format>
#include <thread>
#include <map>
#include <iostream>

#define WEAPON_ID_PISTOL 0x05FB
#define WEAPON_ID_PISTOL_ARMOR_PIERCING 0x1EF1
#define WEAPON_ID_ASSAULT_RIFLE 0x294A
#define WEAPON_ID_SHOTGUN 0x2D3B
#define WEAPON_ID_MACHINE_PISTOL 0x4AAA
#define WEAPON_ID_STUN_GUN 0x50BE
#define WEAPON_ID_HEAVY_RIFLE 0x99AA
#define WEAPON_ID_PEPS 0x6AB8
#define WEAPON_ID_LASER_RIFLE 0xB04E
#define WEAPON_ID_GRENADE_LAUNCHER 0xFF14

/*
*
* Class: Vftables
*
* This is a convenience class to distinctly hold pointers to virtual function tables
* for different classes within Deus Ex Human Revolution.
*
*/
class Vftables {

public:

	Vftables();
	~Vftables() = default;

	uintptr_t NeActor;
	uintptr_t NeActorPlayer;
	uintptr_t NeActorNpc;

    uintptr_t AugmentationSystem;

    uintptr_t HealthSystem;

	uintptr_t UpgradeDescriptor_uint32_t;
	uintptr_t UpgradeDescriptor_bool8;
	uintptr_t UpgradeDescriptor_float;

	uintptr_t GrabSystem;

	uintptr_t InventoryContainer;
	uintptr_t InventoryPlayer;

};

enum class Upgrades {
    EnergyRegenDelay_float,
    EnergyPointsPerCell_float,
    EnergyNumOfCells_uint32_t,
    EnergyRechargeRate_float,
    JumpLevel_uint32_t,
    EnableAugmentedSprint_bool,
    EnableBungee_bool,
    BungeeEnergyCost_float,
    EnablePunchThroughWall_bool,
    PunchThroughWallEnergyCost_float,
    TakeDownNumTargets_uint32_t,
    TakeDownSingleKillEnergyCost_float,
    TakeDownSingleStunEnergyCost_float,
    TakeDownMultiKillEnergyCost_float,
    TakeDownMultiStunEnergyCost_float,
    FiringRecoil_float,
    InventoryWidth_uint32_t,
    InventoryHeight_uint32_t,
    PrimaryDamageTaken_float,
    EnableEMPShielding_bool,
    ClaymoreDamage_float,
    ClaymoreEnergyCost_float,
    EnableUseDeviceRemotely_bool,
    HackingCPUCycles_uint32_t,
    HackingCaptureSoftwareRating_uint32_t,
    HackingFortifySoftwareRating_uint32_t,
    HackingStealthSoftwareRating_uint32_t,
    HackingDetectionFeedback_bool,
    HackingAPIsAnalyzeLevel_uint32_t,
    HackingDatastoresAnalyzeLevel_uint32_t,
    EnableHackCameras_bool,
    EnableHackTurrets_bool,
    EnableHackRobots_bool,
    EnableConversationPersuasionLevel_bool,
    EnableConversationNPCAttributes_bool,
    EnableConversationClues_bool,
    EnableConversationSpotNPCs_bool,
    EnableConversationSpecialAttacks_bool,
    EnableStealthNoiseFeedback_bool,
    EnableStealthVisionFeedback_bool,
    ReticleGrowth_float,
    RadarRange_float,
    RadarUnseenEnemies_bool,
    ImmunedToGasAndHazards_bool,
    SprintDuration_float,
    SprintMaxCooldown_float,
    EnableHeavyObjectsGrab_bool,
    GrabLightObjectEnergyCost_float,
    GrabHeavyObjectEnergyCost_float,
    ThrowLightObjectEnergyCost_float,
    ThrowHeavyObjectEnergyCost_float,
    EnableXRayVision_bool,
    XRayEnergyCostOverTime_float,
    RunSilently_bool,
    SprintSilently_bool,
    JumpLandSilently_bool,
    SilentRunEnergyCostOverTime_float,
    EnableCamouflage_bool,
    CamouflageEnergyCostOverTime_float,
    AlarmTimer_bool,
    FlashSuppressant_bool,
    WirelessInteractionMaxRange_float,
    SyntheticPheromonesPropagator_bool,
    MarksNumber_uint32_t,
    LastKnownPosition_bool,
    NUM_UPGRADE_DESCRIPTORS
};

/*
* 
* Struct: UpgradeDescriptor
* 
* These are used for upgrades and various facets of the game such as:
* 
* FiringRecoil, EnablePunchThroughWall, EnergyCosts, etc.
* 
*/
struct UpgradeDescriptor {

	/* Dependent upon vftable pointer for either UpgradeDescriptor_uint32, UpgradeDescriptor_bool8, UpgradeDescriptor_float */
	uintptr_t type;

	/* Name of the upgrade */
	char* name;

	int unknown1;

	/* A pointer to the value of the upgrade which could be uint32, bool8 or float */
	void* value;

	int unknown2;

	int unknown3;

	int unknown4;

	int unknown5;

};

/*
* 
* Class: UpgradeDescriptorArrayManager
* 
* This handles the NeActorPlayer's array of UpgradeDescriptor's.
* 
* Gets and Sets them.
* 
*/
class UpgradeDescriptorArrayManager {

public:

	UpgradeDescriptorArrayManager(UpgradeDescriptor** upgradeDescriptorArray);
	~UpgradeDescriptorArrayManager() = default;

	uint32_t GetUpgradeUint32_t(std::string name);
	bool GetUpgradeBool8(std::string name);
	float GetUpgradeFloat(std::string name);

	bool SetUpgradeUint32_t(std::string name, uint32_t value);
	bool SetUpgradeBool8(std::string name, bool value);
	bool SetUpgradeFloat(std::string name, float value);

    uint32_t GetUpgradeUint32_t(Upgrades index);
    bool GetUpgradeBool8(Upgrades index);
    float GetUpgradeFloat(Upgrades index);

    bool SetUpgradeUint32_t(Upgrades index, uint32_t value);
    bool SetUpgradeBool8(Upgrades index, bool value);
    bool SetUpgradeFloat(Upgrades index, float value);

protected:

	Vftables udam_vftables;

	UpgradeDescriptor** udam_upgradeDescriptorArray;

	void* GetUpgradeByName(uintptr_t type, std::string name);

    void* GetUpgradeByIndex(Upgrades index);

	bool SetUpgradeByName(uintptr_t type, std::string name, uint8_t* value, uint32_t valueSize);

    bool SetUpgradeByIndex(Upgrades index, uint8_t* value, uint32_t valueSize);

};

class Cheats;

/*
* 
* Class: DXHR
* 
* This class generally contains any and everything you'd need to change an aspect of Deus Ex's game state.
* 
* It contains pointers and helper functions.
* 
*/
class DXHR
{

public:

	DXHR();
	~DXHR() = default;

	float* GetPlayerHealth();

    int* GetPlayerAmmo();

	std::unique_ptr<UpgradeDescriptorArrayManager> UDAM;

    UpgradeDescriptorArrayManager* operator->() {

        this->UDAM = std::make_unique<UpgradeDescriptorArrayManager>(this->GetUpgradeDescriptorArray());

    }

private:

    friend class Cheats;

	std::map<std::string, uintptr_t> dx_offsets;

    Vftables dx_vftables;

    bool IsPtrReadable(void* pointer);

	uintptr_t GetNeActorPlayer();

	uintptr_t GetNeActorPlayerHealthSystem();

    uintptr_t GetInventoryPlayer();

    uintptr_t GetPlayerPrimaryWeapon();

    uint16_t GetPlayerPrimaryWeaponId();

    uintptr_t GetPrimaryWeaponAmmo();

    char* GetPrimaryWeaponDamage();

    char* GetPrimaryWeaponRateOfFire();

    bool* GetPrimaryWeaponLaserSight();

    bool* GetPrimaryWeaponSilencer();

	UpgradeDescriptor** GetUpgradeDescriptorArray();

};

class Cheats {

public:

    DXHR dxhr;

    void Invincible(bool enable);

    void NoEnergyCost(bool enable);

    void SetAmmo(int ammo);

    void SetHealth(float health);

    void NoRecoil(bool enable);

    void HackingUpgrades(bool enable);

    void SetInventoryDimensions(int width, int height);

    void AllCheats(bool enable);

    void SetWeaponDamage(char damage);

    void SetWeaponRateOfFire(char rate);

    void SetWeaponLaserSight(bool enable);

    void SetWeaponSilencer(bool enable);

};