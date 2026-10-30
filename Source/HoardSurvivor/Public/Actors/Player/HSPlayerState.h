#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ActiveGameplayEffectHandle.h"
#include "HSPlayerState.generated.h"

class UAbilitySystemComponent;
class UHSPlayerAttributeSet;
class UHSTalentData;

UCLASS()
class HOARDSURVIVOR_API AHSPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AHSPlayerState(const FObjectInitializer& ObjectInitializer);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Sets talent's rank and re-applies effect. Rank 0 removes it.
	UFUNCTION(BlueprintCallable, Category = "Talents")
	void SetTalentRank(UHSTalentData* Talent, int32 NewRank);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UHSPlayerAttributeSet> PlayerAttributeSet;
	
	//Owned talents and their ranks, applied at BeginPlay, later this comes from save gam
	UPROPERTY(EditAnywhere, Category = "Talents")
	TMap<TObjectPtr<UHSTalentData>, int32> TalentRanks;
	
private:
	void ApplyTalentEffect(UHSTalentData* Talent, int32 Rank);
	
	UPROPERTY(Transient)
	TMap<TObjectPtr<UHSTalentData>, FActiveGameplayEffectHandle> TalentEffectHandles;
};
