// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TLAnimInstance.generated.h"

class UTLActionComponent;

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API UTLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	/* Is Pawn Stunned based on GameplayTag data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsStunned;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UTLActionComponent* ActionComp;

	void NativeInitializeAnimation() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;

};