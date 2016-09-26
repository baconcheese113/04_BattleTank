// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const{
	return Cast<ATank>(GetPawn());
}


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("No Tank identified"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s set up at %s"), *PlayerTank->GetName(), *PlayerTank->GetActorLocation().ToCompactString());
	}
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (GetPlayerTank()) {
		// TODO Move turret towards player

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

