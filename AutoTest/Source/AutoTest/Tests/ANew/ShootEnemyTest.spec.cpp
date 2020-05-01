// (c) 2019 Damian Nowakowski

#include "../MyTestUtils.h"
#include "AutoTestCharacter.h"
#include "EnemyCharacter.h"
#include "Async.h"

BEGIN_DEFINE_SPEC(FNewShootEnemyTest, "AutoTest.ANew.ShootEnemyTest", FMyTestUtils::TestsFlags)

UWorld* World;

END_DEFINE_SPEC(FNewShootEnemyTest)

void FNewShootEnemyTest::Define()
{
	BeforeEach([this]()
	{
		AutomationOpenMap("/Game/FirstPersonCPP/Maps/FirstPersonExampleMap");
		World = FMyTestUtils::GetWorld();
		TestNotNull("Check if World is properly created", World);
	});

	LatentIt("Test Enemy Shoot", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
	{
		AsyncTask(ENamedThreads::GameThread, [this]() {
			int32 EnemiesCount = 0;
			for (TActorIterator<AActor> It(World, AEnemyCharacter::StaticClass()); It; ++It)
			{
				EnemiesCount++;
			}
			TestTrue("Check if there are 3 enemies on the level", EnemiesCount == 3);

			const bool bFireButtonWasPressed = FMyTestUtils::PressKey(FName("LeftMouseButton"), EInputEvent::IE_Pressed);
			TestTrue("Fire button was properly pressed", bFireButtonWasPressed);
		});
		
		float StartTime = FPlatformTime::Seconds();
		while (FPlatformTime::Seconds() - StartTime < 1.f)
		{
			FPlatformProcess::Sleep(0.1f);
		}

		AsyncTask(ENamedThreads::GameThread, [this]() {
			int32 EnemiesCount = 0;
			for (TActorIterator<AActor> It(FMyTestUtils::GetWorld(), AEnemyCharacter::StaticClass()); It; ++It)
			{
				EnemiesCount++;
			}
			TestTrue("Check if there are 2 enemies on the level", EnemiesCount == 2);
		});

		TestDone.Execute();
	});

	AfterEach([this]()
	{
		FMyTestUtils::Exit();
	});
}