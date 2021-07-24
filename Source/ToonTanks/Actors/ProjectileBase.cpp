// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h" 
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //false since we arent using the Tick function
	
	TheProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	TheProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit); //(FUNCTION DELEGATE)On component hit is called when a component hits (or is hit by) something solid, Add dynamic will call on hit function whenever the On compon hit is triggered!!
	RootComponent = TheProjectileMesh;
	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);
	TheProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	TheProjectileMovement->InitialSpeed = ProjectileInitialSpeed;
	TheProjectileMovement->MaxSpeed = ProjectileMaxSpeed; // projectile will gain speed over time
	InitialLifeSpan = 3.0f; //After 3 seconds the projectiles will call the Destroy() function and remove themselves

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(this ,LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* MainComponent, AActor* ComponentHit, UPrimitiveComponent* ExactComponentHit, FVector ForceOfImpact, const FHitResult& Hit) 
{
	AActor* MyOwner = GetOwner();
	if(!MyOwner)
	{
		return;
	}
	//checking if we have hit a valid actor that isn't the my owner(so projectile doesn't destroy the pain spawning it) or isn't in the same class
	if(ComponentHit && ComponentHit!= this && ComponentHit!=MyOwner)
	{
		UGameplayStatics::ApplyDamage(
										ComponentHit, //actor damaged
										Damage, //base damage			
										MyOwner->GetInstigatorController(), // controller responsible for causing damage i.e the player
										this, //the actor causing damage i.e grenade missile
										DamageType //damage type
		);

		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle,  GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this , HitSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
		Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("Hit Detected"));


}
