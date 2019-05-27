// © 2019 Peter Lunneberg

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
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

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}

void UGrabber::PollForGrabbable()
{
	FVector playerViewVector;
	FRotator playerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewVector, playerViewRotation);

	UE_LOG(LogTemp, Warning, TEXT("%s | %s"), *playerViewVector.ToString(), *playerViewRotation.ToString());
	
	FVector lineTraceEnd = playerViewVector + (playerViewRotation.Vector() * Reach);
	DrawDebugLine(GetWorld(), playerViewVector, lineTraceEnd, FColor::Red, false, 0.0f, 0.0f, 5.0f);
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PollForGrabbable();
}
