// Fill out your copyright notice in the Description page of Project Settings.


#include "TLPowerupActor.h"
#include "Components/SphereComponent.h"

// Sets default values
ATLPowerupActor::ATLPowerupActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;

}

void ATLPowerupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	// logic in derived classes...
}


void ATLPowerupActor::ShowPowerup()
{
	SetPowerupState(true);
}


void ATLPowerupActor::HideAndCooldownPowerup()
{
	SetPowerupState(false);

	FTimerHandle TimerHandle_RespawnTimer;
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ATLPowerupActor::ShowPowerup, RespawnTime);
}

void ATLPowerupActor::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	// Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}

