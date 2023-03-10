// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TLBTService_CheckAttackRange.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UTLBTService_CheckAttackRange::UTLBTService_CheckAttackRange()
{
	MaxAttackRange = 2000.f;
}

void UTLBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//check distance between ai pawn and target actor
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if(ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));

		if(TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();

			if(ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();

				if(ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
					bool bWithinRange = DistanceTo < MaxAttackRange;
					bool bHasLOS = false;

					if(bWithinRange)
					{
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}

					BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLOS));
				}
			}
		}

	}
}
