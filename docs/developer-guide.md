# Руководство разработчика: Scrap Architect: Unreal Revival

## 🚀 Начало работы

### Требования к окружению

#### Обязательные инструменты
- **Unreal Engine 5.3+** - основной движок
- **Visual Studio 2022** - для C++ разработки
- **Git** - система контроля версий
- **Windows 10/11** - операционная система

#### Рекомендуемые инструменты
- **Blender** - для создания 3D моделей
- **GIMP/Photoshop** - для работы с текстурами
- **Audacity** - для обработки звуков
- **GitHub Desktop** - удобный Git клиент

### Установка и настройка

#### 1. Клонирование репозитория
```bash
git clone https://github.com/medyz/scrap-architect-unreal.git
cd scrap-architect-unreal
```

#### 2. Настройка Unreal Engine
1. Откройте Unreal Engine Launcher
2. Установите Unreal Engine 5.3 или новее
3. Откройте проект через "Open Project"
4. Выберите файл `ScrapArchitect.uproject`

#### 3. Первая сборка
1. При первом открытии UE5 предложит пересобрать проект
2. Нажмите "Yes" для компиляции C++ кода
3. Дождитесь завершения компиляции

#### 4. Настройка Visual Studio
1. В UE5: Edit → Project Settings → Platforms → Windows
2. Убедитесь, что Visual Studio 2022 выбран как IDE
3. Нажмите "Generate Visual Studio project files"

## 📁 Структура проекта

### Content (Контент)
```
Content/
├── Blueprints/              # Blueprint классы
│   ├── Characters/          # Персонажи
│   ├── GameModes/           # Игровые режимы
│   ├── HUD/                 # Интерфейс
│   ├── Pawns/               # Управляемые объекты
│   └── Widgets/             # UI виджеты
├── Materials/               # Материалы
│   ├── M_Base/              # Базовые материалы
│   ├── M_Parts/             # Материалы деталей
│   └── M_UI/                # UI материалы
├── Meshes/                  # 3D модели
│   ├── Parts/               # Детали
│   ├── Environment/         # Окружение
│   └── Props/               # Объекты
├── Textures/                # Текстуры
│   ├── Parts/               # Текстуры деталей
│   ├── UI/                  # UI текстуры
│   └── Environment/         # Текстуры окружения
├── Sounds/                  # Звуки
│   ├── SFX/                 # Эффекты
│   ├── Music/               # Музыка
│   └── UI/                  # UI звуки
├── UI/                      # Пользовательский интерфейс
│   ├── HUD/                 # Игровой интерфейс
│   ├── Menus/               # Меню
│   └── Widgets/             # Виджеты
└── Levels/                  # Уровни
    ├── MainMenu/            # Главное меню
    ├── WorldMap/            # Карта мира
    ├── TestLevels/          # Тестовые уровни
    └── Missions/            # Миссии
```

### Source (Исходный код)
```
Source/ScrapArchitect/
├── Core/                    # Основные системы
│   ├── ScrapArchitectGameMode.h/.cpp
│   ├── ScrapArchitectGameInstance.h/.cpp
│   └── ScrapArchitectPlayerController.h/.cpp
├── Building/                # Система сборки
│   ├── BuildModeComponent.h/.cpp
│   ├── BuildManager.h/.cpp
│   └── ScrapPart.h/.cpp
├── Physics/                 # Физические системы
│   ├── PhysicsManager.h/.cpp
│   └── ConstraintTypes.h
├── Vehicles/                # Система транспорта
│   ├── VehicleController.h/.cpp
│   └── ToolComponent.h/.cpp
├── Gameplay/                # Игровые механики
│   ├── MissionManager.h/.cpp
│   ├── ProgressionManager.h/.cpp
│   └── SaveManager.h/.cpp
├── UI/                      # Пользовательский интерфейс
│   ├── UIManager.h/.cpp
│   └── HUDWidget.h/.cpp
└── Utils/                   # Утилиты
    ├── MathUtils.h
    └── DebugUtils.h
```

## 🔧 Разработка

### Создание новой детали

#### 1. Создание C++ класса
```cpp
// Header: Source/ScrapArchitect/Building/MyCustomPart.h
#pragma once

#include "CoreMinimal.h"
#include "Building/ScrapPart.h"
#include "MyCustomPart.generated.h"

UCLASS()
class SCRAPARCHITECT_API AMyCustomPart : public AScrapPart
{
    GENERATED_BODY()
    
public:
    AMyCustomPart();
    
    // Специфичные свойства детали
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CustomProperty = 1.0f;
    
    // Переопределение базовых функций
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
protected:
    // Специфичная логика
    void CustomFunction();
};
```

#### 2. Реализация класса
```cpp
// Source: Source/ScrapArchitect/Building/MyCustomPart.cpp
#include "MyCustomPart.h"

AMyCustomPart::AMyCustomPart()
{
    PrimaryActorTick.bCanEverTick = true;
    
    // Настройка компонентов
    MeshComponent->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Meshes/Parts/MyCustomPart")));
    
    // Настройка физики
    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetMassOverrideInKg(NAME_None, 10.0f);
    
    // Добавление сокетов
    ConnectionSockets.Add(FConnectionSocket{
        TEXT("Socket1"),
        FVector(0, 0, 50),
        FRotator::ZeroRotator,
        {EPartCategory::Foundation, EPartCategory::Propulsion},
        false
    });
}

void AMyCustomPart::BeginPlay()
{
    Super::BeginPlay();
    
    // Инициализация детали
    CustomFunction();
}

void AMyCustomPart::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // Обновление логики
}

void AMyCustomPart::CustomFunction()
{
    // Реализация специфичной логики
}
```

#### 3. Создание Blueprint
1. В Content Browser создайте Blueprint класс
2. Выберите родительский класс `MyCustomPart`
3. Настройте визуальные свойства в Blueprint редакторе

#### 4. Добавление в систему
```cpp
// В BuildManager.h
UPROPERTY(EditAnywhere, BlueprintReadWrite)
TArray<TSubclassOf<AScrapPart>> AvailableParts;

// В BuildManager.cpp
AvailableParts.Add(AMyCustomPart::StaticClass());
```

### Создание нового задания

#### 1. Создание структуры данных
```cpp
// В MissionTypes.h
USTRUCT(BlueprintType)
struct FMyMissionObjective
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ObjectiveID;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCompleted = false;
};
```

#### 2. Создание менеджера задания
```cpp
// Header: Source/ScrapArchitect/Gameplay/MyMissionManager.h
UCLASS()
class SCRAPARCHITECT_API UMyMissionManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    void StartMyMission();
    void CheckMyMissionObjectives();
    void CompleteMyMission();
    
protected:
    UPROPERTY()
    TArray<FMyMissionObjective> Objectives;
    
    UPROPERTY()
    bool bMissionActive = false;
};
```

#### 3. Реализация логики
```cpp
// Source: Source/ScrapArchitect/Gameplay/MyMissionManager.cpp
void UMyMissionManager::StartMyMission()
{
    bMissionActive = true;
    
    // Инициализация целей
    Objectives.Empty();
    Objectives.Add(FMyMissionObjective{
        TEXT("OBJ_1"),
        TEXT("Доставьте ящик в указанную точку"),
        false
    });
    
    // Уведомление UI
    if (UUIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<UUIManager>())
    {
        UIManager->ShowNotification(TEXT("Миссия началась!"));
    }
}

void UMyMissionManager::CheckMyMissionObjectives()
{
    if (!bMissionActive) return;
    
    // Проверка выполнения целей
    bool bAllCompleted = true;
    for (FMyMissionObjective& Objective : Objectives)
    {
        if (!Objective.bIsCompleted)
        {
            bAllCompleted = false;
            break;
        }
    }
    
    if (bAllCompleted)
    {
        CompleteMyMission();
    }
}
```

### Работа с физикой

#### 1. Настройка физических ограничений
```cpp
// Создание шарнира
UPhysicsConstraintComponent* CreateHingeConstraint(AScrapPart* Part1, AScrapPart* Part2)
{
    UPhysicsConstraintComponent* Constraint = NewObject<UPhysicsConstraintComponent>(Part1);
    
    // Настройка ограничений
    Constraint->SetConstrainedComponents(
        Part1->GetMeshComponent(),
        NAME_None,
        Part2->GetMeshComponent(),
        NAME_None
    );
    
    // Настройка типа ограничения
    Constraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, 45.0f);
    Constraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Limited, 45.0f);
    Constraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0.0f);
    
    return Constraint;
}
```

#### 2. Обработка столкновений
```cpp
// В ScrapPart.h
UFUNCTION()
void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
                   const FHitResult& Hit);

// В ScrapPart.cpp
void AScrapPart::BeginPlay()
{
    Super::BeginPlay();
    
    // Подписка на события столкновения
    MeshComponent->OnComponentHit.AddDynamic(this, &AScrapPart::OnComponentHit);
}

void AScrapPart::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
                               UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
                               const FHitResult& Hit)
{
    // Вычисление урона
    float ImpactForce = NormalImpulse.Size();
    if (ImpactForce > Strength)
    {
        OnPartDamaged(ImpactForce);
    }
}
```

### Работа с UI

#### 1. Создание виджета
```cpp
// Header: Source/ScrapArchitect/UI/MyWidget.h
UCLASS()
class SCRAPARCHITECT_API UMyWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    // Привязка к Blueprint виджету
    UPROPERTY(meta = (BindWidget))
    class UButton* MyButton;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* MyText;
    
protected:
    virtual void NativeConstruct() override;
    
    UFUNCTION()
    void OnMyButtonClicked();
};
```

#### 2. Реализация виджета
```cpp
// Source: Source/ScrapArchitect/UI/MyWidget.cpp
void UMyWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    // Привязка событий
    if (MyButton)
    {
        MyButton->OnClicked.AddDynamic(this, &UMyWidget::OnMyButtonClicked);
    }
}

void UMyWidget::OnMyButtonClicked()
{
    // Обработка нажатия кнопки
    if (MyText)
    {
        MyText->SetText(FText::FromString(TEXT("Кнопка нажата!")));
    }
}
```

## 🎨 Создание контента

### Создание 3D моделей

#### Требования к моделям
- **Формат:** FBX или OBJ
- **Полигоны:** <1000 для простых деталей, <5000 для сложных
- **Размер:** Соответствовать игровой сетке (1 unit = 1 см)
- **Ориентация:** Y-вперед, Z-вверх
- **Сокеты:** Добавить в Blender как Empty объекты

#### Экспорт из Blender
1. Выберите объект
2. File → Export → FBX
3. Настройки:
   - Scale: 1.0
   - Apply Scale: ✓
   - Apply Unit Scale: ✓
   - Forward: Y Forward
   - Up: Z Up

### Создание материалов

#### Базовый материал
1. Создайте новый Material в Content Browser
2. Настройте базовые параметры:
   - Base Color: основной цвет
   - Metallic: металличность (0-1)
   - Roughness: шероховатость (0-1)
   - Normal: карта нормалей (опционально)

#### Material Instance
1. Создайте Material Instance от базового материала
2. Настройте параметры для конкретной детали
3. Примените к мешу

### Создание звуков

#### Требования к звукам
- **Формат:** WAV или OGG
- **Частота:** 44.1 kHz
- **Битность:** 16-bit
- **Каналы:** Mono для эффектов, Stereo для музыки
- **Длительность:** <5 секунд для эффектов

#### Импорт в UE5
1. Перетащите звуковой файл в Content Browser
2. Настройте параметры:
   - Compression: ADPCM для эффектов, Vorbis для музыки
   - Quality: 70-80%
   - Streaming: для длинных файлов

## 🧪 Тестирование

### Unit тесты
```cpp
// В Source/ScrapArchitect/Tests/BuildSystemTest.cpp
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBuildSystemTest, "ScrapArchitect.BuildSystem", 
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FBuildSystemTest::RunTest(const FString& Parameters)
{
    // Создание тестового мира
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
    
    // Создание тестовой детали
    AScrapPart* TestPart = World->SpawnActor<AScrapPart>();
    
    // Выполнение тестов
    TestTrue(TEXT("Деталь создана"), TestPart != nullptr);
    TestTrue(TEXT("Деталь имеет меш"), TestPart->GetMeshComponent() != nullptr);
    
    // Очистка
    World->DestroyWorld(false);
    
    return true;
}
```

### Интеграционные тесты
```cpp
// Тест взаимодействия систем
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FIntegrationTest, "ScrapArchitect.Integration", 
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FIntegrationTest::RunTest(const FString& Parameters)
{
    // Тест системы сборки и физики
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
    
    // Создание менеджеров
    UBuildManager* BuildManager = World->GetGameInstance()->GetSubsystem<UBuildManager>();
    UPhysicsManager* PhysicsManager = World->GetGameInstance()->GetSubsystem<UPhysicsManager>();
    
    // Тест взаимодействия
    TestTrue(TEXT("Менеджеры созданы"), BuildManager != nullptr && PhysicsManager != nullptr);
    
    World->DestroyWorld(false);
    return true;
}
```

### Ручное тестирование
1. **Функциональное тестирование** - проверка всех функций
2. **Производительность** - измерение FPS и памяти
3. **Совместимость** - тестирование на разных системах
4. **Пользовательский опыт** - удобство использования

## 📝 Документация кода

### Комментарии
```cpp
/**
 * @brief Компонент для управления режимом сборки
 * 
 * Этот компонент отвечает за:
 * - Управление камерой в режиме сборки
 * - Выбор и размещение деталей
 * - Соединение деталей через сокеты
 * - Визуальную обратную связь
 */
UCLASS()
class SCRAPARCHITECT_API UBuildModeComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:
    /**
     * @brief Подбирает деталь для размещения
     * @param Part Указатель на деталь для подбора
     * @return true если деталь успешно подобрана
     */
    UFUNCTION(BlueprintCallable)
    bool PickupPart(AScrapPart* Part);
    
    /**
     * @brief Размещает деталь в указанной позиции
     * @param Location Позиция размещения
     * @param Rotation Поворот детали
     * @return true если деталь успешно размещена
     */
    UFUNCTION(BlueprintCallable)
    bool PlacePart(FVector Location, FRotator Rotation);
};
```

### README файлы
Создавайте README.md файлы в каждой папке с описанием:
- Назначения папки
- Основных классов
- Примеров использования
- Известных проблем

## 🚀 Оптимизация

### Производительность
1. **Профилирование** - используйте Unreal Insights
2. **LOD система** - настройте уровни детализации
3. **Object pooling** - переиспользуйте объекты
4. **Frustum culling** - рендерите только видимые объекты

### Память
1. **Asset streaming** - загружайте ресурсы по требованию
2. **Texture compression** - сжимайте текстуры
3. **Mesh optimization** - оптимизируйте геометрию
4. **Garbage collection** - управляйте памятью

## 🔄 Workflow

### Git workflow
1. **Feature branches** - создавайте ветки для новых функций
2. **Pull requests** - используйте PR для слияния
3. **Code review** - обязательный ревью кода
4. **Squash commits** - объединяйте коммиты перед слиянием

### Соглашения по именованию
- **Классы:** PascalCase (MyClass)
- **Функции:** PascalCase (MyFunction)
- **Переменные:** camelCase (myVariable)
- **Константы:** UPPER_CASE (MY_CONSTANT)
- **Файлы:** PascalCase (MyClass.h/.cpp)

### Структура коммитов
```
feat: добавлена новая деталь "Реактивный двигатель"
fix: исправлена ошибка в системе физики
docs: обновлена документация API
style: форматирование кода
refactor: рефакторинг системы сборки
test: добавлены тесты для BuildManager
```

---

*Документ версии 1.0*  
*Последнее обновление: Декабрь 2024*
