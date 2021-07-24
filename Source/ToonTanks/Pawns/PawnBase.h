// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase; //so pawn base knows what to spawn when fire() is called
class UParticleSystem;
class UHealthComponent;
class USoundBase;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

	private:
		//COMPONENTS
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))	
		UCapsuleComponent* CapsuleComp;	//generally used to demonstrate the collision and setting up the hitbox
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh; //creating for using the base of tank
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh; //creating for using the turret of the tank
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true")) //meta specifier req cuz it is a private member
		USceneComponent* ProjectileSpawnPoint; //used to place where the projectile will spawn out the turret
		
		// VARIABLES
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass; //only make subclasses of baseclass as projectiles to spawn if we had multiple types of projectiles option
		UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle; //
		UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DeathSound;
		UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<UMatineeCameraShake> DeathShake;

	public:
		// Sets default values for this pawn's properties
		APawnBase();

		virtual void HandleDestruction(); //control how pawn reacts when destroyed, this fn is virtual as itll be overridden by the child classes as the tank and turret are gonna handle destruction in diff ways!

	protected:

		void RotateTurret(FVector TargetLocation); //basically where the turret needs to look
		void Fire(); //create projectile using projectile class and launch where turret is facing
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;
};