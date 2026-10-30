#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HSPlayer.generated.h"

class UCameraComponent;

UCLASS()
class HOARDSURVIVOR_API AHSPlayer : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHSPlayer();
	TOptional<FVector> LookForViableLocation(float TraceRange, FCollisionQueryParams& CollisionParams);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	UFUNCTION(BlueprintCallable, Category = "InputAction", meta = (AllowPrivateAccess = true))
	void Move(FVector2D InputVector);
	UFUNCTION(BlueprintCallable, Category = "InputAction", meta = (AllowPrivateAccess = true))
	void Look(FVector2D InputVector);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;
public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
