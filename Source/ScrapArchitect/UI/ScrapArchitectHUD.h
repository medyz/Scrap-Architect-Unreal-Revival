#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ScrapArchitectHUD.generated.h"

UCLASS()
class SCRAPARCHITECT_API AScrapArchitectHUD : public AHUD
{
    GENERATED_BODY()
public:
    virtual void DrawHUD() override;
};

