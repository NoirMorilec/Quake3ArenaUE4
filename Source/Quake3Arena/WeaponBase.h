// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/** inifite ammo for reloads */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	bool bInfiniteAmmo;

	/** infinite ammo in clip, no reload required */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		bool bInfiniteClip;

	/** max ammo */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int32 CurrentAmmo;

	/** clip size */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int32 AmmoPerClip;

	/** initial clips */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int32 InitialClips;

	/** time between two consecutive shots */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float TimeBetweenShots;

	/** failsafe reload duration if weapon doesn't have any animation for it */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float NoAnimReloadDuration;

	/** defaults */
	FWeaponData()
	{
		bInfiniteAmmo = false;
		bInfiniteClip = false;
		CurrentAmmo = 100;
		AmmoPerClip = 20;
		InitialClips = 4;
		TimeBetweenShots = 0.2f;
		NoAnimReloadDuration = 1.0f;
	}
};

UCLASS()
class QUAKE3ARENA_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** weapon data */
	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponData WeaponConfig;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GiveAmmo(int32 amount);
};
