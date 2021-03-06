// © 2019 Peter Lunneberg

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	struct LinePoints
	{
		FVector start;
		FVector end;
	};

	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool hasGrabbed = false;
	float lastGrab = 0.0f;
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* inputComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float Reach = 100.0f;

	// Trace a line and detect the first grabbable actor hit.
	FHitResult FindGrabbable();

	// Return the start and end points of the grabber's reach line.
	LinePoints GetReachLinePoints();

	// Attempt to grab an actor.
	void Grab();

	// Attempt to release an actor.
	void Release();

	// Find and configure the Input Component.
	void SetupInputComponent();

	// Find the Physics Handle Component.
	void SetupPhysicsHandleComponent();

	// Update the position of the grabbed component.
	void UpdateGrabbedComponent();
};
