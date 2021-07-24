// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AGameModeBase_TT;
class APawnTurret;
class APawnTank;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DefaultHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Health = 0.f;

	AGameModeBase_TT* GameModeRef;
	

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	float GetHealthPercent() const;
	float GetHealth() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()																					// damaged by - projectile         damaging actor - tank or turret				
	void TakeDamage(AActor* ActorDamaged, float Damage, const UDamageType* DamageType, AController* DamagedBy, AActor* DamagingActor);
};