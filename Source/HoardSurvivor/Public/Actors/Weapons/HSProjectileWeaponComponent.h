#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/HSWeaponComponent.h"
#include "HSProjectileWeaponComponent.generated.h"

class AHSProjectile;

UCLASS(ClassGroup=(WeaponComponent), meta = (BlueprintSpawnableComponent), Blueprintable)
class HOARDSURVIVOR_API UHSProjectileWeaponComponent : public UHSWeaponComponent
{
	GENERATED_BODY()
	
public:
	virtual void Fire(const FVector StartLocation, const FVector Direction, const float Range, const float DamageAmount) override;
	virtual void InitWeapon(const UHSWeaponData* WeaponData) override;
	
private:
	UPROPERTY()
	TSubclassOf<AHSProjectile> ProjectileClass;
	
};
