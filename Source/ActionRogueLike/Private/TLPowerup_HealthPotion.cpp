// Fill out your copyright notice in the Description page of Project Settings.


#include "TLPowerup_HealthPotion.h"
#include "TLPlayerState.h"
#include "TLAttributeComponent.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

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

FText ATLPowerup_HealthPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{

	UTLAttributeComponent* AttributeComp = UTLAttributeComponent::GetAttributes(InstigatorPawn);

	// Check if not already at max health
	if (ensure(AttributeComp) && AttributeComp->IsFullHealth())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health");
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits, Restores Health To Maximum"), CreditCost);

}

#undef LOCTEXT_NAMESPACE