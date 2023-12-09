#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "MazeController.generated.h"

UCLASS()
class MAZERUNNER_API AMazeController : public APlayerController
{
	GENERATED_BODY()

public:
    // Reference to Camera Actors (set in the editor or dynamically in code)
    UPROPERTY(VisibleAnywhere, Category = "Camera")
    AActor* PerspectiveCamera;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    AActor* OverheadCamera;

    AMazeController();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Function to switch cameras
    void SwitchCameras();
    AActor* GetActiveCamera();
};
