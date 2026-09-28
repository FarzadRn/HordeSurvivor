#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSProjectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class HOARDSURVIVOR_API AHSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHSProjectile();
	
	void LaunchProjectile(const FVector& Location, const FVector& Direction, float InDamage, AActor* Weapon);
	void ReturnToPool();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnStop(const FHitResult& ImpactResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	TObjectPtr<USphereComponent> SphereCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	float InitialProjectileSpeed = 2000.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	float MaxProjectileSpeed = 2000.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Custom")
	float ProjectileLifeSpan = 3.f;
	FTimerHandle LifeSpanTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	float ProjectileGravityScale = 0.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Custom", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DamageLossPerHit = 0.35f;
	
	UPROPERTY()
	TArray<TObjectPtr<AActor>> IgnoredActors;
	//Damage is set from Data Asset. this here so Projectile knows what to do when another target is hit
	float Damage = 0.f;
	bool bIsActive = false;
	
};
