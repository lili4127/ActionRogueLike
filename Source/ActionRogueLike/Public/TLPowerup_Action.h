// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLPowerupActor.h"
#include "TLPowerup_Action.generated.h"

class UTLAction;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ATLPowerup_Action : public ATLPowerupActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Powerup")
	TSubclassOf<UTLAction> ActionToGrant;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;
};
