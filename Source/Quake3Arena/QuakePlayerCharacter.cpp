// Fill out your copyright notice in the Description page of Project Settings.


#include "QuakePlayerCharacter.h"

// Sets default values
AQuakePlayerCharacter::AQuakePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuakePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuakePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQuakePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

