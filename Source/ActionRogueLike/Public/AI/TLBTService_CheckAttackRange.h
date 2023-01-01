// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TLBTService_CheckAttackRange.generated.h"

class UBlackboardComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UTLBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

public:

	UTLBTService_CheckAttackRange();

protected:

	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector AttackRangeKey;

	/* Max desired attack range of AI pawn */
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxAttackRange;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
