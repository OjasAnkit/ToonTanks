// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/PlayerControllers/MainPlayerController.h"


void AMainPlayerController::SetPlayerEnableState(bool SetPlayerEnabled) 
{
    if(SetPlayerEnabled == true)
    {
        GetPawn()->EnableInput(this); //passing the player controller i.e this as an argument
    }

    else
    {
        GetPawn()->DisableInput(this); 
    }

    bShowMouseCursor = SetPlayerEnabled;
}
