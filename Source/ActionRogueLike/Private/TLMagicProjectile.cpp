// Fill out your copyright notice in the Description page of Project Settings.


#include "TLMagicProjectile.h"

#include "TLActionComponent.h"
#include "TLAttributeComponent.h"
#include "TLGameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TLActionEffect.h"


// Sets default values
ATLMagicProjectile::ATLMagicProjectile()
{
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATLMagicProjectile::OnActorOverlap);
	InitialLifeSpan = 10.0f;
	DamageAmount = 20.0f;
}

void ATLMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		UTLActionComponent* ActionComp = Cast<UTLActionComponent>(OtherActor->GetComponentByClass(UTLActionComponent::StaticClass()));

		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MoveComp->Velocity = -MoveComp->Velocity;
			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		//apply damage and impulse
		if (UTLGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();

			if(ActionComp && HasAuthority())
			{
				ActionComp->AddAction(GetInstigator(), BurningActionClass);
			}
		}
	}
}

