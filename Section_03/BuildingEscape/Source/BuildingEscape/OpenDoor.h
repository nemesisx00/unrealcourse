// © 2019 Peter Lunneberg

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCheckMass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RequiredMass = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ATriggerVolume* PressurePlate = nullptr;

	UFUNCTION(BlueprintCallable)
	void TriggerEventsBasedOnCurrentMass();
	
private:
	float GetTotalCollidingMass();
};
