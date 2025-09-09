// Copyright (c) 2024 Scrap Architect
using UnrealBuildTool;
using System.Collections.Generic;

public class ScrapArchitectTarget : TargetRules
{
    public ScrapArchitectTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.AddRange(new string[] { "ScrapArchitect" });
    }
}

