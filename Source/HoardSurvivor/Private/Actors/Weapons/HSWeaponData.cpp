#include "Actors/Weapons/HSWeaponData.h"
#include "Actors/Weapons/HSBeamWeaponComponent.h"
#include "Actors/Weapons/HSProjectileWeaponComponent.h"
#include "Actors/Weapons/HSConeWeaponComponent.h"
TSubclassOf<UHSWeaponComponent> UHSWeaponData::GetWeaponClass() const
{
	switch (WeaponType)
	{
	case EHSWeaponType::Beam: return UHSBeamWeaponComponent::StaticClass();
	case EHSWeaponType::Projectile: return UHSProjectileWeaponComponent::StaticClass();
	case EHSWeaponType::Cone: return UHSConeWeaponComponent::StaticClass();
	default: return nullptr;
	}
}
