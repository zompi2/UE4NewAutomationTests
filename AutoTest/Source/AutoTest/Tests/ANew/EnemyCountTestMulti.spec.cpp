// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "../MyTestUtils.h"
#include "AutoTestCharacter.h"
#include "EnemyCharacter.h"
#include "AssetRegistryModule.h"

BEGIN_DEFINE_SPEC(FNewEnemyCountTestMulti, "AutoTest.ANew.EnemyCountTestMulti", FMyTestUtils::TestsFlags)

UWorld* World;

END_DEFINE_SPEC(FNewEnemyCountTestMulti)

void FNewEnemyCountTestMulti::Define()
{
	FAssetRegistryModule& ARM = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetDataArray;
	ARM.Get().GetAssetsByPath(TEXT("/Game/FirstPersonCPP/Maps"), AssetDataArray);

	for (const auto& AssetData : AssetDataArray)
	{
		if (AssetData.AssetClass == "World")
		{
			Describe(AssetData.AssetName.ToString(), [this, AssetData]()
			{
				BeforeEach([this, AssetData]()
				{
					AutomationOpenMap(AssetData.PackageName.ToString());
					World = FMyTestUtils::GetWorld();
					TestNotNull("Check if World is properly created", World);
				});

				It("Check Enemy Count", [this]()
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
			});
		}
	}
}