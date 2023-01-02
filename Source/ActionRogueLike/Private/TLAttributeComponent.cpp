// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAttributeComponent.h"

#include "TLGameModeBase.h"
#include "Net/UnrealNetwork.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("tl.DamageMultiplier"), 1.0f, TEXT("Global damage modifier for Attribute Component"), ECVF_Cheat);

// Sets default values for this component's properties
UTLAttributeComponent::UTLAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;

	SetIsReplicatedByDefault(true);
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

	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = NewHealth - OldHealth;

	// Is Server?
	if (GetOwner()->HasAuthority())
	{
		Health = NewHealth;

		if (ActualDelta != 0.0f)
		{
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
		}

		// Died
		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			ATLGameModeBase* GM = GetWorld()->GetAuthGameMode<ATLGameModeBase>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}

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

float UTLAttributeComponent::GetHealth() const
{
	return Health;
}

float UTLAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

void UTLAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTLAttributeComponent, Health);
	DOREPLIFETIME(UTLAttributeComponent, HealthMax);

	//DOREPLIFETIME(UTLAttributeComponent, Rage);
	//DOREPLIFETIME(UTLAttributeComponent, RageMax);
}

void UTLAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}