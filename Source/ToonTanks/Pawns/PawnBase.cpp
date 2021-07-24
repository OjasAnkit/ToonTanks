// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "Particles/ParticleSystem.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp; //The root component is essentially the actor, used for the actor's transform (location, rotation, and scale), thus we use a simple collision shape for root component
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent); //basically setting up attachmemt in a hierarchical manner

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(FVector TargetLocation) 
{    
	FVector TargetLocationCleaned = FVector(TargetLocation.X, TargetLocation.Y, TurretMesh->GetComponentLocation().Z); //making Z component same as the turret so it becomes 0 thus preventing rotation along pitch (up n down)
	FVector StartLocation = TurretMesh->GetComponentLocation(); //gets location of turret 

 	FRotator TurretRotation = FVector(TargetLocationCleaned - StartLocation).Rotation(); //vector from turret to the target
	// FRotator Testing = FVector(StartLocation).Rotation();
	// FRotator Smooth = FMath::RInterpTo(Testing, TurretRotation, GetWorld()->GetDeltaSeconds(), 20.f);
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire() 
{
	if (ProjectileClass) //checking for valid projectile class
	{
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation()); // getting world ref and spawning an actor of class type AProjectileBase
		TempProjectile->SetOwner(this);
	}
	
} 

void APawnBase::HandleDestruction() 
{	
	//ref to world, ref to particle to be played, Location i.e actors location, 4th arg is rotation offset dont need it here
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());//used to spawn the universal particle for deaths for both the tank and turret
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation()); //playing the death sound!
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}



