// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		
		void SetPlayerEnableState(bool SetPlayerEnabled);

};
