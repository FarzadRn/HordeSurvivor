#include "Subsystems/HSProjectileSubsystem.h"
#include "Actors/Weapons/Projectiles/HSProjectile.h"

AHSProjectile* UHSProjectileSubsystem::SpawnProjectile(TSubclassOf<AHSProjectile> ProjectileClass, const FVector& Location, const FVector& Direction, float Damage, AActor* Shooter)
{
	if (!ProjectileClass) return nullptr;
	
	AHSProjectile* Projectile = nullptr;
	FHSProjectilePool& Pool = ProjectilePools.FindOrAdd(ProjectileClass);
	
	if (Pool.Projectiles.Num() > 0)
	{
		Projectile = Pool.Projectiles.Pop();
	}
	else
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Projectile = GetWorld()->SpawnActor<AHSProjectile>(ProjectileClass, Location, Direction.Rotation(), SpawnInfo);
	}
	
	if (Projectile)
	{
		Projectile->LaunchProjectile(Location, Direction, Damage, Shooter);
	}
	return Projectile;
}

void UHSProjectileSubsystem::ReturnProjectile(AHSProjectile* Projectile)
{
	if (Projectile)
	{
		ProjectilePools.FindOrAdd(Projectile->GetClass()).Projectiles.Add(Projectile);
	}
}