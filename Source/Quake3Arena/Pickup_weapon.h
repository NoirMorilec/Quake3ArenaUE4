// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupTemplate.h"
#include "Pickup_weapon.generated.h"

/**
 * 
 */
UCLASS()
class QUAKE3ARENA_API APickup_weapon : public APickupTemplate
{
	GENERATED_BODY()

	/** how much ammo does it give? */
	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	int32 AmmoClips;

	/** which weapon gets ammo?
	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	TSubclassOf<class AQuakeWeapon> WeaponType;
	*/

	/** give pickup */
	virtual void GivePickupTo(class AClientPlayer* Player) override;

	/** which weapon gets ammo? */
	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	TSubclassOf<class AWeaponBase> WeaponType;
};
