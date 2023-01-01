// Fill out your copyright notice in the Description page of Project Settings.


#include "TLActionComponent.h"

#include "TLAction.h"

UTLActionComponent::UTLActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTLActionComponent::AddAction(TSubclassOf<UTLAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}

	UTLAction* NewAction = NewObject<UTLAction>(this, ActionClass);

	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UTLActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for(UTLAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool UTLActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UTLAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}

	return false;
}

void UTLActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for(TSubclassOf<UTLAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
}

void UTLActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

