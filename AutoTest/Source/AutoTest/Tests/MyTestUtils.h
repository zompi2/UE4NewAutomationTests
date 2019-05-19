#pragma once

#include "Engine.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

class FMyTestUtils
{
public:

	/** The flag used when defining tests. */
	static const int32 TestsFlags =	EAutomationTestFlags::EditorContext |
									EAutomationTestFlags::ClientContext |
									EAutomationTestFlags::ProductFilter;

	/** Helper method for getting the game world. */
	static UWorld* GetWorld()
	{
		if (GEngine)
		{
			if (FWorldContext* WorldContext = GEngine->GetWorldContextFromPIEInstance(0))
			{
				return WorldContext->World();
			}
		}

		return nullptr;
	}

	/** Helper method for exiting the game. */
	static void Exit()
	{
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* TargetPC = UGameplayStatics::GetPlayerController(World, 0))
			{
				TargetPC->ConsoleCommand(TEXT("Exit"), true);
			}
		}
	}

	static bool PressKey(const FName& KeyName, EInputEvent InputEvent)
	{
		if (GEngine)
		{
			if (GEngine->GameViewport)
			{
				if (FViewport* Viewport = GEngine->GameViewport->Viewport)
				{
					if (FViewportClient * ViewportClient = Viewport->GetClient())
					{
						return ViewportClient->InputKey(FInputKeyEventArgs(Viewport, 0, KeyName, InputEvent));
					}
				}
			}
		}

		return false;
	}
};

