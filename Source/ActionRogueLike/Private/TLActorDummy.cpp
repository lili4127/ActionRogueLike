// Fill out your copyright notice in the Description page of Project Settings.


#include "TLActorDummy.h"

#include "TLAttributeComponent.h"

// Sets default values
ATLActorDummy::ATLActorDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UTLAttributeComponent>("AttributeComp");
	//trigger when health is changed
	AttributeComp->OnHealthChanged.AddDynamic(this, &ATLActorDummy::OnHealthChanged);
}

// Called when the game starts or when spawned
void ATLActorDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATLActorDummy::OnHealthChanged(AActor* InstigatorActor, UTLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

