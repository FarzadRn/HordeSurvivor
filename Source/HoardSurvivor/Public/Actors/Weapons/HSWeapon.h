#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSWeapon.generated.h"

class UHSWeaponData;
class UArrowComponent;
class UHSWeaponComponent;
struct FGameplayAttribute;

UCLASS(Abstract)
class HOARDSURVIVOR_API AHSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AHSWeapon();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopFire();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AddAmmo(int32 Amount);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UHSWeaponData> WeaponData;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UHSWeaponComponent> WeaponComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UArrowComponent> Muzzle;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Weapon")
	int32 CurrentMagAmmo = 0;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Weapon")
	int32 CurrentReserveAmmo = 0;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Weapon")
	bool bIsReloading = false;
	
private:
	void FireShot();
	void FinishReload();
	// Attribute value on the owner's Ability System Component, or 1 if the owner has none (enemies, towers)
	float GetOwnerMultiplier(const FGameplayAttribute& Attribute) const;
	float GetTimeBetweenShots() const;
	float GetReloadTime() const;
	
	FTimerHandle FireTimer;
	FTimerHandle ReloadTimer;
	double GameTimeWhenNextShotIsAllowed = 0.0;
};
