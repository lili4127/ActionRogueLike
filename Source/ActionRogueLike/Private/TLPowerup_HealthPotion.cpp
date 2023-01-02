// Fill out your copyright notice in the Description page of Project Settings.


#include "TLPowerup_HealthPotion.h"
#include "TLPlayerState.h"
#include "TLAttributeComponent.h"

ATLPowerup_HealthPotion::ATLPowerup_HealthPotion()
{
	CreditCost = 50;
}


void ATLPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UTLAttributeComponent* AttributeComp = UTLAttributeComponent::GetAttributes(InstigatorPawn);

	// Check if not already at max health
	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if (ATLPlayerState* PS = InstigatorPawn->GetPlayerState<ATLPlayerState>())
		{
			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
			{
				// Only activate if healed successfully
				HideAndCooldownPowerup();
			}
		}
	}
}

