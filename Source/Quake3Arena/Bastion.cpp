// Fill out your copyright notice in the Description page of Project Settings.


#include "Bastion.h"
#include "Gameframework/WorldSettings.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
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
}

void ABastion::LeftMousePressed()
{
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
		IdleCamera->SetActive(true);
		Camera->SetActive(false);
		IdleWeapon->SetVisibility(true);
		Weapon->SetVisibility(false);
		break;

	case ABastion::STAY:
		State = WALK;
		IdleCamera->SetActive(false);
		Camera->SetActive(true);
		IdleWeapon->SetVisibility(false);
		Weapon->SetVisibility(true);
		break;

	case ABastion::ULTIMATE:
		break;

	default:
		break;
	}
}

void ABastion::RotateWeapon()
{
	IdleWeaponPivot->AddLocalRotation(SpeedRotation);
	GetWorld()->GetTimerManager().SetTimer(SpeedRotationTimer, this, &ABastion::RotateWeapon, GetWorld()->GetDeltaSeconds() , false);
}
