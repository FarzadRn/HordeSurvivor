#include "Actors/Player/HSPlayer.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Actors/Player/HSPlayerState.h"

AHSPlayer::AHSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	//prevent body from rotating in Y axis
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
}

void AHSPlayer::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* AHSPlayer::GetAbilitySystemComponent() const
{
	const AHSPlayerState* HSPlayerState = GetPlayerState<AHSPlayerState>();
	return HSPlayerState ? HSPlayerState->GetAbilitySystemComponent() : nullptr;
}

void AHSPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AHSPlayerState* HSPlayerState = GetPlayerState<AHSPlayerState>())
	{
		HSPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(HSPlayerState, this);
	}
}

void AHSPlayer::Move(FVector2D InputVector)
{
	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	AddMovementInput(Forward, InputVector.X);
	AddMovementInput(Right, InputVector.Y);
}

void AHSPlayer::Look(FVector2D InputVector)
{
	AddControllerYawInput(InputVector.X);
	AddControllerPitchInput(-InputVector.Y);
}

TOptional<FVector> AHSPlayer::LookForViableLocation(float TraceRange, FCollisionQueryParams& CollisionParams)
{
	FVector StartLocation = Camera->GetComponentLocation();
	FVector EndLocation = StartLocation + (Camera->GetForwardVector() * TraceRange);
	FHitResult Hit;
	CollisionParams.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		EndLocation,
		ECC_WorldStatic,
		CollisionParams);
	if (bHit)
	{
		return Hit.ImpactPoint;
	}
	//{} returns empty. "hit nothing"
	return {};
}

// Called every frame
void AHSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
