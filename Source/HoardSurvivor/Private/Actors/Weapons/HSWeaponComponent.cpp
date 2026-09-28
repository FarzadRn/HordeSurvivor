#include "Actors/Weapons/HSWeaponComponent.h"
#include "Core/HSDamageable.h"

UHSWeaponComponent::UHSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHSWeaponComponent::ApplyDamage(const float DamageAmount, const FHitResult& HitResult)
{
	AActor* Target = HitResult.GetActor();
	if (Target && Target->Implements<UHSDamageable>())
	{
		IHSDamageable::Execute_TakeDamage(Target, DamageAmount);
	}
}
