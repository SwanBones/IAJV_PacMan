// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/PacManPlayer.h"

// Sets default values
APacManPlayer::APacManPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APacManPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacManPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUpDown", this, &APacManPlayer::MoveUpDown);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &APacManPlayer::MoveLeftRight);
}

void APacManPlayer::MoveUpDown(float value)
{
	FVector Direction = FVector(1.0f, 0.0f, 0.0f);

	AddMovementInput(Direction, value);
}

void APacManPlayer::MoveLeftRight(float value)
{
	FVector Direction = FVector(0.0f, 1.0f, 0.0f);

	AddMovementInput(Direction, value);
}

