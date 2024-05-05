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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sin Pararameters")
    float Amplitude = 0.25f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sin Pararameters")
    float TimeConstant = 0.5f;

    UFUNCTION(BlueprintPure)
    float TransformSin() const;

    UFUNCTION(BlueprintPure)
    float TransformCos() const;

    template <typename T>
    static T Avg(T First, T Second);

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float RunningTime = 0.f;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* ItemMesh;
};

template <typename T>
T AItem::Avg(T First, T Second)
{
    return (First + Second) / 2;
}
