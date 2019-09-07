// Fill out your copyright notice in the Description page of Project Settings.


#include "Bastion.h"
#include "Gameframework/WorldSettings.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Gameframework/PlayerController.h"
#include "Sound/SoundCue.h"
#define print(str) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::FString(str));

ABastion::ABastion()
{
	State = WALK;

	IdleWeaponPivot = CreateDefaultSubobject<USceneComponent>(TEXT("IdleWeaponPivot"));
	IdleWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IdleWeapon"));
	IdleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("IdleCamera"));


	//GetCapsuleComponent()->SetupAttachment(Root);
	IdleCamera->SetupAttachment(GetCapsuleComponent());
	IdleWeaponPivot->SetupAttachment(IdleCamera);
	IdleWeapon->SetupAttachment(IdleWeaponPivot);

	IdleCamera->SetActive(false);
	Camera->SetActive(true);
	IdleWeapon->SetVisibility(false);
	Weapon->SetVisibility(true);

	SpeedRotation = 20.f;
	TimeToTransform = 1.5f;
}

void ABastion::LeftMousePressed()
{
	Super::LeftMousePressed();

	switch (State)
	{
	case WALK:
		break;
	case STAY:
		RotateWeapon();
		break;
	case ULTIMATE:
		break;
	default:
		break;
	}
}

void ABastion::LeftMouseReleased()
{
	Super::LeftMouseReleased();

	GetWorld()->GetTimerManager().ClearTimer(SpeedRotationTimer);
}

void ABastion::RightMousePressed()
{

}

void ABastion::RightMouseReleased()
{

}

void ABastion::ShiftPressed()
{
	switch (State)
	{
	case ABastion::WALK:
		State = STAY;
		ChangeTransform(false);
		PrevSound = LeftMouseSound;
		LeftMouseSound = LeftMouseSoundIdle;
		break;

	case ABastion::STAY:
		State = WALK;
		ChangeTransform(true);
		LeftMouseSound = PrevSound;
		break;

	case ABastion::ULTIMATE:
		break;

	default:
		break;
	}
}

void ABastion::ChangeTransform(bool bWalk)
{
	if (FireAC) FireAC->Stop();
	PlaySound(ShiftSound);
	DisableInput(Cast<APlayerController>(MyPawn->Controller));
	Camera->SetActive(bWalk);
	Weapon->SetVisibility(bWalk);
	IdleCamera->SetActive(!bWalk);
	IdleWeapon->SetVisibility(!bWalk);
	GetWorld()->GetTimerManager().SetTimer(TransformationTimer, this, &ABastion::EnableSystem, TimeToTransform, false);
}

void ABastion::EnableSystem()
{
	EnableInput(Cast<APlayerController>(MyPawn->Controller));
}

void ABastion::RotateWeapon()
{
	IdleWeaponPivot->AddLocalRotation(FRotator(0.f, 0.f, SpeedRotation));
	GetWorld()->GetTimerManager().SetTimer(SpeedRotationTimer, this, &ABastion::RotateWeapon, GetWorld()->GetDeltaSeconds() , false);
}

