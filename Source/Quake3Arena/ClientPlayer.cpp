// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AClientPlayer::AClientPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AClientPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClientPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AClientPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AClientPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AClientPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AClientPlayer::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AClientPlayer::OnStopJump);

}

void AClientPlayer::MoveForward(float Val)
{
	if (Controller && Val != 0.f)
	{
		FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, Val);
	}
}

void AClientPlayer::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		FVector Direction = GetActorRightVector();
		AddMovementInput(Direction, Val);
	}

}

void AClientPlayer::OnStartJump()
{
	bPressedJump = true;
}

void AClientPlayer::OnStopJump()
{
	bPressedJump = false;
	StopJumping();
}

