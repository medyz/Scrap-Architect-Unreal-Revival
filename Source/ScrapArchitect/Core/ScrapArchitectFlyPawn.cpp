#include "Core/ScrapArchitectFlyPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AScrapArchitectFlyPawn::AScrapArchitectFlyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->TargetArmLength = 0.0f;
    SpringArmComponent->bUsePawnControlRotation = true;
    RootComponent = SpringArmComponent;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->bUsePawnControlRotation = false;

    FloatingMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
    FloatingMovementComponent->MaxSpeed = 1200.0f;

    BaseMoveSpeed = 1200.0f;
    SprintMultiplier = 2.0f;
    bIsSprinting = false;
}

void AScrapArchitectFlyPawn::BeginPlay()
{
    Super::BeginPlay();
}

void AScrapArchitectFlyPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AScrapArchitectFlyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AScrapArchitectFlyPawn::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AScrapArchitectFlyPawn::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &AScrapArchitectFlyPawn::MoveUp);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AScrapArchitectFlyPawn::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AScrapArchitectFlyPawn::LookUp);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AScrapArchitectFlyPawn::SprintPressed);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AScrapArchitectFlyPawn::SprintReleased);
}

void AScrapArchitectFlyPawn::MoveForward(float Value)
{
    if (Value == 0.0f) return;
    const FVector Direction = GetForwardDirection();
    const float Speed = BaseMoveSpeed * (bIsSprinting ? SprintMultiplier : 1.0f);
    AddMovementInput(Direction, Value * Speed);
}

void AScrapArchitectFlyPawn::MoveRight(float Value)
{
    if (Value == 0.0f) return;
    const FVector Direction = GetRightDirection();
    const float Speed = BaseMoveSpeed * (bIsSprinting ? SprintMultiplier : 1.0f);
    AddMovementInput(Direction, Value * Speed);
}

void AScrapArchitectFlyPawn::MoveUp(float Value)
{
    if (Value == 0.0f) return;
    const float Speed = BaseMoveSpeed * (bIsSprinting ? SprintMultiplier : 1.0f);
    AddMovementInput(FVector::UpVector, Value * Speed);
}

void AScrapArchitectFlyPawn::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AScrapArchitectFlyPawn::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void AScrapArchitectFlyPawn::SprintPressed()
{
    bIsSprinting = true;
}

void AScrapArchitectFlyPawn::SprintReleased()
{
    bIsSprinting = false;
}

FVector AScrapArchitectFlyPawn::GetForwardDirection() const
{
    const FRotator ControlRot = Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator;
    return FRotationMatrix(ControlRot).GetUnitAxis(EAxis::X);
}

FVector AScrapArchitectFlyPawn::GetRightDirection() const
{
    const FRotator ControlRot = Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator;
    return FRotationMatrix(ControlRot).GetUnitAxis(EAxis::Y);
}

