// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "../MyTestUtils.h"
#include "AutoTestCharacter.h"
#include "EnemyCharacter.h"

BEGIN_DEFINE_SPEC(FNewEnemyCountTest, "AutoTest.ANew.EnemyCountTest", FMyTestUtils::TestsFlags)

	UWorld* World;

END_DEFINE_SPEC(FNewEnemyCountTest)

void FNewEnemyCountTest::Define()
{
	BeforeEach([this]() 
	{
		AutomationOpenMap("/Game/FirstPersonCPP/Maps/FirstPersonExampleMap");
		World = FMyTestUtils::GetWorld();
		TestNotNull("Check if World is properly created", World);
	});

	It("Test Enemy Count", [this]()
	{
		int32 EnemiesCount = 0;
		for (TActorIterator<AActor> It(World, AEnemyCharacter::StaticClass()); It; ++It)
		{
			EnemiesCount++;
		}
		TestTrue("Check if there are 3 enemies on the level", EnemiesCount == 3);
	});

	AfterEach([this]()
	{
		FMyTestUtils::Exit();
	});
}