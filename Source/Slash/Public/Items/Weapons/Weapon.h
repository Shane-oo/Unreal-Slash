// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;

UCLASS()
class SLASH_API AWeapon : public AItem
{
    GENERATED_BODY()

public:
    AWeapon();

    void Equip(USceneComponent* InParentComponent, FName SocketName);

    void AttachMeshToSocket(USceneComponent* InParentComponent, FName SocketName) const;

    void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

protected:
    virtual void BeginPlay() override;

    virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult) override;

    virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

    UFUNCTION()
    void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                      const FHitResult& SweepResult);

private:
    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    USoundBase* EquipSound;

    UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
    UBoxComponent* WeaponBox;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* BoxTraceStart;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* BoxTraceEnd;

    UPROPERTY()
    TArray<AActor*> ActorsToIgnore;
};
