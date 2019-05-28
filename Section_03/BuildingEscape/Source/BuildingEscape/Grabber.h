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

	FHitResult FindGrabbable();
	LinePoints GetReachLinePoints();
	void Grab();
	void Release();
	void SetupInputComponent();
	void SetupPhysicsHandleComponent();
	void UpdateGrabbedComponent();
};
