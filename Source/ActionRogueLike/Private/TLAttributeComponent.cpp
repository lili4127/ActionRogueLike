// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAttributeComponent.h"

// Sets default values for this component's properties
UTLAttributeComponent::UTLAttributeComponent()
{
	Health = 100.0f;
}


// Called when the game starts
void UTLAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UTLAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}

bool UTLAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

