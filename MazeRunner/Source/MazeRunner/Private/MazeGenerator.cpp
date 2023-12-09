// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"

// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mazeGenerated = false;

	// Create the components, set in editor
	generator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratorRootComponent"));
	RootComponent = generator;
	mazeMaterial = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MazeMaterialComponent"));
}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("MazeGenerator Script Active!"));
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeGenerator::NotifyHit(
	UPrimitiveComponent* MyComp,
	AActor* Other,
	UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	//Generate Maze
	if (!mazeGenerated)
	{
		int nodesGenerated = 0;
		while (nodesGenerated < mazeSize * mazeSize)
		{

			//calculate location
			// Get the bounding box of the StaticMeshComponent
			FBox Bounds = mazeMaterial->Bounds.GetBox();

			// Calculate the size
			FVector MeshSize = Bounds.GetSize();

			// Access the individual dimensions (X, Y, Z)
			float SizeX = MeshSize.X;
			float SizeY = MeshSize.Y;

			int locationY = nodesGenerated / mazeSize * MeshSize.Y; // + OFFSET (CENTER?)
			int locationX = nodesGenerated % mazeSize * MeshSize.X; // + OFFSET (CENTER?)
			
			//spawn the node
			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this; // Set the owner of the spawned actor if needed

				// Specify the location and rotation where you want to spawn the Blueprint
				FVector spawnerLocation = GetActorLocation();
				FVector SpawnLocation = spawnerLocation + FVector(locationX, locationY, 0.0f);
				FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

				// Spawn the Blueprint class
				World->SpawnActor<AActor>(mazeChunk, SpawnLocation, SpawnRotation, SpawnParams);
			}

			nodesGenerated++;
		}
		mazeGenerated = true;
	}
}

