// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "DrawDebugHelpers.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// #region Private Methods

double AEnemy::GetHitAngle(const FVector& ImpactPoint) const
{
    const FVector NormalizedForward = GetActorForwardVector();
    // Lower Impact Point to the Enemy's Actor Location Z
    const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
    const FVector NormalizedToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();

    const double CosTheta = FVector::DotProduct(NormalizedForward, NormalizedToHit);
    double Angle = FMath::RadiansToDegrees(FMath::Acos(CosTheta));

    // if CrossProduct points down, Theta should be Negative
    if (const FVector CrossProduct = FVector::CrossProduct(NormalizedForward, NormalizedToHit); CrossProduct.Z < 0)
    {
        Angle *= -1.f;
    }

    return Angle;
}

void AEnemy::PlayHitReactMontage(const float& Angle) const
{
    FName HitReactSection = FromBackSection;
    if (Angle >= -45.f && Angle < 45.f)
    {
        HitReactSection = FromFrontSection;
    }
    else if (Angle >= -135.f && Angle < -45.f)
    {
        HitReactSection = FromLeftSection;
    }
    else if (Angle >= 45.f && Angle < 135.f)
    {
        HitReactSection = FromRightSection;
    }

    if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance
        && HitReactMontage)
    {
        AnimInstance->Montage_Play(HitReactMontage);
        AnimInstance->Montage_JumpToSection(HitReactSection);
    }
}

// #endregion

// #region Constructors

AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    USkeletalMeshComponent* EnemyMesh = GetMesh();
    EnemyMesh->SetCollisionObjectType(ECC_WorldDynamic); // Mesh is not ignored by weapons 
    EnemyMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // Mesh can get hit by box trace
    EnemyMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

    EnemyMesh->SetGenerateOverlapEvents(true);

    UCapsuleComponent* EnemyCapsule = GetCapsuleComponent();
    EnemyCapsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

// #endregion

// #region Protected Methods

void AEnemy::BeginPlay()
{
    Super::BeginPlay();
}

// #endregion

// #region Public Methods

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void AEnemy::GetHit(const FVector& ImpactPoint)
{
    const double HitAngle = GetHitAngle(ImpactPoint);
    PlayHitReactMontage(HitAngle);

    if (HitSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);
    }
}

// #endregion
