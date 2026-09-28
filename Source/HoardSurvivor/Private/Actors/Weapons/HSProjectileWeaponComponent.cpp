#include "Actors/Weapons/HSProjectileWeaponComponent.h"
#include "Actors/Weapons/HSWeaponData.h"
#include "Subsystems/HSProjectileSubsystem.h"
#include "Actors/Weapons/Projectiles/HSProjectile.h"


void UHSProjectileWeaponComponent::InitWeapon(const UHSWeaponData* WeaponData)
{
	if (WeaponData)
	{
		ProjectileClass = WeaponData->ProjectileClass;
	}
}

void UHSProjectileWeaponComponent::Fire(const FVector StartLocation, const FVector Direction, const float Range, const float DamageAmount)
{
	if (UHSProjectileSubsystem* SubSystem = GetWorld()->GetSubsystem<UHSProjectileSubsystem>())
	{
		SubSystem->SpawnProjectile(ProjectileClass,StartLocation,Direction, DamageAmount, GetOwner());
	}
}