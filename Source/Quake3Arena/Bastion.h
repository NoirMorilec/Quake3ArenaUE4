// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageClass.h"
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

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* IdleWeapon;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* IdleWeaponPivot;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundCue* LeftMouseSoundIdle;
	class USoundCue* PrevSound;

	enum BastionState
	{
		WALK,
		STAY,
		ULTIMATE
	};
	BastionState State;

	void LeftMousePressed() override;
	void LeftMouseReleased() override;
	void RightMousePressed() override;
	void RightMouseReleased() override;
	void ShiftPressed() override;
	void ChangeTransform(bool bWalk);

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
