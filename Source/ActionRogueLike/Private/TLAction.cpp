// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAction.h"

void UTLAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running %s"), *GetNameSafe(this));
}

void UTLAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopping %s"), *GetNameSafe(this));
}

UWorld* UTLAction::GetWorld() const
{
	//Outer is set when creating action via NewObject<T>
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());

	if(Comp)
	{
		return Comp->GetWorld();
	}
	return nullptr;

}
