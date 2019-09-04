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

protected: 
	void Attack() override;
	void StopAttack() override;
	void SecondaryAttack() override;
	void StopSecondaryAttack() override;
	void RotateWeapon();

	UPROPERTY(EditAnywhere)
		FRotator SpeedRotation;
};
