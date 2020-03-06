// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QuakePlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class QUAKE3ARENA_API AQuakePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuakePlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* FirstPersonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);

protected:	

};
