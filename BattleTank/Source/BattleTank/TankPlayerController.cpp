// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }
	FoundAimingComponent(TankAimingComponent);
	
	
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; } // eg. if not possessing
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Got Hit Location is %i"), bGotHitLocation);
	if(bGotHitLocation){
		// Tell tank to aim at point
		TankAimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {

	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);
	auto ScreenLocation = FVector2D(SizeX * CrossHairXLocation, SizeY * CrossHairYLocation);
	FVector LookDirection;
	// De-project the screen position of the crosshair to a world direction
	bool bHit = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT HitLocation, OUT LookDirection);

	if (bHit) {
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector::ZeroVector;
	return false;
}


// TODO Receive OnDeath.Broadcast() 

