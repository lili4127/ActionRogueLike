// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TLAICharacter.generated.h"

class UPawnSensingComponent;
class UTLAttributeComponent;
class UUserWidget;
class UTLUserWidget;
class UTLActionComponent;

UCLASS()
class ACTIONROGUELIKE_API ATLAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATLAICharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTLActionComponent* ActionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTLAttributeComponent* AttributeComp;

	UTLUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName TimeToHitParamName;

	void SetTargetActor(AActor* NewTarget);

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UTLAttributeComponent* OwningComp, float NewHealth, float Delta);
};
