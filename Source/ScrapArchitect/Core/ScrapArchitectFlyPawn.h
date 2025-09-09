#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ScrapArchitectFlyPawn.generated.h"

UCLASS()
class SCRAPARCHITECT_API AScrapArchitectFlyPawn : public APawn
{
    GENERATED_BODY()

public:
    AScrapArchitectFlyPawn();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    virtual void Tick(float DeltaSeconds) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UFloatingPawnMovement* FloatingMovementComponent;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float BaseMoveSpeed;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float SprintMultiplier;

    bool bIsSprinting;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void MoveUp(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void SprintPressed();
    void SprintReleased();
    FVector GetForwardDirection() const;
    FVector GetRightDirection() const;
};

