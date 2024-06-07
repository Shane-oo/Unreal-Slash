// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionState.h"
#include "EquippedState.h"
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
class UAnimMontage;
class AWeapon;

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

    FORCEINLINE EEquippedState GetCharacterState() const { return EquippedState; }

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
    UInputAction* PickUpAction;
    void PickUp(const FInputActionValue& Value);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Action")
    UInputAction* AttackAction;
    void Attack(const FInputActionValue& Value);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Action")
    UInputAction* EquipAction;
    void Equip(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable)
    void AttackEnd();

    UFUNCTION(BlueprintCallable)
    void Disarm();

    UFUNCTION(BlueprintCallable)
    void Arm();

    UFUNCTION(BlueprintCallable)
    void FinishedEquipping();

private:
    bool CanAttack() const;

    bool CanDisarm() const;

    bool CanArm() const;

    FName RightHandSocket = FName("RightHandSocket");

    FName SpineSocket = FName("SpineSocket");

    EEquippedState EquippedState = EEquippedState::EES_UnEquipped;

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    EActionState ActionState = EActionState::EAS_UnOccupied;

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

    UPROPERTY(VisibleAnywhere, Category= "Weapon")
    AWeapon* EquippedWeapon;

    // Animation Montages
    FName Attack1Section = FName("Attack1");

    FName Attack2Section = FName("Attack2");

    UPROPERTY(EditDefaultsOnly, Category = "Montages")
    UAnimMontage* AttackMontage;

    void PlayAttackMontage() const;

    FName EquipSection = FName("Equip");

    FName UnEquipSection = FName("UnEquip");

    UPROPERTY(EditDefaultsOnly, Category = "Montages")
    UAnimMontage* EquipMontage;

    void PlayEquipMontage(FName SectionName);
};
