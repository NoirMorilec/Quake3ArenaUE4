// Fill out your copyright notice in the Description page of Project Settings.


#include "LinetraceType.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
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
		const int32 RandomSeed = FMath::Rand();
		FRandomStream WeaponRandomStream(RandomSeed);
		const float ConeHalfAngle = FMath::DegreesToRadians(LinetraceConfig.Spread);

		const FVector Start = WeaponMeshPtr ? 
			WeaponMeshPtr->GetSocketLocation(BaseConfig.WeaponSocket) :
			Owner->GetWeaponMesh()->GetSocketLocation(BaseConfig.WeaponSocket);
		const FVector AimDir = Owner->GetViewRotation().Vector();
		const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle);

		const FVector End = ((ShootDir * BaseConfig.BulletDistance) + Start);

		//DrawDebugCone(GetWorld(), Start, AimDir, BaseConfig.BulletDistance, ConeHalfAngle, ConeHalfAngle, 20, FColor::Red, false, 30.f);
		//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.f, 0, 1);

		FCollisionQueryParams CollisionParams;
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
		{
			if (OutHit.bBlockingHit)
			{
				if (GEngine)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				}
			}
		}

		SpawnTrailEffect(Start,End);
	}

	GetWorld()->GetTimerManager().SetTimer(FiringTimer, this, &ULinetraceType::StartShooting, BaseConfig.TimeBetweenShots, false);
}

void ULinetraceType::SpawnTrailEffect(const FVector & StartPoint, const FVector & EndPoint)
{
	if (TrailFX)
	{

		UParticleSystemComponent* TrailPSC = UGameplayStatics::SpawnEmitterAtLocation(this, TrailFX, StartPoint);
		if (TrailPSC)
		{
			TrailPSC->SetVectorParameter(TrailTargetParam, EndPoint);
		}
	}
}