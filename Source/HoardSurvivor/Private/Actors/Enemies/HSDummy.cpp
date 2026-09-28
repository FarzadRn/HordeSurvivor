#include "Actors/Enemies/HSDummy.h"

AHSDummy::AHSDummy()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AHSDummy::TakeDamage_Implementation(const float DamageAmount)
{
	Health -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Yellow, FString::Printf(TEXT("Health: %f"), Health));
}


