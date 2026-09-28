#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HSWeaponComponent.generated.h"

class UHSWeaponData;

UCLASS(Abstract, ClassGroup=(WeaponComponent))
class HOARDSURVIVOR_API UHSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHSWeaponComponent();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire(const FVector StartLocation, const FVector Direction, const float Range, const float DamageAmount) PURE_VIRTUAL(UHSWeaponComponent::Fire,);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void InitWeapon(const UHSWeaponData* WeaponData){}
protected:
	virtual void ApplyDamage(const float DamageAmount,const FHitResult& HitResult);
	
	
};
