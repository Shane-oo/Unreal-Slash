// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemState.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;

UCLASS()
class SLASH_API AItem : public AActor
{
    GENERATED_BODY()

public:
    AItem();
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    EItemState ItemState = EItemState::EIS_Hovering;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trig Pararameters")
    float Amplitude = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trig Pararameters")
    float TimeConstant = 0.5f;

    UFUNCTION(BlueprintPure)
    float TransformSin() const;

    UFUNCTION(BlueprintPure)
    float TransformCos() const;

    template <typename T>
    static T Avg(T First, T Second);

    UFUNCTION()
    virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* ItemMesh;

    UPROPERTY(VisibleAnywhere)
    USphereComponent* SphereComponent;

private:
    void Hover(float DeltaTime);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float RunningTime = 0.f;
};

template <typename T>
T AItem::Avg(T First, T Second)
{
    return (First + Second) / 2;
}
