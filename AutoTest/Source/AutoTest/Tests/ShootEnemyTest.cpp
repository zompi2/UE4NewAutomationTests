// (c) 2019 Damian Nowakowski

#include "MyTestUtils.h"
#include "AutoTestCharacter.h"
#include "EnemyCharacter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FShootEnemyTest, "AutoTest.ShootEnemyTest", FMyTestUtils::TestsFlags);

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitForEnemyToBeShooted, FShootEnemyTest*, Test);

bool FShootEnemyTest::RunTest(const FString& Parameters)
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

	const bool bFireButtonWasPressed = FMyTestUtils::PressKey(FName("LeftMouseButton"), EInputEvent::IE_Pressed);
	TestTrue("Fire button was properly pressed", bFireButtonWasPressed);
	if (!bFireButtonWasPressed) return false;
	
	ADD_LATENT_AUTOMATION_COMMAND(FEngineWaitLatentCommand(1.f));
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForEnemyToBeShooted(this));
	ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand);

	return true;
}

bool FWaitForEnemyToBeShooted::Update()
{
	int32 EnemiesCount = 0;
	for (TActorIterator<AActor> It(FMyTestUtils::GetWorld(), AEnemyCharacter::StaticClass()); It; ++It)
	{
		EnemiesCount++;
	}
	Test->TestTrue("Check if there are 2 enemies on the level", EnemiesCount == 2);
	
	return true;
}
