// Fill out your copyright notice in the Description page of Project Settings.


#include "TLGameplayFunctionLibrary.h"

#include "TLAttributeComponent.h"

bool UTLGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UTLAttributeComponent* AttributeComp = UTLAttributeComponent::GetAttributes(TargetActor);

	if(AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}

	return false;
}

bool UTLGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if(ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();

		if(HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			//Direction = Target - Origin
			FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
			Direction.Normalize();

			HitComp->AddImpulseAtLocation(Direction * 300000.0f, HitResult.ImpactPoint, HitResult.BoneName);
		}

		return true;
	}

	return false;
}
