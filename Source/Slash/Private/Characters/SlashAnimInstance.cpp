// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashAnimInstance.h"
#include "Characters//SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// #region Public Methods

void USlashAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
    if (SlashCharacter)
    {
        SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
    }
}

void USlashAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (SlashCharacterMovement)
    {
        IsFalling = SlashCharacterMovement->IsFalling();
        GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
        CharacterState = SlashCharacter->GetCharacterState();
    }
}

// #endregion
