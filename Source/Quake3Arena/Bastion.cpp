// Fill out your copyright notice in the Description page of Project Settings.


#include "Bastion.h"


void ABastion::Attack()
{
	RotateWeapon();
}

void ABastion::StopAttack()
{
}

void ABastion::SecondaryAttack()
{
}

void ABastion::StopSecondaryAttack()
{
}

void ABastion::RotateWeapon()
{
	WeaponPivot->AddLocalRotation(SpeedRotation);
}
