// Fill out your copyright notice in the Description page of Project Settings.


#include "TLInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "TLGameplayInterface.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("tl.InteractionDebugDraw"), false, TEXT("Enable Debug Lines For Interact Component"), ECVF_Cheat);

UTLInteractionComponent::UTLInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTLInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTLInteractionComponent::PrimaryInteract()
{

	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	float Radius = 30.0f;
	Shape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for(FHitResult Hit : Hits)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
		}

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UTLGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				ITLGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
	}

	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
	}
	
}

