// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Health = 0.0f;

	//Root = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("RootComp"));
	//RootComponent = Root;
	RootComponent = GetCapsuleComponent();

	WeaponPivot = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponPivot"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	//GetCapsuleComponent()->SetupAttachment(Root);
	Camera->SetupAttachment(GetCapsuleComponent());
	WeaponPivot->SetupAttachment(Camera);
	WeaponMesh->SetupAttachment(WeaponPivot);

	bCanMove = true;
	bMousePressed = false;
	FireAC = NULL;
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftMouse",EInputEvent::IE_Pressed, this, &ADefaultCharacter::LeftMousePressed);
	PlayerInputComponent->BindAction("RightMouse", EInputEvent::IE_Pressed, this, &ADefaultCharacter::RightMousePressed);
	PlayerInputComponent->BindAction("LeftMouse", EInputEvent::IE_Released, this, &ADefaultCharacter::LeftMouseReleased);
	PlayerInputComponent->BindAction("RightMouse", EInputEvent::IE_Released, this, &ADefaultCharacter::RightMouseReleased);
	PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Pressed, this, &ADefaultCharacter::ShiftPressed);
	PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Released, this, &ADefaultCharacter::ShiftReleased);
	PlayerInputComponent->BindAction("Space", EInputEvent::IE_Pressed, this, &ADefaultCharacter::SpacePressed);
	PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Released, this, &ADefaultCharacter::SpaceReleased);


	PlayerInputComponent->BindAxis("MoveForward", this, &ADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
}



void ADefaultCharacter::LeftMousePressed()
{
	bMousePressed = true;
	if (!FireAC)
	{
		FireAC = PlaySound(LeftMouseSound);
	}
}

void ADefaultCharacter::RightMousePressed()
{

}

void ADefaultCharacter::LeftMouseReleased()
{
	bMousePressed = false;
	if (FireAC)
	{
		FireAC->FadeOut(0.1f, 0.0f);
		FireAC = NULL;
	}
}

void ADefaultCharacter::RightMouseReleased()
{
}

void ADefaultCharacter::ShiftPressed()
{
}

void ADefaultCharacter::ShiftReleased()
{
}

void ADefaultCharacter::SpacePressed()
{
	if (bCanMove)
	{
		Jump();
	}
}

void ADefaultCharacter::SpaceReleased()
{
	ResetJumpState();
}

void ADefaultCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && bCanMove)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADefaultCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && bCanMove)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

UAudioComponent * ADefaultCharacter::PlaySound(USoundCue * Sound)
{
	return Sound && this? UGameplayStatics::SpawnSoundAttached(Sound, this->GetRootComponent()) : NULL;
}
