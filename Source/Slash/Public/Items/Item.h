// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SLASH_API AItem : public AActor
{
    GENERATED_BODY()

public:
    AItem();
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    float RunningTime = 0.f;

    UPROPERTY(EditAnywhere) // Blueprints
    float Amplitude = 0.25f;

    UPROPERTY(EditAnywhere) // Instances
    float TimeConstant = 0.5f;
};
