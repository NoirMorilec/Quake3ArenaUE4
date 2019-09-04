// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = 0.0f;

	//Root = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("RootComp"));
	//RootComponent = Root;
	RootComponent = GetCapsuleComponent();

	WeaponPivot = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponPivot"));
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	//GetCapsuleComponent()->SetupAttachment(Root);
	GetMesh()->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(GetCapsuleComponent());
	WeaponPivot->SetupAttachment(Camera);
	Weapon->SetupAttachment(WeaponPivot);

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
	PlayerInputComponent->BindAction("LeftMouse", EInputEvent::IE_Released, this, &ADefaultCharacter::LeftMousePressed);
	PlayerInputComponent->BindAction("RightMouse", EInputEvent::IE_Released, this, &ADefaultCharacter::RightMousePressed);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);

}

void ADefaultCharacter::Attack()
{
}

void ADefaultCharacter::StopAttack()
{
}

void ADefaultCharacter::SecondaryAttack()
{
}

void ADefaultCharacter::StopSecondaryAttack()
{
}

void ADefaultCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADefaultCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ADefaultCharacter::LeftMousePressed()
{
	Attack();
}

void ADefaultCharacter::RightMousePressed()
{
	SecondaryAttack();
}

void ADefaultCharacter::LeftMouseReleased()
{
	StopAttack();
}

void ADefaultCharacter::RightMouseReleased()
{
	StopSecondaryAttack();
}
