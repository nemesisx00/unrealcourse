// © 2019 Peter Lunneberg

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool isOpen = false;
	float delayTimer = 0.0f;
	float lastDoorOpenTime = 0.0f;

	UPROPERTY(EditAnywhere)
	float CloseDelay = 2.0f;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float RequiredMass = 50.0f;

	void CloseDoorIfTime();
	float GetTotalCollidingMass();
	void MoveDoor(bool open = true);
	void PollTriggerVolume();
};
