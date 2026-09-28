#include "Actors/Player/HSBuildMode.h"
#include "Actors/Player/HSPlayer.h"
#include "Actors/Buildable/HSBuildPreview.h"
#include "Engine/World.h"

UHSBuildMode::UHSBuildMode()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

int32 UHSBuildMode::CycleIndex(float InputValue, int32 CurrentIndex, int32 MaxIndex)
{
	int32 Direction = FMath::Sign(InputValue);
	if (MaxIndex == 0)
	{
		return 0;
	}
	return (CurrentIndex + Direction + MaxIndex) % MaxIndex;
}

UStaticMesh* UHSBuildMode::GetStaticMeshOfClass(TSubclassOf<AHSBuildable> BuildableClass)
{
	if (!BuildableClass) return nullptr;

	const AHSBuildable* CDO = BuildableClass->GetDefaultObject<AHSBuildable>();
	return CDO ? CDO->GetMesh() : nullptr;
}

void UHSBuildMode::EnterBuildMode()
{
	bIsInBuildMode = true;
	SetComponentTickEnabled(true);
}

void UHSBuildMode::ExitBuildMode()
{
	bIsInBuildMode = false;
	SetComponentTickEnabled(false);
	if (Preview)
	{
		Preview->Destroy();
		Preview = nullptr;
	}
}

void UHSBuildMode::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AHSPlayer>(GetOwner());
}

void UHSBuildMode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TOptional<FVector> PotentialLocation = Player->LookForViableLocation(LineTraceDistance, LineTraceCollisionParams);
	if (PotentialLocation.IsSet())
	{
		BuildLocation = PotentialLocation.GetValue();
		bCanBuildAtLocation = true; //this line will be removed after adding collision check
		UpdatePreview();
	}
	else
	{
		if (Preview) Preview->SetActorHiddenInGame(true);
		bCanBuildAtLocation = false;
	}
}

void UHSBuildMode::UpdatePreview()
{
	if (!Preview)
	{
		Preview = GetWorld()->SpawnActor<AHSBuildPreview>(PreviewClass, BuildLocation, FRotator::ZeroRotator);
		if (!Preview) return;
	}
	Preview->SetActorLocation(BuildLocation);
	Preview->SetActorRotation(BuildRotation);
	Preview->SetActorHiddenInGame(false);
}

void UHSBuildMode::RotateBuilding(float Direction)
{
	//if Direction .3 then Rotation Amount = 1(Direction) * 5(RotationStep) = 5 degrees
	float RotationAngle = FMath::Sign(Direction) * RotationStep;
	BuildRotation.Yaw += RotationAngle;
}
