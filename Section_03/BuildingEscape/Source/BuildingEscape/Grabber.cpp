// © 2019 Peter Lunneberg

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/CollisionProfile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(inputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber: Input Component found on %s!"), *GetOwner()->GetName());

		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber: Input Component not found on %s!"), *GetOwner()->GetName());
	}

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(physicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber: Physics Handle Component found on %s!"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber: Physics Handle Component not found on %s!"), *GetOwner()->GetName());
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab attempted!"));
}

void UGrabber::PollForGrabbable()
{
	FVector playerViewVector;
	FRotator playerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewVector, playerViewRotation);

	FVector lineTraceEnd = playerViewVector + (playerViewRotation.Vector() * Reach);
	auto objectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	auto queryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	FHitResult result;
	GetWorld()->LineTraceSingleByObjectType(result, playerViewVector, lineTraceEnd, objectParams, queryParams);

	if(result.GetActor())
		UE_LOG(LogTemp, Warning, TEXT("%s"), *result.GetActor()->GetName());
		//Grab(*result.GetActor());
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PollForGrabbable();
}
