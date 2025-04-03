#include "pch.h"
#include "DXHR.h"

/* Vftables Functions */

Vftables::Vftables() {

	uintptr_t base = reinterpret_cast<uintptr_t>(LoadLibraryA("DXHRDC.exe"));

	this->NeActor = base + 0x6B3B60;
	this->NeActorPlayer = base + 0x6B3DE0;
	this->NeActorNpc = base + 0x6B3C78;

	this->AugmentationSystem = base + 0x6A5934;

	this->HealthSystem = base + 0x6A621C;

	this->UpgradeDescriptor_uint32_t = base + 0x6A58CC;
	this->UpgradeDescriptor_bool8 = base + 0x6A58EC;
	this->UpgradeDescriptor_float = base + 0x6A58AC;

	this->GrabSystem = base + 0x6A611C;

	this->InventoryContainer = base + 0x6B2D8C;
	this->InventoryPlayer = base + 0x6A63E0;

}

/* UpgradeDescriptorArrayManager Functions */

UpgradeDescriptorArrayManager::UpgradeDescriptorArrayManager(UpgradeDescriptor** upgradeDescriptorArray) : udam_upgradeDescriptorArray(upgradeDescriptorArray) {}


void* UpgradeDescriptorArrayManager::GetUpgradeByName(uintptr_t type, std::string name) {

	for (int i = 0; i < static_cast<size_t>(Upgrades::NUM_UPGRADE_DESCRIPTORS); i++) {

		UpgradeDescriptor* upgrade = this->udam_upgradeDescriptorArray[i];

		if (upgrade->type == type) {

			if (std::strcmp(name.c_str(), upgrade->name) == 0) return upgrade->value;

		}

	}

	return nullptr;

}

void* UpgradeDescriptorArrayManager::GetUpgradeByIndex(Upgrades index) {

	if (static_cast<size_t>(index) > static_cast<size_t>(Upgrades::NUM_UPGRADE_DESCRIPTORS)) return nullptr;

	UpgradeDescriptor* upgrade = this->udam_upgradeDescriptorArray[static_cast<size_t>(index)];

	if (upgrade == nullptr) return nullptr;

	if (upgrade->type == this->udam_vftables.UpgradeDescriptor_uint32_t ||
		upgrade->type == this->udam_vftables.UpgradeDescriptor_bool8 ||
		upgrade->type == this->udam_vftables.UpgradeDescriptor_float) return upgrade->value;

	return nullptr;

}

uint32_t UpgradeDescriptorArrayManager::GetUpgradeUint32_t(std::string name) {

	uint32_t* value = reinterpret_cast<uint32_t*>(this->GetUpgradeByName(this->udam_vftables.UpgradeDescriptor_uint32_t, name));

	return (value != nullptr ? *value : 0);

}

uint32_t UpgradeDescriptorArrayManager::GetUpgradeUint32_t(Upgrades index) {

	uint32_t result = *reinterpret_cast<uint32_t*>(this->GetUpgradeByIndex(index));

	return result;

}


bool UpgradeDescriptorArrayManager::GetUpgradeBool8(std::string name) {

	bool* value = reinterpret_cast<bool*>(this->GetUpgradeByName(this->udam_vftables.UpgradeDescriptor_bool8, name));

	return (value != nullptr ? *value : false);

}

bool UpgradeDescriptorArrayManager::GetUpgradeBool8(Upgrades index) {

	bool result = *reinterpret_cast<bool*>(this->GetUpgradeByIndex(index));

	return result;

}

float UpgradeDescriptorArrayManager::GetUpgradeFloat(std::string name) {

	float* value = reinterpret_cast<float*>(this->GetUpgradeByName(this->udam_vftables.UpgradeDescriptor_float, name));

	return (value != nullptr ? *value : 0.0f);

}

float UpgradeDescriptorArrayManager::GetUpgradeFloat(Upgrades index) {

	float result = *reinterpret_cast<float*>(this->GetUpgradeByIndex(index));

	return result;

}

bool UpgradeDescriptorArrayManager::SetUpgradeByName(uintptr_t type, std::string name, uint8_t* value, uint32_t valueSize) {

	for (int i = 0; i < static_cast<size_t>(Upgrades::NUM_UPGRADE_DESCRIPTORS); i++) {

		UpgradeDescriptor* upgrade = this->udam_upgradeDescriptorArray[i];

		if (upgrade->type == type) {

			if (std::strcmp(name.c_str(), upgrade->name) == 0) {

				if (std::memcpy(upgrade->value, value, valueSize) == upgrade->value) return true;

				else return false;

			}

		}

	}

	return false;

}

bool UpgradeDescriptorArrayManager::SetUpgradeByIndex(Upgrades index, uint8_t* value, uint32_t valueSize) {

	if (static_cast<size_t>(index) < static_cast<size_t>(Upgrades::NUM_UPGRADE_DESCRIPTORS)) return false;

	UpgradeDescriptor* upgrade = this->udam_upgradeDescriptorArray[static_cast<size_t>(index)];

	if (upgrade == nullptr) return false;

	if (upgrade->type == this->udam_vftables.UpgradeDescriptor_uint32_t ||
		upgrade->type == this->udam_vftables.UpgradeDescriptor_bool8 ||
		upgrade->type == this->udam_vftables.UpgradeDescriptor_float) {

		if (std::memcpy(upgrade->value, value, valueSize) == upgrade->value) return true;

		else return false;

	}

	return false;

}

bool UpgradeDescriptorArrayManager::SetUpgradeUint32_t(std::string name, uint32_t value) {

	return this->SetUpgradeByName(this->udam_vftables.UpgradeDescriptor_uint32_t, name, reinterpret_cast<uint8_t*>(&value), sizeof(value));

}

bool UpgradeDescriptorArrayManager::SetUpgradeUint32_t(Upgrades index, uint32_t value) {

	return this->SetUpgradeByIndex(index, reinterpret_cast<uint8_t*>(&value), sizeof(uint32_t));

}


bool UpgradeDescriptorArrayManager::SetUpgradeBool8(std::string name, bool value) {

	return this->SetUpgradeByName(this->udam_vftables.UpgradeDescriptor_bool8, name, reinterpret_cast<uint8_t*>(&value), sizeof(value));

}

bool UpgradeDescriptorArrayManager::SetUpgradeBool8(Upgrades index, bool value) {

	return this->SetUpgradeByIndex(index, reinterpret_cast<uint8_t*>(&value), sizeof(bool));

}

bool UpgradeDescriptorArrayManager::SetUpgradeFloat(std::string name, float value) {

	return this->SetUpgradeByName(this->udam_vftables.UpgradeDescriptor_float, name, reinterpret_cast<uint8_t*>(&value), sizeof(value));

}

bool UpgradeDescriptorArrayManager::SetUpgradeFloat(Upgrades index, float value) {

	return this->SetUpgradeByIndex(index, reinterpret_cast<uint8_t*>(&value), sizeof(float));

}

/* DXHR Functions */

DXHR::DXHR() {

	this->dx_offsets["base"] = reinterpret_cast<uintptr_t>(LoadLibraryA("DXHRDC.exe"));

	this->dx_offsets["base_to_MessageSystem"] = 0x261530;

	this->dx_offsets["base_to_GlobalManagement"] = 0x01602738;

	this->dx_offsets["base_to_PlayerCoordinates"] = 0x1608240; // 3 floats (X, Y, Z)

	this->dx_offsets["GlobalManagement_to_NeActorPlayer"] = 0x14;

	this->dx_offsets["NeActorPlayer_to_HealthSystem"] = 0x64;

	this->dx_offsets["NeActorPlayer_to_AugmentationSystem"] = 0x130;

	this->dx_offsets["NeActorPlayer_to_InventoryPlayer"] = 0x60;

	this->dx_offsets["HealthSystem_to_Health"] = 0x5C;

	this->dx_offsets["InventoryPlayer_to_PrimaryWeapon"] = 0x14;

	this->dx_offsets["PrimaryWeapon_to_Container"] = 0x70;

	this->dx_offsets["Container_to_Ammo"] = 0x14;

	this->dx_offsets["Container_to_Damage"] = 0x17;

	this->dx_offsets["Container_to_RateOfFire"] = 0x19;

	this->dx_offsets["Container_to_LaserSight"] = 0x1B;

	this->dx_offsets["Container_to_Silencer"] = 0x1C;

	this->dx_offsets["AugmentationSystem_to_UpgradeDescriptorArray"] = 0x40;

	this->UDAM = std::make_unique<UpgradeDescriptorArrayManager>(this->GetUpgradeDescriptorArray());

}

/* Public */

float* DXHR::GetPlayerHealth() {

	float* result = reinterpret_cast<float*>(this->GetNeActorPlayerHealthSystem() + this->dx_offsets["HealthSystem_to_Health"]);

	if (!this->IsPtrReadable(result)) {

		return nullptr;

	}

	return result;

}

int* DXHR::GetPlayerAmmo() {

	return reinterpret_cast<int*>(this->GetPrimaryWeaponAmmo());

}

/* Private */

bool DXHR::IsPtrReadable(void* pointer) {

	if (pointer == nullptr) return false;

	__try {

		volatile char test = *(char*)pointer;

		return true;

	}
	__except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {

		return false;

	}

}

uintptr_t DXHR::GetNeActorPlayer() {

	uintptr_t* result = nullptr;

	result = reinterpret_cast<uintptr_t*>(this->dx_offsets["base"] + this->dx_offsets["base_to_GlobalManagement"]);

	if (!this->IsPtrReadable(result)) return 0;

	result = reinterpret_cast<uintptr_t*>(*result + this->dx_offsets["GlobalManagement_to_NeActorPlayer"]);

	if (!this->IsPtrReadable(result)) return 0;

	return *result;

}

uintptr_t DXHR::GetInventoryPlayer() {

	uintptr_t* result = nullptr;

	result = reinterpret_cast<uintptr_t*>(this->GetNeActorPlayer() + this->dx_offsets["NeActorPlayer_to_InventoryPlayer"]);

	if (!this->IsPtrReadable(result)) return 0;

	return *result;

}

uintptr_t DXHR::GetPlayerPrimaryWeapon() {

	uintptr_t* result = nullptr;

	result = reinterpret_cast<uintptr_t*>(this->GetInventoryPlayer() + this->dx_offsets["InventoryPlayer_to_PrimaryWeapon"]);

	if (!this->IsPtrReadable(result)) return 0;

	return *result;

}

uint16_t DXHR::GetPlayerPrimaryWeaponId() {

	uintptr_t* result = nullptr;

	result = reinterpret_cast<uintptr_t*>(this->GetPlayerPrimaryWeapon() + this->dx_offsets["PrimaryWeapon_to_Container"]);

	if (!this->IsPtrReadable(result)) return 0;

	result = reinterpret_cast<uintptr_t*>(*result);

	if (!this->IsPtrReadable(result)) return 0;

	uint16_t* weapon_id = reinterpret_cast<uint16_t*>(result);

	return *weapon_id;

}

uintptr_t DXHR::GetPrimaryWeaponAmmo() {

	uintptr_t* result = nullptr;

	result = reinterpret_cast<uintptr_t*>(this->GetPlayerPrimaryWeapon() + this->dx_offsets["PrimaryWeapon_to_Container"]);

	if (!this->IsPtrReadable(result)) return 0;

	return (*result) + this->dx_offsets["Container_to_Ammo"];

}

char* DXHR::GetPrimaryWeaponDamage() {

	uintptr_t* container = reinterpret_cast<uintptr_t*>(this->GetPlayerPrimaryWeapon() + this->dx_offsets["PrimaryWeapon_to_Container"]);

	if (!this->IsPtrReadable(container)) return nullptr;

	char* damage = reinterpret_cast<char*>((*container) + this->dx_offsets["Container_to_Damage"]);

	return damage;

}

char* DXHR::GetPrimaryWeaponRateOfFire()
{
	uintptr_t* container = reinterpret_cast<uintptr_t*>(this->GetPlayerPrimaryWeapon() + this->dx_offsets["PrimaryWeapon_to_Container"]);

	if (!this->IsPtrReadable(container)) return nullptr;

	char* rof = reinterpret_cast<char*>((*container) + this->dx_offsets["Container_to_RateOfFire"]);

	return rof;
}

bool* DXHR::GetPrimaryWeaponLaserSight()
{
	uintptr_t* container = reinterpret_cast<uintptr_t*>(this->GetPlayerPrimaryWeapon() + this->dx_offsets["PrimaryWeapon_to_Container"]);

	if (!this->IsPtrReadable(container)) return nullptr;

	bool* laserSight = reinterpret_cast<bool*>((*container) + this->dx_offsets["Container_to_LaserSight"]);

	return laserSight;
}

bool* DXHR::GetPrimaryWeaponSilencer()
{
	uintptr_t* container = reinterpret_cast<uintptr_t*>(this->GetPlayerPrimaryWeapon() + this->dx_offsets["PrimaryWeapon_to_Container"]);

	if (!this->IsPtrReadable(container)) return nullptr;

	bool* silencer = reinterpret_cast<bool*>((*container) + this->dx_offsets["Container_to_Silencer"]);

	return silencer;
}

uintptr_t DXHR::GetNeActorPlayerHealthSystem() {

	uintptr_t* result = reinterpret_cast<uintptr_t*>(this->GetNeActorPlayer() + this->dx_offsets["NeActorPlayer_to_HealthSystem"]);

	if (!this->IsPtrReadable(result)) return 0;

	return *result;

}

UpgradeDescriptor** DXHR::GetUpgradeDescriptorArray() {

	uintptr_t AugmentationSystem = this->GetNeActorPlayer() + this->dx_offsets["NeActorPlayer_to_AugmentationSystem"];

	if (!this->IsPtrReadable((void*)AugmentationSystem)) return nullptr;

	if (*reinterpret_cast<uintptr_t*>(AugmentationSystem) != this->dx_vftables.AugmentationSystem) {

		return nullptr;

	}

	UpgradeDescriptor** result = reinterpret_cast<UpgradeDescriptor**>(AugmentationSystem + this->dx_offsets["AugmentationSystem_to_UpgradeDescriptorArray"]);



	if (!this->IsPtrReadable(result)) {

		return nullptr;

	}

	return result;

}

void Cheats::Invincible(bool enable) {

	if (enable) {

		this->dxhr.UDAM->SetUpgradeFloat("PrimaryDamageTaken", 0);

	}
	else {

		this->dxhr.UDAM->SetUpgradeFloat("PrimaryDamageTaken", 0.5f);

	}

}

void Cheats::NoEnergyCost(bool enable) {

	dxhr.UDAM->SetUpgradeFloat("EnergyRegenDelay", 0);
	dxhr.UDAM->SetUpgradeFloat("EnergyRechargeRate", 90);

	dxhr.UDAM->SetUpgradeFloat("XRayEnergyCostOverTime", 0);
	dxhr.UDAM->SetUpgradeFloat("CamouflageEnergyCostOverTime", 0);
	dxhr.UDAM->SetUpgradeFloat("SilentRunEnergyCostOverTime", 0);
	dxhr.UDAM->SetUpgradeFloat("PunchThroughWallEnergyCost", 0);

	dxhr.UDAM->SetUpgradeFloat("TakeDownSingleKillEnergyCost", 0);
	dxhr.UDAM->SetUpgradeFloat("TakeDownSingleStunEnergyCost", 0);
	dxhr.UDAM->SetUpgradeFloat("TakeDownMultiKillEnergyCost", 0);
	dxhr.UDAM->SetUpgradeFloat("TakeDownMultiStunEnergyCost", 0);

	dxhr.UDAM->SetUpgradeFloat("ClaymoreEnergyCost", 0);

	dxhr.UDAM->SetUpgradeFloat("GrabHeavyObjectEnergyCost", 0);
	dxhr.UDAM->SetUpgradeFloat("ThrowHeavyObjectEnergyCost", 0);


}

void Cheats::SetAmmo(int ammo) {

	uint16_t weaponId = this->dxhr.GetPlayerPrimaryWeaponId();

	/* TODO: Add WEAPON_ID_STUN_GUN */
	if(
		weaponId == WEAPON_ID_ASSAULT_RIFLE || 
		weaponId == WEAPON_ID_HEAVY_RIFLE || 
		weaponId == WEAPON_ID_MACHINE_PISTOL ||
		weaponId == WEAPON_ID_PISTOL ||
		weaponId == WEAPON_ID_PISTOL_ARMOR_PIERCING ||
		weaponId == WEAPON_ID_SHOTGUN ||
		weaponId == WEAPON_ID_STUN_GUN ||
		weaponId == WEAPON_ID_HEAVY_RIFLE ||
		weaponId == WEAPON_ID_LASER_RIFLE ||
		weaponId == WEAPON_ID_GRENADE_LAUNCHER ||
		weaponId == WEAPON_ID_PEPS
		) {

		int* pAmmo = this->dxhr.GetPlayerAmmo();

		if (pAmmo != nullptr) {

			*pAmmo = ammo;

		}
	}

}

void Cheats::SetHealth(float health) {

	float* pHealth = this->dxhr.GetPlayerHealth();

	if (pHealth != nullptr) {

		*pHealth = health;

	}

}

void Cheats::NoRecoil(bool enable) {

	if(enable) {

		this->dxhr.UDAM->SetUpgradeFloat("FiringRecoil", 0.0f);

	}
	else {

		this->dxhr.UDAM->SetUpgradeFloat("FiringRecoil", 1.0f);

	}

}

void Cheats::HackingUpgrades(bool enable) {

	this->dxhr.UDAM->SetUpgradeUint32_t("HackingCPUCycles", 5);
	this->dxhr.UDAM->SetUpgradeUint32_t("HackingCaptureSoftwareRating", 5);
	this->dxhr.UDAM->SetUpgradeUint32_t("HackingFortifySoftwareRating", 5);
	this->dxhr.UDAM->SetUpgradeUint32_t("HackingStealthSoftwareRating", 5);
	this->dxhr.UDAM->SetUpgradeUint32_t("HackingAPIsAnalyzeLevel", 5);
	this->dxhr.UDAM->SetUpgradeUint32_t("HackingDatastoresAnalyzeLevel", 5);

}

void Cheats::SetInventoryDimensions(int width, int height) {

	this->dxhr.UDAM->SetUpgradeUint32_t("InventoryWidth", width);
	this->dxhr.UDAM->SetUpgradeUint32_t("InventoryHeight", height);

}

void Cheats::AllCheats(bool enable) {

	if (enable) {

		this->Invincible(true);
		this->NoRecoil(true);
		this->NoEnergyCost(true);
		this->HackingUpgrades(true);

	}
	else {

		this->Invincible(false);
		this->NoRecoil(false);
		this->NoEnergyCost(false);
		this->HackingUpgrades(false);

	}

}

void Cheats::SetWeaponDamage(char damage)
{

	char* pDamage = this->dxhr.GetPrimaryWeaponDamage();

	if (pDamage != nullptr) {

		*pDamage = damage;

	}

}

void Cheats::SetWeaponRateOfFire(char rate)
{

	char* pRate = this->dxhr.GetPrimaryWeaponRateOfFire();

	if (pRate != nullptr) {

		*pRate = rate;

	}

}

void Cheats::SetWeaponLaserSight(bool enable)
{

	bool* laserSight = this->dxhr.GetPrimaryWeaponLaserSight();

	if (laserSight != nullptr) {

		*laserSight = enable;

	}

}

void Cheats::SetWeaponSilencer(bool enable)
{

	bool* silencer = this->dxhr.GetPrimaryWeaponSilencer();

	if (silencer != nullptr) {

		*silencer = enable;

	}

}

