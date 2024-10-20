// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Ghost.h"

#include "AIController.h"
#include "PaperFlipbookComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Entity/PacManPlayer.h"

AGhost::AGhost()
{
	IsDead = false;
	IsFrightened = false;
}

void AGhost::SetAliveMode()
{
	// Alive = not dead & not frighten
	IsDead = false;
	IsFrightened = false;
	// Set back to base animation
	FlipbookComponent->SetFlipbook(BaseFlipbookRight);
	// Clear TimerHandler
	GetWorldTimerManager().ClearTimer(TimerHandle);
	UFloatingPawnMovement* FloatingMovement = Cast<UFloatingPawnMovement>(MovementComponent);
	FloatingMovement->MaxSpeed = 700.0f;
	// Debug message for test purpose
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SetAlive"));

	// Récupère l'AIController pour mettre à jour le Blackboard
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			// Mets à jour les clé 'IsFrightened' & 'IsDead' dans le Blackboard
			BlackboardComp->SetValueAsBool(TEXT("IsDead"), IsDead);
			BlackboardComp->SetValueAsBool(TEXT("IsFrightened"), IsFrightened);
		}
	} 
}

void AGhost::SetDeadMode()
{
	// Either dead or frighten not both
	IsDead = true;
	IsFrightened = false;
	// Set animation to dead
	FlipbookComponent->SetFlipbook(DeadFlipbookRight);
	// Clear timer so don't come back alive in middle of comming back to respawn
	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGhost::SetAliveMode, 7.0f, false);
	UFloatingPawnMovement* FloatingMovement = Cast<UFloatingPawnMovement>(MovementComponent);
	FloatingMovement->MaxSpeed = 1200.0f;
	

	// Récupère l'AIController pour mettre à jour le Blackboard
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			// Mets à jour la clé 'IsDead' dans le Blackboard
			BlackboardComp->SetValueAsBool(TEXT("IsDead"), IsDead);
			BlackboardComp->SetValueAsBool(TEXT("IsFrightened"), IsDead);
		}
		
	} 
}

void AGhost::SetFrightenMode()
{
	// Either frighten or dead not both
	IsFrightened = true;
	IsDead = false;
	// Set animation to frighten
	FlipbookComponent->SetFlipbook(FrightenFlipbook);
	// Set timer of 5s wich will call SetAliveMode()
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGhost::SetFinalFrightenAnimation, 7.0f, false);
	UFloatingPawnMovement* FloatingMovement = Cast<UFloatingPawnMovement>(MovementComponent);
	FloatingMovement->MaxSpeed = 600.0f;

	// Récupère l'AIController pour mettre à jour le Blackboard
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			// Mets à jour la clé 'IsFrightened' dans le Blackboard
			BlackboardComp->SetValueAsBool(TEXT("IsFrightened"), IsFrightened);
			BlackboardComp->SetValueAsBool(TEXT("IsDead"), IsDead);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SetIsFrighten"));
		}
	} 
}

void AGhost::SetFinalFrightenAnimation()
{
	FlipbookComponent->SetFlipbook(FrightenFlipbookFinal);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGhost::SetAliveMode, 3.0f, false);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SetFinalAnimation"));
}

void AGhost::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind function OnActorBeginOverlap with your class function OnOverlap
	this->OnActorBeginOverlap.AddDynamic(this, &AGhost::OnOverlap);
}

void AGhost::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto Pacman = Cast<APacManPlayer>(OtherActor))
	{
		if(IsFrightened)
		{
			SetDeadMode();
		}
		else if (!IsDead && !IsFrightened)
		{
			Pacman->LoseLife(); // need to add animation & respawn to middle
		}
	}
}
