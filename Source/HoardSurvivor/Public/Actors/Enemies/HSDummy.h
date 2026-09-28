#pragma once

#include "CoreMinimal.h"
#include "Core/HSDamageable.h"
#include "GameFramework/Actor.h"
#include "HSDummy.generated.h"

UCLASS()
class HOARDSURVIVOR_API AHSDummy : public AActor, public IHSDamageable
{
	GENERATED_BODY()
	
public:	
	AHSDummy();

	virtual void TakeDamage_Implementation(const float DamageAmount) override;
private:
	float Health = 10000;
	float MaxHealth = 10000;
};
