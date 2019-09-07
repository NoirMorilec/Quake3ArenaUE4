// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

UCLASS()
class QUAKE3ARENA_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
		float Health;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* WeaponPivot;

	ADefaultCharacter* MyPawn;

	class UAudioComponent* FireAC;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundCue* LeftMouseSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundCue* RightMouseSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundCue* ShiftSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundCue* UltimateSound;

	void MoveForward(float value);
	void MoveRight(float value);
	class UAudioComponent* PlaySound(class USoundCue* Sound);

	virtual void LeftMousePressed();
	virtual void LeftMouseReleased();
	virtual void RightMousePressed();
	virtual void RightMouseReleased();
	virtual void ShiftPressed();
	virtual void ShiftReleased();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
