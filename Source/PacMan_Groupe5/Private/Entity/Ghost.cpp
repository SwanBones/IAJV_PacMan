// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Ghost.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

AGhost::AGhost()
{
	IsDead = false;
	IsFrightened = false;
}

void AGhost::SetAliveMode()
{
	IsDead = false;
	IsFrightened = false;

	// Récupère l'AIController pour mettre à jour le Blackboard
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			// Mets à jour la clé 'IsFrightened' dans le Blackboard
			BlackboardComp->SetValueAsBool(TEXT("IsDead"), IsDead);
			BlackboardComp->SetValueAsBool(TEXT("IsFrightened"), IsFrightened);
		}
	} 
}

void AGhost::SetDeadMode()
{
	IsDead = true;

	// Récupère l'AIController pour mettre à jour le Blackboard
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			// Mets à jour la clé 'IsFrightened' dans le Blackboard
			BlackboardComp->SetValueAsBool(TEXT("IsDead"), IsDead);
		}
	} 
}

void AGhost::SetFrightenMode()
{
	IsFrightened = true;

	// Récupère l'AIController pour mettre à jour le Blackboard
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			// Mets à jour la clé 'IsFrightened' dans le Blackboard
			BlackboardComp->SetValueAsBool(TEXT("IsFrightened"), IsFrightened);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SetIsFrighten"));
		}
	} 
}

void AGhost::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();
	SetFrightenMode();
}
