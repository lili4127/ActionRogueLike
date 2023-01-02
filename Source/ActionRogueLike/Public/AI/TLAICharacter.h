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

	ATLAICharacter();

protected:

	UPROPERTY()
	UTLUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	/* Widget to display when bot first sees a player. */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SpottedWidgetClass;

	/* Material parameter for Hitflashes */
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	/* Key for AI Blackboard 'TargetActor' */
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TargetActorKey;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetTargetActor(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = "AI")
	AActor* GetTargetActor() const;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UTLAttributeComponent* OwningComp, float NewHealth, float Delta);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTLAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTLActionComponent* ActionComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPawnSeen();

	// -- Significance Manager -- //

	/* Accessor for Blueprint to skip playing Audio or VFX based on significance thresholds */
	//UFUNCTION(BlueprintPure, Category = "Optimization")
	//bool IsSignificant(float RequiredSignificance = 0.0f) const;
};
