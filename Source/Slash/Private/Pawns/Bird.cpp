// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
// #region Constructors

ABird::ABird()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// #endregion

// #region Protected Methods

void ABird::BeginPlay()
{
    Super::BeginPlay();
}

// #endregion

// #region Public Methods

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABird::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// #endregion