// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAnimInstance.h"
#include "GameplayTagContainer.h"
#include "TLActionComponent.h"

void UTLAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AActor* OwningActor = GetOwningActor();
	if (OwningActor)
	{
		ActionComp = Cast<UTLActionComponent>(OwningActor->GetComponentByClass(UTLActionComponent::StaticClass()));
	}
}

void UTLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	static FGameplayTag StunnedTag = FGameplayTag::RequestGameplayTag("Status.Stunned");
	if (ActionComp)
	{
		bIsStunned = ActionComp->ActiveGameplayTags.HasTag(StunnedTag);
	}
}