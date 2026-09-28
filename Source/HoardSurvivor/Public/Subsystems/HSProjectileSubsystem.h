#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "HSProjectileSubsystem.generated.h"

class AHSProjectile;

USTRUCT()
struct FHSProjectilePool
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<TObjectPtr<AHSProjectile>> Projectiles;
};

UCLASS()
class HOARDSURVIVOR_API UHSProjectileSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	AHSProjectile* SpawnProjectile(TSubclassOf<AHSProjectile> ProjectileClass, const FVector& Location, const FVector& Direction, float Damage, AActor* Shooter);
	void ReturnProjectile(AHSProjectile* Projectile);
	
private:
	UPROPERTY()
	TMap<TSubclassOf<AHSProjectile>, FHSProjectilePool> ProjectilePools;
	
};
