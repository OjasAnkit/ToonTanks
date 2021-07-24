// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/GameModes/GameModeBase_TT.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/PlayerControllers/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AGameModeBase_TT::BeginPlay() 
{
    Super::BeginPlay();

    HandleGameStart();
}

void AGameModeBase_TT::ActorDied(AActor* DeadActor) 
{
    if(DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();    //calling the APawnTank's destruction function to handle the player dying
        HandleGameOver(false); //passing false to indicate a GAME OVER SCENARIO
        
        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnableState(false);
        }
    }
    
    else if(APawnTurret* Turret = Cast<APawnTurret>(DeadActor))
    {
        Turret->HandleDestruction(); //calling the APawnTurret's destruction function to handle the turret dying
        --NumberOfTargets; //updating targets, since calling GetAllActorsOfClass is a slow function thus we are not calling it every tick to check the number of turrets!

        if(NumberOfTargets == 0)
        {
            HandleGameOver(true); // GAME WIN CONDITION
        }
    }

}

void AGameModeBase_TT::HandleGameStart() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(this, APawnTurret::StaticClass(), TurretActors);
    NumberOfTargets = TurretActors.Num();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    GameStart();
    if(PlayerControllerRef) //having this after GameStart means we will not be able to move during the round countdown!!
    { 
        PlayerControllerRef->SetPlayerEnableState(false);

        FTimerHandle PlayerEnableHandle; //TO ADD COUNTDOWN DELAY AND DISABLE TANK MOVEMENT DURING IT
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, 
            &AMainPlayerController::SetPlayerEnableState, true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);

    }
}   

void AGameModeBase_TT::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);
}

