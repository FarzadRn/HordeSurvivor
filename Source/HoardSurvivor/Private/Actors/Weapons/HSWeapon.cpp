#include "Actors/Weapons/HSWeapon.h"
#include "Actors/Weapons/HSWeaponComponent.h"
#include "Actors/Weapons/HSWeaponData.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"

AHSWeapon::AHSWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);
}

void AHSWeapon::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData, TEXT("%s has no WeaponData"), *GetName());


	const TSubclassOf<UHSWeaponComponent> WeaponComponentClass = WeaponData->GetWeaponClass();
	checkf(WeaponComponentClass, TEXT("%s has no WeaponComponent Class for WeaponComponent."), *GetName());

	WeaponComponent = Cast<UHSWeaponComponent>(
		AddComponentByClass(WeaponComponentClass, false, FTransform::Identity, false));
	checkf(WeaponComponent, TEXT("%s failed to assign its WeaponComponent"), *GetName());

	WeaponComponent->InitWeapon(WeaponData);

	CurrentMagAmmo = WeaponData->MagazineSize;
	CurrentReserveAmmo = WeaponData->MaxReserveAmmo;
	
}

void AHSWeapon::StartFire()
{
	const double CooldownSeconds = FMath::Max(0.0, GameTimeWhenNextShotIsAllowed - GetWorld()->GetTimeSeconds());
	
	if (CooldownSeconds <= 0.0)
	{
		FireShot();
		if (WeaponData->bIsAutomatic)
		{
			GetWorldTimerManager().SetTimer(FireTimer, this, &AHSWeapon::FireShot, WeaponData->TimeBetweenShots,true);
		}
	}
	else if (WeaponData->bIsAutomatic)
	{
		GetWorldTimerManager().SetTimer(FireTimer, this, &AHSWeapon::FireShot, WeaponData->TimeBetweenShots,true, static_cast<float>(CooldownSeconds));
	}
}

void AHSWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
}

void AHSWeapon::FireShot()
{
	if (bIsReloading) return;
	
	if (CurrentMagAmmo <= 0)
	{
		Reload();
		return;
	}
	
	// this shall be replaced by UI for now it is here for dev feedback
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString::Printf(TEXT("%d Ammo left in mag"), CurrentMagAmmo));
	}
	

	FVector ProjectileSpawnOrigin = Muzzle->GetComponentLocation();
	FRotator AimDirection = Muzzle->GetComponentRotation();
	
	WeaponComponent->Fire(ProjectileSpawnOrigin, AimDirection.Vector(), WeaponData->Range, WeaponData->Damage);
	
	CurrentMagAmmo--;
	GameTimeWhenNextShotIsAllowed = GetWorld()->GetTimeSeconds() + WeaponData->TimeBetweenShots;
}

void AHSWeapon::Reload()
{
	if (bIsReloading) return;
	if (CurrentMagAmmo >= WeaponData->MagazineSize || CurrentReserveAmmo <= 0) return;
	
	// this shall be replaced by UI for now it is here for dev feedback
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,1.f,FColor::Blue,TEXT("Reloading"));
	}
	
	bIsReloading = true;
	GetWorldTimerManager().SetTimer(ReloadTimer, this, &AHSWeapon::FinishReload, WeaponData->ReloadTime, false);
}

void AHSWeapon::FinishReload()
{
	const int32 AmmoNeededToFillMag = WeaponData->MagazineSize - CurrentMagAmmo;
	const int32 AmmoTakenFromReserveToFillMag = FMath::Min(AmmoNeededToFillMag, CurrentReserveAmmo);
	//Play animation maybe here
	CurrentMagAmmo += AmmoTakenFromReserveToFillMag;
	CurrentReserveAmmo -= AmmoTakenFromReserveToFillMag;
	bIsReloading = false;
}

void AHSWeapon::AddAmmo(int32 Amount)
{
	CurrentReserveAmmo = FMath::Clamp(CurrentReserveAmmo + Amount, 0, WeaponData->MaxReserveAmmo);
}
