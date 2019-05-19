// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyTestUtils.h"
#include "AutoTestCharacter.h"
#include "EnemyCharacter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEnemyCountTest, "AutoTest.EnemyCountTest", FMyTestUtils::TestsFlags)
bool FEnemyCountTest::RunTest(const FString& Parameters)
{
	AutomationOpenMap("/Game/FirstPersonCPP/Maps/FirstPersonExampleMap");

	UWorld* World = FMyTestUtils::GetWorld();
	TestNotNull("Check if World is properly created", World);
	if (!World) return false;

	int32 EnemiesCount = 0;
	for (TActorIterator<AActor> It(World, AEnemyCharacter::StaticClass()); It; ++It)
	{
		EnemiesCount++;
	}
	TestTrue("Check if there are 3 enemies on the level", EnemiesCount == 3);
	
	ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand);

	return true;
}

