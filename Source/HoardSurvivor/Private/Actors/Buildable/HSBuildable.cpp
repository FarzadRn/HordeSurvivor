// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Buildable/HSBuildable.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHSBuildable::AHSBuildable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

}

UStaticMesh* AHSBuildable::GetMesh() const
{
	return StaticMesh->GetStaticMesh();
}

// Called when the game starts or when spawned
void AHSBuildable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHSBuildable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

