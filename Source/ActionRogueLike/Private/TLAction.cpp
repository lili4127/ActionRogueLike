// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAction.h"
#include "TLActionComponent.h"
#include "ActionRogueLike/ActionRogueLike.h"
#include "Net/UnrealNetwork.h"

void UTLAction::Initialize(UTLActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

bool UTLAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	UTLActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}

void UTLAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Started: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);

	UTLActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;

	if (GetOwningComponent()->GetOwnerRole() == ROLE_Authority)
	{
		TimeStarted = GetWorld()->TimeSeconds;
	}

	GetOwningComponent()->OnActionStarted.Broadcast(GetOwningComponent(), this);
}

void UTLAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Stopped: %s"), *ActionName.ToString()), FColor::White);

	//ensureAlways(bIsRunning);

	UTLActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	RepData.bIsRunning = false;
	RepData.Instigator = Instigator;

	GetOwningComponent()->OnActionStopped.Broadcast(GetOwningComponent(), this);
}

UWorld* UTLAction::GetWorld() const
{
	// Outer is set when creating action via NewObject<T>
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}

UTLActionComponent* UTLAction::GetOwningComponent() const
{
	//AActor* Actor = Cast<AActor>(GetOuter());
	//return Actor->GetComponentByClass(UTLActionComponent::StaticClass());

	return ActionComp;
}

void UTLAction::OnRep_RepData()
{
	if (RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StopAction(RepData.Instigator);
	}
}

bool UTLAction::IsRunning() const
{
	return RepData.bIsRunning;
}

void UTLAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTLAction, RepData);
	DOREPLIFETIME(UTLAction, TimeStarted);
	DOREPLIFETIME(UTLAction, ActionComp);
}