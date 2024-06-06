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

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASlashCharacter();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    [[nodiscard]] FName GetRightHandSocket() const;

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

private:
    FName RightHandSocket = FName("RightHandSocket");
    
    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;

    UPROPERTY(VisibleAnywhere, Category = "Hair")
    UGroomComponent* Hair;

    UPROPERTY(VisibleAnywhere, Category = "Hair")
    UGroomComponent* Eyebrows;
};
