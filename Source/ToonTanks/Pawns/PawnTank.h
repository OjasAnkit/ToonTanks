// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "ToonTanks/PlayerControllers/MainPlayerController.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	
	private:

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm; //sets up the springarm which is a player specific thing, this basically creates child class
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera; //camera is setup on the springarm, again a playere speciifc thing, creates child class

		FVector MoveDirection;	//to set direction in which tanks has to be moved 
		FQuat RotationDirection;	//to set the rotation of the turret of the tank											 																																																		

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 20.f; 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float TurnSpeed = 10.f;
		
		APlayerController* PlayerControllerRef;

		void CalculateMoveInput(float Value); //bound to input functions gets the values of whatever Movement input has been given
		void CalculateRotateInput(float Value); //bound to input functions gets the values of whatever Rotation input has been given

		void Move(); //called when movement has been calculated and the tanks needs to start moving
		void Rotate(); //called when rotation has been calculated and turret needs to rotate

		bool bIsPlayerAlive = true;

	public:																														

		APawnTank();
		
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		virtual void HandleDestruction() override;

		bool GetPlayerStatus();

		UFUNCTION(BlueprintPure)
		float GetTankHealthPercent() const;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;		
		
};																	

