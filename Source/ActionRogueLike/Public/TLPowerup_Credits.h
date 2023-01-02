// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLPowerupActor.h"
#include "TLPowerup_Credits.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ATLPowerup_Credits : public ATLPowerupActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditsAmount;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

	ATLPowerup_Credits();
};
