// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"

APawnTank::APawnTank()
{
	SpringArm = 
	CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm")); //Create a component or subobject, allows creating a child class and returning the parent class.
	SpringArm->SetupAttachment(RootComponent); //Initializes desired Attach Parent and SocketName to be attached to when the component is registered.
	Camera = 
	CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); //same as above
 	Camera->SetupAttachment(SpringArm);	//same as above
}	

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerControllerRef = Cast<APlayerController>(GetController()); //using to get a reference to the player controller pawn and basically controls the player pawn
}

void APawnTank::HandleDestruction() 
{
	Super::HandleDestruction();
	//make a function to hide the player
	bIsPlayerAlive = false;
	SetActorHiddenInGame(true); //makes actor invisible on using but doesn't destroy it since destroying it will get rid of the camera component!
	SetActorTickEnabled(false); //stops the tick from updating every frame for the actor also stops movement after death
}

bool APawnTank::GetPlayerStatus() 
{
	return bIsPlayerAlive; //making a function to get players health status bcz the variable is pvt to prevent accidentally changing its value
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate(); //rotate called before move so the direction actor moves is know before actor starts moving
	Move();
	
	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult); //using to find out where the turret needs to be facing, 2nd arg is false cuz we dont want complex tracing
		
		FVector HitLocation = TraceHitResult.ImpactPoint; //returns the end location where trace has hit
		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput); // we are binding axis as opposed to binding action because movement is under axis mapping in the project settings 
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);//1st arg = name of mapping, 2nd ref to the world, 3rd what function to call when event takes place
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value) 
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0); //multiplying by delta time to make movement speed framerate independent	
}

void APawnTank::CalculateRotateInput(float Value) 
{
	float RotateAmount = Value * TurnSpeed * GetWorld()->DeltaTimeSeconds; //value getting from playerinputcomponent
	FRotator Rotation = FRotator(0, RotateAmount, 0); //only going to rotate the yaw
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move() 
{
	AddActorLocalOffset(MoveDirection, true); //bsweep true means sweep checking enabled, if disabled player can phase through walls n stuff lol
}

void APawnTank::Rotate() 
{
	AddActorLocalRotation(RotationDirection, true);	
}

float APawnTank::GetTankHealthPercent() const
{
	// UE_LOG(LogTemp, Warning, TEXT("Health %f"), HealthComponent->GetHealthPercent());
    return (HealthComponent->GetHealthPercent());
}
