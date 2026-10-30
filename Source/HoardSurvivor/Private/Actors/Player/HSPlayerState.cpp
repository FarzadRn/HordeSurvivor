#include "Actors/Player/HSPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Actors/Player/HSPlayerAttributeSet.h"
#include "Actors/Player/HSTalentData.h"

AHSPlayerState::AHSPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PlayerAttributeSet = CreateDefaultSubobject<UHSPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

UAbilitySystemComponent* AHSPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AHSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	for (const TPair<TObjectPtr<UHSTalentData>, int32>& TalentRank : TalentRanks)
	{
		ApplyTalentEffect(TalentRank.Key, TalentRank.Value);
	}
}

void AHSPlayerState::SetTalentRank(UHSTalentData* Talent, int32 NewRank)
{
	if (!Talent) return;

	NewRank = FMath::Clamp(NewRank, 0, Talent->MaxRank);
	TalentRanks.Add(Talent, NewRank);
	ApplyTalentEffect(Talent, NewRank);
}

void AHSPlayerState::ApplyTalentEffect(UHSTalentData* Talent, int32 Rank)
{
	if (!Talent) return;

	// Remove the previous rank's effect
	FActiveGameplayEffectHandle OldHandle;
	if (TalentEffectHandles.RemoveAndCopyValue(Talent, OldHandle))
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(OldHandle);
	}

	Rank = FMath::Clamp(Rank, 0, Talent->MaxRank);
	if (Rank == 0 || !Talent->Effect) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(Talent);

	// Level = rank; the effect's curve table turns it into the bonus
	const FGameplayEffectSpecHandle EffectSpecHandle =
		AbilitySystemComponent->MakeOutgoingSpec(Talent->Effect, Rank, EffectContext);

	if (EffectSpecHandle.IsValid())
	{
		TalentEffectHandles.Add(Talent, AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()));
	}
}