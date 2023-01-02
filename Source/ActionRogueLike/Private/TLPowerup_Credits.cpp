// Fill out your copyright notice in the Description page of Project Settings.


#include "TLPowerup_Credits.h"
#include "TLPlayerState.h"

ATLPowerup_Credits::ATLPowerup_Credits()
{
	CreditsAmount = 80;
}


void ATLPowerup_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (ATLPlayerState* PS = InstigatorPawn->GetPlayerState<ATLPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldownPowerup();
	}
}