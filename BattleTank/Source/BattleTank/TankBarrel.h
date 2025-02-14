// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max upward movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5; //Sensible starting point

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 45.f;	//Elevation in degrees
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.f;
};
