// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAttributeComponent.h"

// Sets default values for this component's properties
UTLAttributeComponent::UTLAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;
}

UTLAttributeComponent* UTLAttributeComponent::GetAttributes(AActor* FromActor)
{
	if(FromActor)
	{
		return Cast<UTLAttributeComponent>(FromActor->GetComponentByClass(UTLAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UTLAttributeComponent::IsActorAlive(AActor* Actor)
{
	UTLAttributeComponent* AttributeComp = GetAttributes(Actor);
	if(AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}


// Called when the game starts
void UTLAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UTLAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}

bool UTLAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{

	if(!GetOwner()->CanBeDamaged())
	{
		return false;
	}

	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

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

