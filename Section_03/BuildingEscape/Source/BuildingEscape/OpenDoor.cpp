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

void UOpenDoor::TriggerEventsBasedOnCurrentMass()
{
	if(GetTotalCollidingMass() >= RequiredMass)
		OnOpen.Broadcast();
	else
		OnClose.Broadcast();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//PollTriggerVolume();
}
