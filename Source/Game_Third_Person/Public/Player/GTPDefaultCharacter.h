// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/GTPPlayerController.h"
#include "GTPDefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;
class UCharacterMovementComponent;
class UGTPWeaponComponent;
class AGTPPlayerController;

UCLASS()
class GAME_THIRD_PERSON_API AGTPDefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGTPDefaultCharacter();
	UFUNCTION()
    ULMAHealthComponent *GetHealthComponent() const {
        return HealthComponent;
    }  

protected:

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent *SpringArmComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent *CameraComponent;

  UPROPERTY()
  UDecalComponent *CurrentCursor = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
  UMaterialInterface *CursorMaterial = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
  FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
  ULMAHealthComponent *HealthComponent;

  UPROPERTY(EditDefaultsOnly, Category = "Animation")
  UAnimMontage *DeathMontage;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UGTPWeaponComponent *WeaponComponent;


  virtual void BeginPlay() override;


public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void SprintStart();
    void SprintStop();
    UFUNCTION(BlueprintCallable)
    void OnDeath();

private:

    float YRotation = -75.0f;
	float ArmLength = 1400.0f;
    float FOV = 55.0f;
    float WalkSpeed = 600.0f;
    float SprintSpeed = 1000.0f;
    int Endurance = 100;
    bool SwitchSprint = false;

    UCharacterMovementComponent *comp = GetCharacterMovement();
    AGTPPlayerController* PlayerPossess;
	//void OnDeath();

	void RotationPlayerOnCursor();
    void OnHealthChanged(float NewHealth);
};