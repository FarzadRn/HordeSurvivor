// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSBuildable.generated.h"

class UStaticMeshComponent;

UCLASS()
class HOARDSURVIVOR_API AHSBuildable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHSBuildable();
	UStaticMesh* GetMesh() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
