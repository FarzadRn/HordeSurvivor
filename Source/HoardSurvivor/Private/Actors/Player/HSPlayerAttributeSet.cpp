#include "Actors/Player/HSPlayerAttributeSet.h"

UHSPlayerAttributeSet::UHSPlayerAttributeSet()
{
	InitDamageMultiplier(1.f);
	InitFireRateMultiplier(1.f);
	InitReloadSpeedMultiplier(1.f);
}

void UHSPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetDamageMultiplierAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
	else if (Attribute == GetFireRateMultiplierAttribute() || Attribute == GetReloadSpeedMultiplierAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.1f);
	}
}
