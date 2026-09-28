#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HSWeaponData.generated.h"

class UHSWeaponComponent;
class AHSProjectile;

UENUM(BlueprintType)
enum class EHSWeaponType : uint8
{
	Beam,
	Projectile,
	Cone
};

UCLASS(BlueprintType)
class HOARDSURVIVOR_API UHSWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FText DisplayName = FText::FromString("DefaultName");
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "0.0"))
	float Damage = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool bIsAutomatic = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mag", meta = (ClampMin = "1"))
	int32 MagazineSize = 30;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mag", meta = (ClampMin = "0"))
	int32 MaxReserveAmmo = 90;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mag", meta = (ClampMin = "0.0"))
	float ReloadTime = 1.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "0.0"))
	float Range = 10000.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon")
	EHSWeaponType WeaponType = EHSWeaponType::Beam;
	
	UFUNCTION(BlueprintPure, Category = "Weapon")
	TSubclassOf<UHSWeaponComponent> GetWeaponClass() const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Projectile", meta = (EditCondition = "WeaponType == EHSWeaponType::Projectile", EditConditionHides))
		TSubclassOf<AHSProjectile> ProjectileClass = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (ClampMin = "0.01",EditCondition = "WeaponType == EHSWeaponType::Projectile", EditConditionHides))
	float TimeBetweenShots = 1.f;
};
