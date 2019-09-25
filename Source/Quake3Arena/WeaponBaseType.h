// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DefaultCharacter.h"
#include "WeaponBaseType.generated.h"

USTRUCT()
struct FWeaponConfigs
{
	GENERATED_BODY()
	
	/*Damage we could deal in one shot*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon settings")
		uint16 DmgPerShot;
	/*The capacity of weapon clip*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon settings")
		uint16 Ammo;
	/*How much damage will be removed by the distance*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon settings")
		uint16 DmgReductionByDistance;
	/*How many bullets will be used to fire before a pause (for ex. baptiste from overwatch with 3 bullets)*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon settings")
		uint16 BurstAmmoExpense;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon settings")
		float BulletDistance;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon settings")
		float TimeBetweenShots;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon settings")
		FName WeaponSocket;

	FWeaponConfigs()
	{

	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUAKE3ARENA_API UWeaponBaseType : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Configs")
	FWeaponConfigs BaseConfig;

public:
	// Sets default values for this component's properties
	UWeaponBaseType();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void StartShooting();
	virtual void StopShooting();

	UPROPERTY()
	class USkeletalMeshComponent* WeaponMeshPtr;
	FTimerHandle FiringTimer;
};
