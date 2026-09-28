#include "Actors/Weapons/Projectiles/HSProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Subsystems/HSProjectileSubsystem.h"
#include "TimerManager.h"
#include "Core/HSDamageable.h"

AHSProjectile::AHSProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("SphereCollision"));
	SphereCollision->InitSphereRadius(5.f);
	RootComponent = SphereCollision;
	SphereCollision->SetCollisionProfileName(TEXT("Projectile"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(SphereCollision);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = SphereCollision;
	ProjectileMovement->InitialSpeed = InitialProjectileSpeed;
	ProjectileMovement->MaxSpeed = MaxProjectileSpeed;
	ProjectileMovement->ProjectileGravityScale = ProjectileGravityScale;
	ProjectileMovement->bRotationFollowsVelocity = true;
	
}

void AHSProjectile::LaunchProjectile(const FVector& Location, const FVector& Direction, float InDamage, AActor* Weapon)
{
	Damage = InDamage;
	
	SetActorLocationAndRotation(Location, Direction.Rotation(), false, nullptr, ETeleportType::TeleportPhysics);
	SetActorHiddenInGame(false);
	
	IgnoredActors.Reset();
	SphereCollision->ClearMoveIgnoreActors();
	if (Weapon)
	{
		IgnoredActors.Add(Weapon);
		SphereCollision->IgnoreActorWhenMoving(Weapon,true);
		
		if (AActor* Shooter = Weapon->GetOwner())
		{
			IgnoredActors.Add(Shooter);
			SphereCollision->IgnoreActorWhenMoving(Shooter, true);
		}
	}
	
	ProjectileMovement->SetUpdatedComponent(SphereCollision);
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
	ProjectileMovement->Activate(true);
	
	bIsActive = true;
	SetActorEnableCollision(true);
	
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &AHSProjectile::ReturnToPool, ProjectileLifeSpan, false);
	
}

void AHSProjectile::ReturnToPool()
{
	if (!bIsActive) return;
	bIsActive = false;
	
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	
	ProjectileMovement->StopMovementImmediately();
	ProjectileMovement->Deactivate();
	
	GetWorldTimerManager().ClearTimer(LifeSpanTimer);
	
	if (UHSProjectileSubsystem* Subsystem = GetWorld()->GetSubsystem<UHSProjectileSubsystem>())
	{
		Subsystem->ReturnProjectile(this);
	}
}

void AHSProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AHSProjectile::OnOverlap);
	ProjectileMovement->OnProjectileStop.AddDynamic(this, &AHSProjectile::OnStop);
}

void AHSProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActive || !OtherActor || IgnoredActors.Contains(OtherActor)) return;
	if (!OtherActor->Implements<UHSDamageable>()) return;
	
	IgnoredActors.Add(OtherActor);
	IHSDamageable::Execute_TakeDamage(OtherActor,Damage);
	Damage *= (1.f -DamageLossPerHit);
}

void AHSProjectile::OnStop(const FHitResult& ImpactResult)
{
	ReturnToPool();
}
