// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Ghost.h"

AGhost::AGhost()
{
}

void AGhost::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();
}
