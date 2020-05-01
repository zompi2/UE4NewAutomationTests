// (c) 2019 Damian Nowakowski

#include "MyTestUtils.h"
#include "AutoTestCharacter.h"
#include "EnemyCharacter.h"
#include "AssetRegistryModule.h"

IMPLEMENT_COMPLEX_AUTOMATION_TEST(FEnemyCountTestMulti, "AutoTest.EnemyCountTestMulti", FMyTestUtils::TestsFlags)

void FEnemyCountTestMulti::GetTests(TArray<FString>& OutBeautifiedNames, TArray <FString>& OutTestCommands) const
{
	FAssetRegistryModule& ARM = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetDataArray;
	ARM.Get().GetAssetsByPath(TEXT("/Game/FirstPersonCPP/Maps"), AssetDataArray);

	for (const auto& AssetData : AssetDataArray)
	{
		if (AssetData.AssetClass == "World")
		{
			OutBeautifiedNames.Add(AssetData.AssetName.ToString());
			OutTestCommands.Add(AssetData.PackageName.ToString());
		}
	}
}

bool FEnemyCountTestMulti::RunTest(const FString& Parameters)
{
	AutomationOpenMap(Parameters);

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

