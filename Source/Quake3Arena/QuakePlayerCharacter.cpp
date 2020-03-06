// Fill out your copyright notice in the Description page of Project Settings.


#include "QuakePlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AQuakePlayerCharacter::AQuakePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCameraComponent"));
	
	CameraComponent->SetupAttachment(RootComponent);
	FirstPersonMesh->SetupAttachment(CameraComponent);
}

// Called when the game starts or when spawned
void AQuakePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuakePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQuakePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &AQuakePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AQuakePlayerCharacter::MoveRight);
}

void AQuakePlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AQuakePlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}