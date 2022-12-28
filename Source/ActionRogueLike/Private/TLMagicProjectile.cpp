// Fill out your copyright notice in the Description page of Project Settings.


#include "TLMagicProjectile.h"

#include "TLAttributeComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ATLMagicProjectile::ATLMagicProjectile()
{
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATLMagicProjectile::OnActorOverlap);
	DamageAmount = 20.0f;
}

void ATLMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		UTLAttributeComponent* AttributeComp = Cast< UTLAttributeComponent>(OtherActor->GetComponentByClass(UTLAttributeComponent::StaticClass()));

		if(AttributeComp)
		{
			// minus in front of DamageAmount to apply the change as damage, not healing
			AttributeComp->ApplyHealthChange(GetInstigator(), -DamageAmount);

			// Only explode when we hit something valid
			Explode();
		}
	}
}

