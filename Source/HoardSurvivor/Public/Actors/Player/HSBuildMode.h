#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HSBuildMode.generated.h"

class AHSPlayer;
class AHSBuildPreview;
class AHSBuildable;
class UStaticMesh;

UCLASS(Blueprintable, ClassGroup = (Component), meta = (BlueprintSpawnableComponent))
class HOARDSURVIVOR_API UHSBuildMode : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UHSBuildMode();
		
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "HelperFunction")
	int32 CycleIndex(float InputValue, int32 CurrentIndex, int32 MaxIndex);
	UFUNCTION(BlueprintCallable, Category = "HelperFunction")
	UStaticMesh* GetStaticMeshOfClass(TSubclassOf<AHSBuildable> BuildableClass);
protected:
	UFUNCTION(BlueprintCallable, Category = "BuildMode")
	void EnterBuildMode();
	UFUNCTION(BlueprintCallable, Category = "BuildMode")
	void ExitBuildMode();
	
	void UpdatePreview();
	UFUNCTION(BlueprintCallable, Category = "BuildMode")
	void RotateBuilding(float Direction);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildMode")
	TSubclassOf<AHSBuildPreview> PreviewClass;
	UPROPERTY(Transient, BlueprintReadOnly, Category = "BuildMode")
	TObjectPtr<AHSBuildPreview> Preview;

	UPROPERTY()
	TObjectPtr<AHSPlayer> Player;
	FCollisionQueryParams LineTraceCollisionParams;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BuildMode")
	float LineTraceDistance = 700.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuildMode")
	FRotator BuildRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BuildMode")
	float RotationStep = 5.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuildMode")
	FVector BuildLocation = FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuildMode")
	bool bCanBuildAtLocation = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuildMode")
	bool bIsInBuildMode = false;
	

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
