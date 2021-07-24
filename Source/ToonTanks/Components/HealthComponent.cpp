// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "ToonTanks/GameModes/GameModeBase_TT.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	GameModeRef = Cast<AGameModeBase_TT>(UGameplayStatics::GetGameMode(GetWorld()));
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage); //dynamic delegate
}

void UHealthComponent::TakeDamage(AActor* ActorDamaged, float Damage, const UDamageType* DamageType, AController* DamagedBy, AActor* DamagingActor) 
{
	if(Damage == 0 || Health <= 0)
	{
		return;
	}	

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth); // this fn clamps 1st value b/w 2nd and 3rd value

	UE_LOG(LogTemp, Warning, TEXT("Remaining health of %s is: %f"), *ActorDamaged->GetName(), Health);

	if(Health <= 0) //meaning actor died
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDied(ActorDamaged); 
			UE_LOG(LogTemp, Warning, TEXT("%s DIED!!"), *ActorDamaged->GetName());
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health Component no ref to Game Mode"));
		}
	}

}

float UHealthComponent::GetHealthPercent() const
{
	return Health/100;	
}

float UHealthComponent::GetHealth() const
{
	return Health;
}
