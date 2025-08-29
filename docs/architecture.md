# Архитектура проекта: Scrap Architect: Unreal Revival

## 🏗 Общая архитектура

### Принципы проектирования
1. **Component-based архитектура** - модульность и переиспользование
2. **Event-driven система** - слабая связанность компонентов
3. **MVC паттерн** - разделение логики и представления
4. **Data-driven подход** - настройка через Scriptable Objects

### Структура проекта

```
ScrapArchitect/
├── Content/                          # Unreal Engine контент
│   ├── Blueprints/                   # Blueprint классы
│   ├── Materials/                    # Материалы
│   ├── Meshes/                       # 3D модели
│   ├── Textures/                     # Текстуры
│   ├── Sounds/                       # Звуки
│   ├── UI/                          # Пользовательский интерфейс
│   └── Levels/                      # Уровни игры
├── Source/                          # C++ исходный код
│   └── ScrapArchitect/              # Основной модуль
│       ├── Core/                    # Основные системы
│       ├── Building/                # Система сборки
│       ├── Physics/                 # Физические системы
│       ├── Vehicles/                # Система транспорта
│       ├── Gameplay/                # Игровые механики
│       ├── UI/                      # Пользовательский интерфейс
│       └── Utils/                   # Утилиты
└── Config/                          # Конфигурационные файлы
```

## 🔧 Основные системы

### 1. Система сборки (Building System)

#### Компоненты
```cpp
// Основной компонент сборки
UCLASS()
class SCRAPARCHITECT_API UBuildModeComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:
    // Состояния сборки
    UENUM()
    enum class EBuildState
    {
        Idle,
        Selecting,
        Placing,
        Connecting,
        Testing
    };
    
    UPROPERTY(BlueprintReadOnly)
    EBuildState CurrentState = EBuildState::Idle;
    
    // Управление камерой
    void HandleCameraInput(FVector2D Movement, FVector2D Rotation, float Zoom);
    
    // Управление деталями
    void PickupPart(AScrapPart* Part);
    void PlacePart(FVector Location, FRotator Rotation);
    void ConnectParts(AScrapPart* Part1, AScrapPart* Part2);
    
    // Визуальная обратная связь
    void ShowConnectionPreview();
    void HighlightCompatibleSockets();
    
protected:
    UPROPERTY()
    AScrapPart* SelectedPart = nullptr;
    
    UPROPERTY()
    AScrapPart* HoveredPart = nullptr;
};
```

#### Менеджер сборки
```cpp
UCLASS()
class SCRAPARCHITECT_API UBuildManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Управление режимами
    void EnterBuildMode();
    void ExitBuildMode();
    void EnterTestMode();
    void ExitTestMode();
    
    // Управление деталями
    void SpawnPart(TSubclassOf<AScrapPart> PartClass, FVector Location);
    void DeletePart(AScrapPart* Part);
    void DuplicatePart(AScrapPart* Part);
    
    // Сохранение/загрузка
    void SaveVehicle(const FString& VehicleName);
    void LoadVehicle(const FString& VehicleName);
    
protected:
    UPROPERTY()
    TArray<AScrapPart*> AllParts;
    
    UPROPERTY()
    UBuildModeComponent* BuildComponent = nullptr;
};
```

### 2. Система деталей (Parts System)

#### Базовый класс детали
```cpp
UCLASS()
class SCRAPARCHITECT_API AScrapPart : public AActor
{
    GENERATED_BODY()
    
public:
    AScrapPart();
    
    // Основные компоненты
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* MeshComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UPhysicsConstraintComponent* ConstraintComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UBoxComponent* CollisionComponent;
    
    // Свойства детали
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPartData PartData;
    
    // Сокеты для соединения
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FConnectionSocket> ConnectionSockets;
    
    // Физические свойства
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Mass = 1.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Strength = 100.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 0.0f;
    
    // События
    UFUNCTION(BlueprintCallable)
    void OnPartDamaged(float DamageAmount);
    
    UFUNCTION(BlueprintCallable)
    void OnPartDestroyed();
    
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
    // Визуальные эффекты
    void UpdateVisualState();
    void SpawnDestructionEffects();
};
```

#### Структуры данных
```cpp
USTRUCT(BlueprintType)
struct FPartData
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PartID;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DisplayName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPartCategory Category;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 UnlockLevel = 1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ScrapCost = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Mesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialInterface* Material;
};

USTRUCT(BlueprintType)
struct FConnectionSocket
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector LocalPosition;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator LocalRotation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EPartCategory> CompatibleCategories;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOccupied = false;
};
```

### 3. Физическая система (Physics System)

#### Менеджер физики
```cpp
UCLASS()
class SCRAPARCHITECT_API UPhysicsManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Настройка физики
    void InitializePhysics();
    void SetPhysicsEnabled(bool bEnabled);
    
    // Управление ограничениями
    UPhysicsConstraintComponent* CreateConstraint(
        AScrapPart* Part1, 
        AScrapPart* Part2, 
        FName Socket1, 
        FName Socket2,
        EConstraintType Type
    );
    
    void DestroyConstraint(UPhysicsConstraintComponent* Constraint);
    
    // Симуляция
    void StartSimulation();
    void StopSimulation();
    void ResetSimulation();
    
    // События
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartCollision, AScrapPart*, Part);
    UPROPERTY(BlueprintAssignable)
    FOnPartCollision OnPartCollision;
    
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartDestroyed, AScrapPart*, Part);
    UPROPERTY(BlueprintAssignable)
    FOnPartDestroyed OnPartDestroyed;
    
protected:
    UPROPERTY()
    TArray<UPhysicsConstraintComponent*> ActiveConstraints;
    
    UPROPERTY()
    bool bPhysicsEnabled = false;
};
```

#### Типы ограничений
```cpp
UENUM(BlueprintType)
enum class EConstraintType : uint8
{
    Fixed,          // Жесткое соединение
    Hinge,          // Шарнир
    Prismatic,      // Призматическое
    Spherical,      // Сферическое
    Spring,         // Пружина
    Cable           // Трос
};
```

### 4. Система транспорта (Vehicle System)

#### Контроллер транспорта
```cpp
UCLASS()
class SCRAPARCHITECT_API UVehicleController : public UActorComponent
{
    GENERATED_BODY()
    
public:
    // Управление движением
    void HandleThrottle(float Input);
    void HandleSteering(float Input);
    void HandleBrake(float Input);
    
    // Управление инструментами
    void ActivateTool(int32 ToolIndex);
    void DeactivateTool(int32 ToolIndex);
    void SwitchTool(int32 ToolIndex);
    
    // Камера
    void SwitchCameraView();
    void HandleCameraLook(FVector2D Input);
    void ResetCamera();
    
    // Состояние
    bool IsVehicleOperational() const;
    float GetVehicleHealth() const;
    
protected:
    UPROPERTY()
    TArray<AScrapPart*> VehicleParts;
    
    UPROPERTY()
    TArray<UToolComponent*> Tools;
    
    UPROPERTY()
    UCameraComponent* DriverCamera = nullptr;
    
    UPROPERTY()
    float VehicleHealth = 100.0f;
};
```

#### Компонент инструмента
```cpp
UCLASS()
class SCRAPARCHITECT_API UToolComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:
    // Активация/деактивация
    UFUNCTION(BlueprintCallable)
    void Activate();
    
    UFUNCTION(BlueprintCallable)
    void Deactivate();
    
    // Состояние
    UPROPERTY(BlueprintReadOnly)
    bool bIsActive = false;
    
    UPROPERTY(BlueprintReadOnly)
    float EnergyConsumption = 0.0f;
    
    // События
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToolActivated);
    UPROPERTY(BlueprintAssignable)
    FOnToolActivated OnToolActivated;
    
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToolDeactivated);
    UPROPERTY(BlueprintAssignable)
    FOnToolDeactivated OnToolDeactivated;
    
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
    // Логика инструмента
    virtual void OnActivate();
    virtual void OnDeactivate();
    virtual void OnTick(float DeltaTime);
};
```

### 5. Система заданий (Mission System)

#### Менеджер заданий
```cpp
UCLASS()
class SCRAPARCHITECT_API UMissionManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Управление заданиями
    void LoadMissions();
    void StartMission(const FString& MissionID);
    void CompleteMission(const FString& MissionID);
    void FailMission(const FString& MissionID);
    
    // Прогресс
    bool IsMissionCompleted(const FString& MissionID) const;
    float GetMissionProgress(const FString& MissionID) const;
    
    // Награды
    void GrantRewards(const FString& MissionID);
    
protected:
    UPROPERTY()
    TMap<FString, FMissionData> Missions;
    
    UPROPERTY()
    TSet<FString> CompletedMissions;
    
    UPROPERTY()
    FString CurrentMissionID;
};
```

#### Структура задания
```cpp
USTRUCT(BlueprintType)
struct FMissionData
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MissionID;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DisplayName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMissionType Type;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredLevel = 1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> RequiredMissions;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FMissionRewards Rewards;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FMissionObjective> Objectives;
};
```

### 6. Система прогрессии (Progression System)

#### Менеджер прогрессии
```cpp
UCLASS()
class SCRAPARCHITECT_API UProgressionManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Опыт и уровни
    void AddExperience(int32 Amount);
    int32 GetCurrentLevel() const;
    int32 GetCurrentExperience() const;
    int32 GetExperienceToNextLevel() const;
    
    // Скрап (валюта)
    void AddScrap(int32 Amount);
    void SpendScrap(int32 Amount);
    int32 GetScrapAmount() const;
    
    // Разблокировка
    bool IsPartUnlocked(const FString& PartID) const;
    void UnlockPart(const FString& PartID);
    
    // Достижения
    void UnlockAchievement(const FString& AchievementID);
    bool IsAchievementUnlocked(const FString& AchievementID) const;
    
protected:
    UPROPERTY()
    int32 PlayerLevel = 1;
    
    UPROPERTY()
    int32 CurrentExperience = 0;
    
    UPROPERTY()
    int32 ScrapAmount = 0;
    
    UPROPERTY()
    TSet<FString> UnlockedParts;
    
    UPROPERTY()
    TSet<FString> UnlockedAchievements;
};
```

### 7. Система сохранения (Save System)

#### Менеджер сохранения
```cpp
UCLASS()
class SCRAPARCHITECT_API USaveManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Сохранение/загрузка
    void SaveGame(const FString& SaveSlot);
    void LoadGame(const FString& SaveSlot);
    void DeleteSave(const FString& SaveSlot);
    
    // Автосохранение
    void EnableAutoSave(bool bEnable);
    void SetAutoSaveInterval(float Interval);
    
    // Настройки
    void SaveSettings(const FGameSettings& Settings);
    FGameSettings LoadSettings();
    
protected:
    UPROPERTY()
    bool bAutoSaveEnabled = true;
    
    UPROPERTY()
    float AutoSaveInterval = 300.0f; // 5 минут
    
    UPROPERTY()
    FTimerHandle AutoSaveTimer;
    
    void PerformAutoSave();
};
```

#### Структура сохранения
```cpp
USTRUCT()
struct FSaveGameData
{
    GENERATED_BODY()
    
    // Прогресс игрока
    UPROPERTY()
    int32 PlayerLevel = 1;
    
    UPROPERTY()
    int32 CurrentExperience = 0;
    
    UPROPERTY()
    int32 ScrapAmount = 0;
    
    UPROPERTY()
    TSet<FString> UnlockedParts;
    
    UPROPERTY()
    TSet<FString> CompletedMissions;
    
    UPROPERTY()
    TSet<FString> UnlockedAchievements;
    
    // Сохраненные машины
    UPROPERTY()
    TArray<FVehicleBlueprint> SavedVehicles;
    
    // Настройки
    UPROPERTY()
    FGameSettings Settings;
    
    // Метаданные
    UPROPERTY()
    FDateTime SaveDate;
    
    UPROPERTY()
    float TotalPlayTime = 0.0f;
};
```

## 🎨 UI/UX архитектура

### Система интерфейса
```cpp
UCLASS()
class SCRAPARCHITECT_API UUIManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Управление экранами
    void ShowScreen(const FString& ScreenName);
    void HideScreen(const FString& ScreenName);
    void ShowModal(const FString& ModalName);
    void HideModal();
    
    // HUD
    void UpdateHUD();
    void ShowNotification(const FString& Message, float Duration = 3.0f);
    
    // Инвентарь
    void OpenInventory();
    void CloseInventory();
    void UpdateInventory();
    
protected:
    UPROPERTY()
    TMap<FString, UUserWidget*> Screens;
    
    UPROPERTY()
    UUserWidget* CurrentModal = nullptr;
    
    UPROPERTY()
    UUserWidget* HUDWidget = nullptr;
};
```

### Основные экраны
- **Главное меню** - старт игры, настройки, выход
- **Карта мира** - выбор заданий
- **Режим сборки** - интерфейс конструктора
- **Инвентарь** - управление деталями
- **Настройки** - графические и игровые опции
- **HUD** - информация во время игры

## 🔧 Оптимизация

### Производительность
1. **LOD система** - автоматическое снижение детализации
2. **Object pooling** - переиспользование объектов
3. **Frustum culling** - рендеринг только видимых объектов
4. **Level streaming** - загрузка уровней по частям

### Память
1. **Asset streaming** - загрузка ресурсов по требованию
2. **Texture compression** - сжатие текстур
3. **Mesh optimization** - оптимизация геометрии
4. **Garbage collection** - управление памятью

## 🧪 Тестирование

### Автоматизированные тесты
```cpp
// Unit тесты для основных систем
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBuildSystemTest, "ScrapArchitect.BuildSystem", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FBuildSystemTest::RunTest(const FString& Parameters)
{
    // Тестирование системы сборки
    return true;
}
```

### Интеграционные тесты
- Тестирование взаимодействия систем
- Проверка производительности
- Валидация игрового баланса

---

*Документ версии 1.0*  
*Последнее обновление: Декабрь 2024*
