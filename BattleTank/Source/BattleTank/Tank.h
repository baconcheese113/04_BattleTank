// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "GameFramework/Pawn.h"
#include "TankBarrel.h"
#include "Tank.generated.h"

class UTankTurret;
//class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();
	 
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative is TSubTypeOf<blah>()

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;

	// TODO Remove once stable
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000; //Sensible starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	double ReloadTime = 4;
};
