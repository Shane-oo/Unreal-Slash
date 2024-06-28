// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"

#include "Components/CapsuleComponent.h"

// #region Protected Methods

void AEnemy::BeginPlay()
{
    Super::BeginPlay();
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

// #region Public Methods

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEnemy::GetHit()
{
    
}


// #endregion
