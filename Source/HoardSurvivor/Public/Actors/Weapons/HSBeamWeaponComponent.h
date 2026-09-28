#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/HSWeaponComponent.h"
#include "HSBeamWeaponComponent.generated.h"

UCLASS(ClassGroup=(WeaponComponent), meta = (BlueprintSpawnableComponent), Blueprintable)
class HOARDSURVIVOR_API UHSBeamWeaponComponent : public UHSWeaponComponent
{
	GENERATED_BODY()
	
public:
	virtual void Fire(const FVector StartLocation, const FVector Direction, const float Range, const float DamageAmount) override;
	
};
