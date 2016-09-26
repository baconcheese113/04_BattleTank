// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

//AimTowardsCrosshair
	//Find Turret
	//Find 

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Owner is undefined"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("You got %s at %s"), *ControlledTank->GetName(), *ControlledTank->GetActorLocation().ToCompactString());
	}
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location is %s"), *HitLocation.ToString());
		// Tell tank to aim at point
		GetControlledTank()->AimAt(HitLocation);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Hit Location is undefined"));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {

	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);
	auto ScreenLocation = FVector2D(SizeX * CrossHairXLocation, SizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Screen position is %f %f"), SizeX * CrossHairXLocation, SizeY * CrossHairYLocation);
	FVector LookDirection;
	// "De-project the screen position of the crosshair to a world direction
	bool bHit = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT HitLocation, OUT LookDirection);

	if (bHit) {
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return bHit;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility)) {
		//UE_LOG(LogTemp, Warning, TEXT("Looking toward %s"), *HitResult.ImpactPoint.ToString());
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector::ZeroVector;
	return false;
}


