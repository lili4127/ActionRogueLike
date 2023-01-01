// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "TLActionComponent.generated.h"

class UTLAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UTLActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTLActionComponent();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AddAction(TSubclassOf<UTLAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer ActiveGameplayTags;


protected:
	virtual void BeginPlay() override;

	//Granted Abilities at Game Start
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<UTLAction>> DefaultActions;

	UPROPERTY()
	TArray<UTLAction*> Actions;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
