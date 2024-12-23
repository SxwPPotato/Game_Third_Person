// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_THIRD_PERSON_API ULMAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULMAHealthComponent();

  UFUNCTION(BlueprintCallable)
  float GetHealth() const { return Health; }

  UFUNCTION(BlueprintCallable)
  bool IsDead() const;

  bool AddHealth(float NewHealth);
  bool IsHealthFull() const;

  UPROPERTY(BlueprintAssignable)
  FOnDeath OnDeath;

  FOnHealthChanged OnHealthChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.0f;



	

private:
        float Health = 0.0f;

        UFUNCTION()
        void OnTakeAnyDamage(AActor *DamagedActor, float Damage,
                             const class UDamageType *DamageType,
                             class AController *InstigatedBy,
                             AActor *DamageCauser);
};


// DECLARE_MULTICAST_DELEGATE(FOnDeath)