// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{

}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
	//current timer manager created for the world
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle, 
		this, 
		&APawnTurret::CheckFireCondition, 
		FireRate,
		true); //1st arg an FTimer, 2nd ref to the world, 3rd and 4th is what function to call at what rate, 5th wether timer should loop or nah 

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));	//get player pawn returns the player at specified index, index 0 means player 1, using cast to convert the pawn to APawnTank from APawn
}

void APawnTurret::HandleDestruction() 
{
	Super::HandleDestruction(); //calls the base handle destruction to play effects first, perform base class logic first and then return and perform the child class logic
	Destroy(); //default function defined in AActor
}

float APawnTurret::GetTurretHealth() const
{
	return (HealthComponent->GetHealth());
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerPawn || ReturnDistanceToPlayer() > FireRange) //player invalid or out of range
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation()); //when player in range turret starts rotating to look at player
}

void APawnTurret::CheckFireCondition() 
{
	if(!PlayerPawn || !(PlayerPawn->GetPlayerStatus()))
	{
		return; //if player isnt valid or health == 0 then return 
	} 

	if(ReturnDistanceToPlayer() <= FireRange)
	{
		//fire functionality will be declared in pawn base as both turret and tank are gonna be using it
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer() 
{
	
	if (!PlayerPawn)
	{
		return 0;
	}

	return(FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation()));

}
