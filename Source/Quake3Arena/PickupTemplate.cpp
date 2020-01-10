// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupTemplate.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "ClientPlayer.h"
#define print(str) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::FString(str));

// Sets default values
APickupTemplate::APickupTemplate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RotationMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationMovement"));

	RootComponent = Root;
	SphereCollision->SetupAttachment(RootComponent);
	StaticMesh->SetupAttachment(SphereCollision);
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupTemplate::BeginOverlap);
}


// Called when the game starts or when spawned
void APickupTemplate::BeginPlay()
{
	Super::BeginPlay();
	
}

/*void APickupTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
// Called every frame


void APickupTemplate::GivePickupTo(AClientPlayer * Player)
{
	//Overrided by inheritors
}

void APickupTemplate::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != this && OtherActor)
	{
		AClientPlayer* Player = Cast<AClientPlayer>(OtherActor);
		GivePickupTo(Player);
		Destroy();
	}
}

