#include "Core/ScrapArchitectGameModeBase.h"
#include "Core/ScrapArchitectFlyPawn.h"
#include "UI/ScrapArchitectHUD.h"

AScrapArchitectGameModeBase::AScrapArchitectGameModeBase()
{
    DefaultPawnClass = AScrapArchitectFlyPawn::StaticClass();
    HUDClass = AScrapArchitectHUD::StaticClass();
}

