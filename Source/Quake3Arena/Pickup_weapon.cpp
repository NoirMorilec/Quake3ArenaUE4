// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_weapon.h"
#include "ClientPlayer.h"
#include "WeaponBase.h"

void APickup_weapon::GivePickupTo(AClientPlayer * Player)
{
	AWeaponBase* Weapon = (Player ? Player->FindWeapon(WeaponType) : NULL);
	if (Weapon)
	{

	}
	else
	{

	}
}
