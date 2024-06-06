// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SlashCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class AItem;

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASlashCharacter();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    FORCEINLINE AItem* GetOverlappingItem() const { return OverlappingItem; };

    FORCEINLINE void SetOverlappingItem(AItem* Item) { this->OverlappingItem = Item; };

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* SlashMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
    UInputAction* MovementAction;
    void Move(const FInputActionValue& Value);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
    UInputAction* LookAction;
    void Look(const FInputActionValue& Value);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Action")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Action")
    UInputAction* EquipAction;
    void EKeyPressed(const FInputActionValue& Value);

private:
    FName RightHandSocket = FName("RightHandSocket");

    UPROPERTY(VisibleInstanceOnly)
    AItem* OverlappingItem;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;

    UPROPERTY(VisibleAnywhere, Category = "Hair")
    UGroomComponent* Hair;

    UPROPERTY(VisibleAnywhere, Category = "Hair")
    UGroomComponent* Eyebrows;
};
