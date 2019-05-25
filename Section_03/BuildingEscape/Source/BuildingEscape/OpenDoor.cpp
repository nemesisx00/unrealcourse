// © 2019 Peter Lunneberg

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PollTriggerVolume();
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActivatingActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::MoveDoor(bool open)
{
	auto Owner = GetOwner();
	float angle = open ? OpenAngle : -OpenAngle;
	FRotator rotation = Owner->GetActorRotation();
	rotation.Add(0.0f, angle, 0.0f);
	Owner->SetActorRotation(rotation);

	isOpen = open;
}

void UOpenDoor::PollTriggerVolume()
{
	if(!isOpen && PressurePlate->IsOverlappingActor(ActivatingActor))
	{
		//Stop and reset timer before opening
		MoveDoor();
	}

	if(isOpen && !PressurePlate->IsOverlappingActor(ActivatingActor))
	{
		//Start timer before closing
		MoveDoor(false);
	}
}
