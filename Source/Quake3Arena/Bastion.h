// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageClass.h"
#include "LinetraceType.h"
#include "Bastion.generated.h"

UCLASS()
class QUAKE3ARENA_API ABastion : public ADamageClass
{
	GENERATED_BODY()
public:
	ABastion();
	
protected: 

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* IdleCamera;
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* IdleWeaponMesh;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* IdleWeaponPivot;

	UPROPERTY(VisibleDefaultsOnly)
		ULinetraceType* Rifle;
	UPROPERTY(VisibleDefaultsOnly)
		ULinetraceType* MachineGun;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundCue* LeftMouseSoundIdle;

	bool bIsWalking;
	

	void LeftMousePressed() override;
	void LeftMouseReleased() override;
	void RightMousePressed() override;
	void RightMouseReleased() override;
	void ShiftPressed() override;
	void ChangeTransformTo(bool bNewState);

	UFUNCTION()
	void RotateWeapon();
	UFUNCTION()
	void EnableSystem(); //After transform we should enable sounds and input

	UPROPERTY(EditAnywhere, Category = "Features")
	float SpeedRotation;
	UPROPERTY(EditDefaultsOnly, Category = "Features")
	float TimeToTransform;

	FTimerHandle SpeedRotationTimer;
	FTimerHandle TransformationTimer;
};
