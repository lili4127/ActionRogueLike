// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TLAICharacter.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "TLAttributeComponent.h"
#include "TLActionComponent.h"
#include "TLCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "BrainComponent.h"
#include "TLUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATLAICharacter::ATLAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
	AttributeComp = CreateDefaultSubobject<UTLAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<UTLActionComponent>("ActionComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	TimeToHitParamName = "TimeToHit";
}


void ATLAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ATLAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &ATLAICharacter::OnHealthChanged);
}

void ATLAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}

void ATLAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "PlayerSpotted", nullptr, FColor::White, 4.0f, true);
}

void ATLAICharacter::OnHealthChanged(AActor* InstigatorActor, UTLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(Delta < 0.0f)
	{

		if(InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		if(ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<UTLUserWidget>(GetWorld(), HealthBarWidgetClass);

			if (ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}

		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);

		//Died
		if(NewHealth <= 0.0f)
		{
			//Stop BT
			AAIController* AIC = Cast<AAIController>(GetController());

			if(AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			//Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			//Set Lifespan
			SetLifeSpan(10.0f);
		}
	}
}

