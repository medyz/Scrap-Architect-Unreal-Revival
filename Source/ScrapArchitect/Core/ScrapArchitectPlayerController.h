#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScrapArchitectPlayerController.generated.h"

UCLASS()
class SCRAPARCHITECT_API AScrapArchitectPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    AScrapArchitectPlayerController();
protected:
    virtual void SetupInputComponent() override;
};

