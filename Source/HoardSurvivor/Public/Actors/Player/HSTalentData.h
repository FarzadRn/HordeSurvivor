#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HSTalentData.generated.h"

class UGameplayEffect;


UCLASS(Blueprintable)
class HOARDSURVIVOR_API UHSTalentData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Talent")
	FText DisplayName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Talent")
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Talent", meta = (ClampMin = 1))
	int32 MaxRank = 5;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Talent")
	TSubclassOf<UGameplayEffect> Effect;
};
