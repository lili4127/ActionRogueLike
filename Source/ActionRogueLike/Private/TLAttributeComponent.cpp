// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAttributeComponent.h"

// Sets default values for this component's properties
UTLAttributeComponent::UTLAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;
}


// Called when the game starts
void UTLAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UTLAttributeComponent::ApplyHealthChange(float Delta)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta); // @fixme: Still nullptr for InstigatorActor parameter

	return ActualDelta != 0;
}

bool UTLAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UTLAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float UTLAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

