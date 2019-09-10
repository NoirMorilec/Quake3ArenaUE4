// Fill out your copyright notice in the Description page of Project Settings.


#include "LinetraceType.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#define print(str) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::FString(str));

ULinetraceType::ULinetraceType()
{
	Owner = Cast<ADefaultCharacter>(GetOwner());
}

void ULinetraceType::StartShooting()
{
	if (Owner)
	{
		FHitResult OutHit;
		FVector Start = WeaponMeshPtr ? 
			WeaponMeshPtr->GetSocketLocation(WeaponSocket) : 
			Owner->GetWeaponMesh()->GetSocketLocation(WeaponSocket);
		FRotator ForwardView = Owner->GetViewRotation();
		FVector End = ((ForwardView.Vector() * BulletDistance) + Start);
		FCollisionQueryParams CollisionParams;
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
		{
			if (OutHit.bBlockingHit)
			{
				if (GEngine) {

					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

				}
			}
		}
	}
}
