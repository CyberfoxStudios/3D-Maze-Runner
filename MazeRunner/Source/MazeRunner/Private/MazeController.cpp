// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeController.h"

AMazeController::AMazeController()
{
	// Set this player controller to tick every frame
	PrimaryActorTick.bCanEverTick = true;
    PerspectiveCamera = nullptr;
    OverheadCamera = nullptr;
}

void AMazeController::BeginPlay()
{
    Super::BeginPlay();

    //Sets the perspective camera to the default camera when the game starts
    PerspectiveCamera = GetActiveCamera();

    if (!PerspectiveCamera)
    {
        UE_LOG(LogTemp, Warning, TEXT("PerspectiveCamera not found!"));
    }

    //Set the overhead camera
    // Specify the name of the actor you want to get
    OverheadCamera = GetCameraByTag("overhead");
}

//on tick, listen for c key
void AMazeController::Tick(float DeltaTime)
{
    // Check if the "C" key was just pressed
    if (WasInputKeyJustPressed(EKeys::C))
    {
        UE_LOG(LogTemp, Display, TEXT("C press detected."));
        SwitchCameras();
    }
}

//on c key, 
// store current camera
// switch to alt camera
// set alt camera to old camera
void AMazeController::SwitchCameras()
{
    //Set the overhead camera
    // Specify the name of the actor you want to get
    OverheadCamera = GetCameraByTag("overhead");

    // Check if the current view target is the first camera, switch to the second camera, and vice versa
    if (GetActiveCamera() == PerspectiveCamera)
    {
        SetViewTargetWithBlend(OverheadCamera, 0.5f);
    }
    else
    {
        SetViewTargetWithBlend(PerspectiveCamera, 0.5f);
    }
}

AActor* AMazeController::GetActiveCamera()
{
    // Get a reference to the player controller
    APlayerController* PlayerController = this;

    if (PlayerController)
    {
        // Get the view target (which is usually the pawn or character)
        AActor* ViewTarget = PlayerController->GetViewTarget();

        if (ViewTarget)
        {
            // Get the camera actor from the view target
            return ViewTarget;
        }
        else
        {
            // Handle the case where the view target is not found
            UE_LOG(LogTemp, Warning, TEXT("View target not found."));
            return nullptr;
        }
    }
    else
    {
        // Handle the case where the player controller is not found
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not found."));
        return nullptr;
    }
}

AActor* AMazeController::GetCameraByTag(FString TagName)
{
    // Get all actors in the level
    TArray<AActor*> AllActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

    // Iterate through all actors to find the one with the specified name and tag
    for (AActor* OneActor : AllActors)
    {
        // Check if the actor has the correct name
        if (OneActor->ActorHasTag(FName(*TagName)))
        {
            return OneActor;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Camera with tag %s not found!"), *TagName);
    return nullptr;
}

