// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Set Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.f; // Assume 40 ton driving force of 10 m/s

	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
private:

	UTankTrack();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void ApplySidewaysForce();
	
	void DriveTrack();

	float CurrentThrottle = 0.f;
};
