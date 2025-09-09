#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ScrapArchitectGameInstance.generated.h"

UCLASS()
class SCRAPARCHITECT_API UScrapArchitectGameInstance : public UGameInstance
{
    GENERATED_BODY()
public:
    virtual void Init() override;
    virtual void Shutdown() override;
};

