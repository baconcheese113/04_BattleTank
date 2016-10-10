// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser));
	
	UE_LOG(LogTemp, Warning, TEXT("Damage:%i Health is:%i, ActualDamage is:%i, Health is:%i"), DamagePoints, CurrentHealth - DamagePoints, DamagePoints, CurrentHealth);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		//UE_LOG(LogTemp, Warning, TEXT("DEAD"));
	}
	
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}


// TODO OnDeath.Broadcast()


