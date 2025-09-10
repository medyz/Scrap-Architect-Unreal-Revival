# API документация (черновик)

Эта страница будет содержать описания публичных C++ и Blueprint API модулей проекта.

## Модули
- ScrapArchitect (Runtime)

## Подсистемы (UGameInstanceSubsystem)
- BuildManager
- PhysicsManager
- MissionManager
- ProgressionManager
- SaveManager
- UIManager

## Базовые классы
- AScrapPart - базовый актор детали
- UBuildModeComponent - режим сборки
- UVehicleController - управление транспортом
- UToolComponent - базовый инструмент

## Пример использования (C++)
```cpp
#include "Building/BuildManager.h"

void SpawnExamplePart(UWorld* World, TSubclassOf<AScrapPart> PartClass, FVector Location)
{
    if (UGameInstance* GI = World->GetGameInstance())
    {
        if (UBuildManager* BM = GI->GetSubsystem<UBuildManager>())
        {
            BM->SpawnPart(PartClass, Location);
        }
    }
}
```

---

Статус: черновик. Будет уточняться по мере реализации модулей.