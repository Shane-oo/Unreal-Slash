// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Hit.h"
#include "Enemy.generated.h"

class UAnimMontage;

UCLASS()
class SLASH_API AEnemy : public ACharacter, public IHit
{
    GENERATED_BODY()

public:
    AEnemy();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void GetHit(const FVector& ImpactPoint) override;

protected:
    virtual void BeginPlay() override;

private:
    double GetHitAngle(const FVector& ImpactPoint) const;

    // Animation Montages
    FName FromRightSection = FName("FromRight");
    FName FromLeftSection = FName("FromLeft");
    FName FromFrontSection = FName("FromFront");
    FName FromBackSection = FName("FromBack");

    UPROPERTY(EditDefaultsOnly, Category = "Montages")
    UAnimMontage* HitReactMontage;

    void PlayHitReactMontage(const float& Angle) const;

};
