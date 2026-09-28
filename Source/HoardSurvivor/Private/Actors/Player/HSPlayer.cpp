// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Player/HSPlayer.h"
#include "Camera/CameraComponent.h"

// Sets default values
AHSPlayer::AHSPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	//prevent body from rotating in Y axis
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
}

// Called when the game starts or when spawned
void AHSPlayer::BeginPlay()
{
	Super::BeginPlay();
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
