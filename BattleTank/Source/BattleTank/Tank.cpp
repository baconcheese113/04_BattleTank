// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Smolder = Cast<UParticleSystemComponent>(GetComponentByClass(UParticleSystemComponent::StaticClass())); //Make sure to set this ahead of time in BP
	if (Smolder) {
		UE_LOG(LogTemp, Warning, TEXT("Found Smolder"));
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);	
	float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UE_LOG(LogTemp, Warning, TEXT("SuperDamage:%f, DamagePoints:%i, CurrentHealth will be:%i, CurrentHealth was:%i"), SuperDamage, DamagePoints, CurrentHealth - DamagePoints, CurrentHealth);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		//UE_LOG(LogTemp, Warning, TEXT("DEAD"));
		OnDeath.Broadcast();
		//if(ensure(Smolder))
		//	Smolder->Activate();
	}
	
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}
