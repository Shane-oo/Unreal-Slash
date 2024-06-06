// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GroomComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"

// #region Private Methods

void ASlashCharacter::PlayAttackMontage() const
{
    if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance
        && AttackMontage)
    {
        AnimInstance->Montage_Play(AttackMontage);
        FName SectionName = FName();

        switch (FMath::RandRange(0, 1))
        {
        case 0:
            SectionName = Attack1;
            break;
        case 1:
            SectionName = Attack2;
            break;
        default:
            break;
        }
        AnimInstance->Montage_JumpToSection(SectionName);
    }
}

// #endregion

// #region Constructors

ASlashCharacter::ASlashCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
    // Rotate character with controls
    CharacterMovementComponent->bOrientRotationToMovement = true;
    CharacterMovementComponent->RotationRate = FRotator(0.f, 400.f, 0.0f);

    USceneComponent* Root = GetRootComponent();

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(Root);
    SpringArm->TargetArmLength = 300.f;

    ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
    ViewCamera->SetupAttachment(SpringArm);

    Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
    Hair->SetupAttachment(GetMesh());
    Hair->AttachmentName = FString("head");

    Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
    Eyebrows->SetupAttachment(GetMesh());
    Eyebrows->AttachmentName = FString("head");
}

// #endregion

// #region Protected Methods

void ASlashCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(SlashMappingContext, 0);
        }
    }
}

void ASlashCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.0f);

    // Forward/Backward
    const FVector NormalisedForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(NormalisedForwardDirection, MovementVector.Y);

    // Left/Right
    const FVector NormalisedRightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(NormalisedRightDirection, MovementVector.X);
}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

void ASlashCharacter::EKeyPressed(const FInputActionValue& Value)
{
    if (const AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem))
    {
        OverlappingWeapon->Equip(GetMesh(), RightHandSocket);
        CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
    }
}

void ASlashCharacter::Attack(const FInputActionValue& Value)
{
    if(ActionState == EActionState::EAS_UnOccupied)
    {
        ActionState = EActionState::EAS_Attacking;
        PlayAttackMontage();
    }
}

// #endregion

// #region Public Methods

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up actions
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed);
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);
    }
}

void ASlashCharacter::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// #endregion
