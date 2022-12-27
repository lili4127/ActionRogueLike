// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLPowerupActor.h"
#include "TLPowerup_HealthPotion.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ATLPowerup_HealthPotion : public ATLPowerupActor
{
	GENERATED_BODY()

public:

	ATLPowerup_HealthPotion();

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	// float healt amount?
	
};
