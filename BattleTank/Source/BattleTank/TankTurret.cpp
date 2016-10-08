// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	if (RawNewRotation > 180.f) { RawNewRotation = 180 - RawNewRotation; }
	//UE_LOG(TempLog, Warning, TEXT("Moving to %f"), RawNewElevation);
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}


