// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn) {
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	FBox Bounds(Min, Max);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		UE_LOG(LogTemp, Warning, TEXT("Spawn Point: %s"), *SpawnPoint.ToCompactString());
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	CastSphere(GetActorLocation(), 300);
	CastSphere(GetActorLocation()+ FVector(0,0,1000) , 300);

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
	HitResult,
	Location,
	Location,
	FQuat::Identity,
	ECollisionChannel::ECC_Camera,
	FCollisionShape::MakeSphere(Radius)
	);

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, Radius, 16, ResultColor, true, 100);
	return HasHit;
}
