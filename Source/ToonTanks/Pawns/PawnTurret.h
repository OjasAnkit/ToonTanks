// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class UHealthComponent;
class APawnTank; //declaring so that we can store and reference the player pawn
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

	private:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float FireRate = 2.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float FireRange = 100.0f;
		
		FTimerHandle FireRateTimerHandle;
		APawnTank* PlayerPawn;

		void CheckFireCondition();// checks if player tank is in firing radius
		float ReturnDistanceToPlayer();

	public:
	
		APawnTurret();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		virtual void HandleDestruction() override; 

		float GetTurretHealth() const;

	protected:

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;		

};
