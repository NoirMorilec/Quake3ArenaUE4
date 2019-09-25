// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBaseType.h"
#include "DrawDebugHelpers.h"
#include "LinetraceType.generated.h"

USTRUCT()
struct FLinetraceConfigs
{
	GENERATED_BODY()
	/*The spread of any weapon*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon settings")
		float Spread;

	FLinetraceConfigs()
	{
		Spread = 0;
	}
};

UCLASS()
class QUAKE3ARENA_API ULinetraceType : public UWeaponBaseType
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Configs")
	FLinetraceConfigs LinetraceConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* TrailFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FName TrailTargetParam;

	void SpawnTrailEffect(const FVector& StartPoint, const FVector& EndPoint);

public:
	ULinetraceType();
	
	ADefaultCharacter* Owner;

	FORCEINLINE void SetMeshPtr(USkeletalMeshComponent* MeshPtr) { WeaponMeshPtr = MeshPtr; }
	void StartShooting() override;

};
