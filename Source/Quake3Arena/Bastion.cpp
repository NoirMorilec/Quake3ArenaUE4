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
#include "GameFramework/CharacterMovementComponent.h"
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

	/*if (WeaponSockets.Num() == 2)
	{
		Rifle->SetStartVector(GetMesh()->GetSocketLocation(WeaponSockets[0]));
		MachineGun->SetStartVector(GetMesh()->GetSocketLocation(WeaponSockets[1]));
	}*/
	
	TimeToTransform = 1.5f;
}

void ABastion::LeftMousePressed()
{
	Super::LeftMousePressed();

	if (bCanMove)
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

	GetWorld()->GetTimerManager().ClearTimer(Rifle->FiringTimer);
	GetWorld()->GetTimerManager().ClearTimer(MachineGun->FiringTimer);
}

void ABastion::RightMousePressed()
{
	print("yes")
}

void ABastion::RightMouseReleased()
{

}

void ABastion::ShiftPressed()
{
	Swap(LeftMouseSound, LeftMouseSoundIdle);
	ChangeTransformTo(!bCanMove);
}

void ABastion::ChangeTransformTo(bool bNewState)
{
	if (FireAC) FireAC->Stop();
	PlaySound(ShiftSound);
	LeftMouseReleased();
	DisableInput(Cast<APlayerController>(this->Controller));
	Camera->SetActive(bNewState);
	IdleCamera->SetActive(!bNewState);
	WeaponMesh->SetVisibility(bNewState);
	IdleWeaponMesh->SetVisibility(!bNewState);
	GetWorld()->GetTimerManager().SetTimer(TransformationTimer, this, &ABastion::EnableSystem, TimeToTransform, false);
	bCanMove = bNewState;
}

void ABastion::EnableSystem()
{
	EnableInput(Cast<APlayerController>(this->Controller));
}
