// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLProjectileBase.h"
#include "GameplayTagContainer.h"
#include "TLMagicProjectile.generated.h"

class UTLActionEffect;

UCLASS()
class ACTIONROGUELIKE_API ATLMagicProjectile : public ATLProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATLMagicProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UTLActionEffect> BurningActionClass;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
