// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_TT.generated.h"

class APawnTurret;
class APawnTank;
class AMainPlayerController;

UCLASS()
class TOONTANKS_API AGameModeBase_TT : public AGameModeBase
{
	GENERATED_BODY()

	private:
	
	APawnTank* PlayerTank;
	int32 NumberOfTargets = 0;
	AMainPlayerController* PlayerControllerRef;	
	void HandleGameStart();
	//these will contain the code and will be calling the blueprint GameStart and GameOver		
	void HandleGameOver(bool Playerwon);
	

	public:

	void ActorDied(AActor* DeadActor); //functions pawn will call, game mode will decide what to do depending on wether the turret or tank called it

	protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent) // responsible for setting timers, creating widgets 
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

};