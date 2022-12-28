// Fill out your copyright notice in the Description page of Project Settings.


#include "TLItemChest.h"

// Sets default values
ATLItemChest::ATLItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110.0f;
}

void ATLItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
	ITLGameplayInterface::Interact_Implementation(InstigatorPawn);
}

