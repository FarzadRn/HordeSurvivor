#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HSPlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class HOARDSURVIVOR_API UHSPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UHSPlayerAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FGameplayAttributeData DamageMultiplier;
	ATTRIBUTE_ACCESSORS(UHSPlayerAttributeSet, DamageMultiplier)
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FGameplayAttributeData FireRateMultiplier;
	ATTRIBUTE_ACCESSORS(UHSPlayerAttributeSet, FireRateMultiplier)
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FGameplayAttributeData ReloadSpeedMultiplier;
	ATTRIBUTE_ACCESSORS(UHSPlayerAttributeSet, ReloadSpeedMultiplier)
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
