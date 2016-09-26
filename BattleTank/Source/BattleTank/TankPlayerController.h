// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = .5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .333333f;

	UPROPERTY(EditAnywhere)
	int32 LineTraceRange = 1000000;
	
	// Called every frame
	void Tick(float DeltaSeconds) override;

	ATank* GetControlledTank() const;
	
	void BeginPlay() override;
	
	// Start the tank moving the barrel so that a shot would hit where the crosshairs intersect the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector & HitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

};
