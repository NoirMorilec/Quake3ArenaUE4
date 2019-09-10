// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBaseType.h"
#include "DrawDebugHelpers.h"
#include "LinetraceType.generated.h"


UCLASS()
class QUAKE3ARENA_API ULinetraceType : public UWeaponBaseType
{
	GENERATED_BODY()

public:
	ULinetraceType();
	
	ADefaultCharacter* Owner;

	FORCEINLINE void SetMeshPtr(USkeletalMeshComponent* MeshPtr) { WeaponMeshPtr = MeshPtr; }
	void StartShooting() override;
};
