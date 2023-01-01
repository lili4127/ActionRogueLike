// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TLBTTask_HealSelf.h"
#include "TLAttributeComponent.h"
#include "AIController.h"


EBTNodeResult::Type UTLBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* MyPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UTLAttributeComponent* AttributeComp = UTLAttributeComponent::GetAttributes(MyPawn);
	if (ensure(AttributeComp))
	{
		AttributeComp->ApplyHealthChange(MyPawn, AttributeComp->GetHealthMax());
	}

	return EBTNodeResult::Succeeded;
}