// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h" // put new includes above

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel; //Forward Declaration

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);


	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;
protected:

	// Needs to be protected because we're using it in a child blueprint class
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative is TSubTypeOf<blah>()

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000; //Sensible starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;

	FVector AimDirection = FVector::ZeroVector;

	double LastFireTime = 0;

	void MoveBarrelTowards();

	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();

};
