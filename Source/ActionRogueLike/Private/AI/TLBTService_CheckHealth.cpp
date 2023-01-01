// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TLBTService_CheckHealth.h"
#include "TLAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"



UTLBTService_CheckHealth::UTLBTService_CheckHealth()
{
	LowHealthFraction = 0.3f;
}


void UTLBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ensure(AIPawn))
	{
		UTLAttributeComponent* AttributeComp = UTLAttributeComponent::GetAttributes(AIPawn);
		if (ensure(AttributeComp))
		{
			bool bLowHealth = (AttributeComp->GetHealth() / AttributeComp->GetHealthMax()) < LowHealthFraction;

			UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
			BlackBoardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
		}
	}
}

