// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector TossVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		TossVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		4.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		true
	);
	if (bHaveAimSolution) {
		auto AimDirection = TossVelocity.GetSafeNormal();
		//MoveBarrel();
		//UE_LOG(LogTemp, Warning, TEXT("%s suggested velocity is %s"), *GetOwner()->GetName(), *AimDirection.ToString());
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("No Solution found"));
	}
}

//MoveBarrel(FVector AimDirection)
	// if AimDirection is within +-.5, set barrelElevation
	// In tick, slowly move to barrelelevation

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	float Elevation = AimDirection.Z;
	auto AimAsRotator = AimDirection.Rotation();

	//auto BarrelRotation = Barrel->GetForwardVector().Rotation;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *BarrelRotation.ToString());

	Barrel->Elevate(5); // TODO remove magic number
}