// Copyright (c) 2024 Scrap Architect
using UnrealBuildTool;
using System.IO;

public class ScrapArchitect : ModuleRules
{
    public ScrapArchitect(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "UMG",
            "Slate",
            "SlateCore",
            "PhysicsCore",
            "Chaos",
            "ChaosSolverEngine",
            "ChaosVehicles",
            "ChaosVehiclesCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            
        });

        PublicIncludePaths.AddRange(new string[]
        {
            
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            
        });
    }
}

