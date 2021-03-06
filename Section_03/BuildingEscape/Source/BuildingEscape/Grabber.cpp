// © 2019 Peter Lunneberg

#include "Grabber.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/CollisionProfile.h"
#include "Engine/World.h"

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

	SetupInputComponent();
	SetupPhysicsHandleComponent();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}

FHitResult UGrabber::FindGrabbable()
{
	auto points = GetReachLinePoints();
	auto objectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	auto queryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult result;
	GetWorld()->LineTraceSingleByObjectType(result, points.start, points.end, objectParams, queryParams);
	
	return result;
}

UGrabber::LinePoints UGrabber::GetReachLinePoints()
{
	FVector playerViewVector;
	FRotator playerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewVector, playerViewRotation);
	FVector reachEnd = playerViewVector + (playerViewRotation.Vector() * Reach);

	return LinePoints { playerViewVector, reachEnd };
}

void UGrabber::Grab()
{
	auto now = GetWorld()->GetTimeSeconds();
	if(physicsHandle && !physicsHandle->GrabbedComponent && now > lastGrab)
	{
		auto result = FindGrabbable();
		auto comp = result.GetComponent();

		if(result.GetActor())
		{
			lastGrab = now;
			physicsHandle->GrabComponentAtLocationWithRotation(comp, NAME_None, comp->GetOwner()->GetActorLocation(), comp->GetOwner()->GetActorRotation());
		}
	}
}

void UGrabber::Release()
{
	auto now = GetWorld()->GetTimeSeconds();
	if(physicsHandle && physicsHandle->GrabbedComponent && now > lastGrab)
	{
		physicsHandle->ReleaseComponent();
	}
}

void UGrabber::SetupInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(inputComponent)
	{
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Grab);
		inputComponent->BindAction("Release", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber: Input Component not found on %s!"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupPhysicsHandleComponent()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!physicsHandle)
		UE_LOG(LogTemp, Error, TEXT("Grabber: Physics Handle Component not found on %s!"), *GetOwner()->GetName());
}

void UGrabber::UpdateGrabbedComponent()
{
	//Update position/physics of actor
	if(physicsHandle && physicsHandle->GrabbedComponent)
	{
		auto points = GetReachLinePoints();
		physicsHandle->SetTargetLocation(points.end);
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateGrabbedComponent();
}
