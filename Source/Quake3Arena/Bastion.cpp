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
	IdleWeaponPivot = CreateDefaultSubobject<USceneComponent>(TEXT("IdleWeaponPivot"));
	IdleWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("IdleWeaponMesh"));
	IdleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("IdleCamera"));
	Rifle = CreateDefaultSubobject<ULinetraceType>(TEXT("Rifle"));
	MachineGun = CreateDefaultSubobject<ULinetraceType>(TEXT("MachineGun"));

	//GetCapsuleComponent()->SetupAttachment(Root);
	IdleCamera->SetupAttachment(GetCapsuleComponent());
	IdleWeaponPivot->SetupAttachment(IdleCamera);
	IdleWeaponMesh->SetupAttachment(IdleWeaponPivot);

	IdleCamera->SetActive(false);
	Camera->SetActive(true);
	IdleWeaponMesh->SetVisibility(false);
	WeaponMesh->SetVisibility(true);
	bIsWalking = true;

	/*if (WeaponSockets.Num() == 2)
	{
		Rifle->SetStartVector(GetMesh()->GetSocketLocation(WeaponSockets[0]));
		MachineGun->SetStartVector(GetMesh()->GetSocketLocation(WeaponSockets[1]));
	}*/
	

	SpeedRotation = 20.f;
	TimeToTransform = 1.5f;
}

void ABastion::LeftMousePressed()
{
	Super::LeftMousePressed();

	if (bIsWalking)
	{
		Rifle->SetMeshPtr(WeaponMesh);
		Rifle->StartShooting();
	}
	else
	{
		MachineGun->SetMeshPtr(IdleWeaponMesh);
		MachineGun->StartShooting();
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
	Swap(LeftMouseSound, LeftMouseSoundIdle);
	ChangeTransformTo(!bIsWalking);
}

void ABastion::ChangeTransformTo(bool bNewState)
{
	if (FireAC) FireAC->Stop();
	PlaySound(ShiftSound);
	DisableInput(Cast<APlayerController>(this->Controller));
	Camera->SetActive(bNewState);
	IdleCamera->SetActive(!bNewState);
	WeaponMesh->SetVisibility(bNewState);
	IdleWeaponMesh->SetVisibility(!bNewState);
	GetWorld()->GetTimerManager().SetTimer(TransformationTimer, this, &ABastion::EnableSystem, TimeToTransform, false);
	bIsWalking = bNewState;
}

void ABastion::EnableSystem()
{
	EnableInput(Cast<APlayerController>(this->Controller));
}

void ABastion::RotateWeapon()
{
	IdleWeaponPivot->AddLocalRotation(FRotator(0.f, 0.f, SpeedRotation));
	GetWorld()->GetTimerManager().SetTimer(SpeedRotationTimer, this, &ABastion::RotateWeapon, GetWorld()->GetDeltaSeconds() , false);
}

