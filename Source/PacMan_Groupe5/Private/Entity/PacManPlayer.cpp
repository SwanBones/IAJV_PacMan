// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/PacManPlayer.h"

#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

// Sets default values
APacManPlayer::APacManPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialisez les différents Flipbooks pour les directions de déplacement
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookUpAsset(TEXT("/Game/Assets/Pacman/FB_Pacman_Up.FB_Pacman_Up"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookDownAsset(TEXT("/Game/Assets/Pacman/FB_Pacman_Down.FB_Pacman_Down"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookLeftAsset(TEXT("/Game/Assets/Pacman/FB_Pacman_Left.FB_Pacman_Left"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRightAsset(TEXT("/Game/Assets/Pacman/FB_Pacman_Right.FB_Pacman_Right"));
	
	if (FlipbookUpAsset.Succeeded()) FlipbookUp = FlipbookUpAsset.Object;
	if (FlipbookDownAsset.Succeeded()) FlipbookDown = FlipbookDownAsset.Object;
	if (FlipbookLeftAsset.Succeeded()) FlipbookLeft = FlipbookLeftAsset.Object;
	if (FlipbookRightAsset.Succeeded()) FlipbookRight = FlipbookRightAsset.Object;
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
	if (value > 0.0f)  // Vers la haut
	{
		// Assigner un Flipbook spécifique pour l'animation du mouvement vers le haut
		FlipbookComponent->SetFlipbook(FlipbookUp);
	}
	else if (value < 0.0f)  // Vers la bas
	{
		// Assigner un Flipbook spécifique pour l'animation du mouvement vers la bas
		FlipbookComponent->SetFlipbook(FlipbookDown);
	}
	
	FVector Direction = FVector(1.0f, 0.0f, 0.0f);
	AddMovementInput(Direction, value);
}

void APacManPlayer::MoveLeftRight(float value)
{
	if (value > 0.0f)  // Vers la droite
	{
		// Assigner un Flipbook spécifique pour l'animation du mouvement vers la droite
		FlipbookComponent->SetFlipbook(FlipbookRight);
	}
	else if (value < 0.0f)  // Vers la gauche
	{
		// Assigner un Flipbook spécifique pour l'animation du mouvement vers la gauche
		FlipbookComponent->SetFlipbook(FlipbookLeft);
	}
	
	FVector Direction = FVector(0.0f, 1.0f, 0.0f);
	AddMovementInput(Direction, value);
}

