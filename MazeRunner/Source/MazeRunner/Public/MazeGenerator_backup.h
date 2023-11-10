// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

UCLASS()
class MAZERUNNER_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:
	//generator is the root component used to spawn the maze (i.e. a button)
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* generator;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mazeMaterial;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> mazeChunk;
	bool mazeGenerated;
	const int mazeSize = 10; //Configurable size prop, e.g. 10x10
	// Sets default values for this actor's properties
	AMazeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	virtual void NotifyHit(
		UPrimitiveComponent* MyComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;

};
