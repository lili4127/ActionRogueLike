// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TLAICharacter.h"

// Sets default values
ATLAICharacter::ATLAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATLAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATLAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

