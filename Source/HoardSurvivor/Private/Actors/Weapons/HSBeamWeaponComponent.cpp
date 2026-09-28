#include "Actors/Weapons/HSBeamWeaponComponent.h"
#include "Core/HSCollisionChannels.h"

void UHSBeamWeaponComponent::Fire(const FVector StartLocation, const FVector Direction, const float Range,
                                  const float DamageAmount)
{
	FCollisionQueryParams CollisionParams;
	FVector EndLocation = StartLocation + (Direction * Range);
	CollisionParams.AddIgnoredActor(GetOwner());
	//DrawDebugLine will be removed. and replaced with actual beam that starts from gun and ends at point(probably a linetracesinglebychannel)
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, -1);
	//-
	TArray<FHitResult> HitResults;
	GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, EndLocation, ECC_Weapon, CollisionParams);
	for (const FHitResult& Hit : HitResults)
	{
		ApplyDamage(DamageAmount, Hit);
	}
}


