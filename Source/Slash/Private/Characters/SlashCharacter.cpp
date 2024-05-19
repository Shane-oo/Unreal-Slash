// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"

// #region Private Methods

// #endregion

// #region Constructors

ASlashCharacter::ASlashCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// #endregion

// #region Protected Methods

void ASlashCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// #endregion

// #region Public Methods

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASlashCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// #endregion




