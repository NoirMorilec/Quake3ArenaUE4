// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupTemplate.generated.h"

UCLASS()
class QUAKE3ARENA_API APickupTemplate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupTemplate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* SphereCollision;
	UPROPERTY(VisibleAnywhere)
		class URotatingMovementComponent* RotationMovement;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	virtual void GivePickupTo(class AClientPlayer* Player);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
};
