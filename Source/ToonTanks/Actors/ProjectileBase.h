// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;
class USoundBase;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))	
	UProjectileMovementComponent* TheProjectileMovement; // controls the movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TheProjectileMesh; // visual representation of our projectile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" , meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleTrail; //trail which will be attached on the projectile
	UPROPERTY(EditDefaultsOnly, Category = "Damage") //only the subclass of UDamageType are the options by choosing EditDefaultsOnly
	TSubclassOf<UDamageType> DamageType; // the template class tells the editor's property windows to list only classes derived from UDamageType as choices for the property
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float ProjectileInitialSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement" , meta = (AllowPrivateAccess = "true"))
	float ProjectileMaxSpeed = 1200.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage" , meta = (AllowPrivateAccess = "true"))
	float Damage = 20.f;
	
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticle; 
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound; 

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UMatineeCameraShake> HitShake;

	UFUNCTION() //dynamic delegates are declared as UFUNCTIONS
	void OnHit(UPrimitiveComponent* MainComponent, AActor* ComponentHit, UPrimitiveComponent* ExactComponentHit, FVector ForceOfImpact, const FHitResult& Hit ); //main component is missile comp hit is the actor which is hit by missile, exact comp is the exact mesh that missile hit in case there are sub meshes

public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
