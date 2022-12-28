// Fill out your copyright notice in the Description page of Project Settings.


#include "TLGameModeBase.h"

#include "DrawDebugHelpers.h"
#include "TLAttributeComponent.h"
#include "AI/TLAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EngineUtils.h"

ATLGameModeBase::ATLGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void ATLGameModeBase::StartPlay()
{
	Super::StartPlay();

	//Continuous timer to spawn in bots
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ATLGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ATLGameModeBase::KillAll()
{
	for (TActorIterator<ATLAICharacter> It(GetWorld()); It; ++It)
	{
		ATLAICharacter* Bot = *It;
		UTLAttributeComponent* AttributeComp = UTLAttributeComponent::GetAttributes(Bot);

		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this); // @fixme: pass in player for kill credit?
		}

	}
}

void ATLGameModeBase::SpawnBotTimerElapsed()
{

	int32 NrOfAliveBots = 0;
	for (TActorIterator<ATLAICharacter> It(GetWorld()); It; ++It)
	{
		ATLAICharacter* Bot = *It;
		UTLAttributeComponent* AttributeComp = UTLAttributeComponent::GetAttributes(Bot);

		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}

	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots."), NrOfAliveBots);

	float MaxBotCount = 10.0f;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity. Skipping bot spawn."));
		return;
	}

	// Run EQS to find valid spawn location
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ATLGameModeBase::OnBotSpawnQueryCompleted);
	}
}

void ATLGameModeBase::OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed!"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		{
			GetWorld()->SpawnActor<AActor>(MonsterClass, Locations[0], FRotator::ZeroRotator);
			DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
		}
	}
}