using UnrealBuildTool;
using System.Collections.Generic;

public class PIStage : ModuleRules
{
	public PIStage(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivatePCHHeaderFile = "Public/PIStage.h";

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
            "CoreUObject",
			"Engine",
            "PoppIt"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
	}
}