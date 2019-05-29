// © 2019 Peter Lunneberg

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if(!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("Open Door: Pressure Plate missing on %s"), *GetOwner()->GetName());
}

void UOpenDoor::CloseDoorIfTime()
{
	auto now = GetWorld()->GetTimeSeconds();
	if(now - lastDoorOpenTime >= CloseDelay)
	{
		MoveDoor(false);
		isOpen = false;
	}
}

float UOpenDoor::GetTotalCollidingMass()
{
	float mass = 0.0f;

	if(PressurePlate)
	{
		TSet<AActor*> actors;
		PressurePlate->GetOverlappingActors(actors);

		for(const auto* actor : actors)
		{
			mass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}

	return mass;
}

void UOpenDoor::MoveDoor(bool opening)
{
	auto Owner = GetOwner();
	float angle = opening ? OpenAngle : -OpenAngle;
	FRotator rotation = Owner->GetActorRotation();
	rotation.Add(0.0f, angle, 0.0f);
	Owner->SetActorRotation(rotation);
}

void UOpenDoor::PollTriggerVolume()
{
	if(GetTotalCollidingMass() >= RequiredMass)
	{
		if(!isOpen)
			MoveDoor();
		isOpen = true;
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if(isOpen)
			CloseDoorIfTime();
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PollTriggerVolume();
}
