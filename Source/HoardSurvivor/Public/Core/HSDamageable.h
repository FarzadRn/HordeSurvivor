#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HSDamageable.generated.h"

UINTERFACE(MinimalAPI)
class UHSDamageable : public UInterface
{
	GENERATED_BODY()
};

class HOARDSURVIVOR_API IHSDamageable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TakeDamage(const float DamageAmount);
};
