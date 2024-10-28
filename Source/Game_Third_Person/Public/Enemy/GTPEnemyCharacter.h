// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GTPEnemyCharacter.generated.h"

class ULMAHealthComponent;
class UBehaviorTree;

UCLASS()
class GAME_THIRD_PERSON_API AGTPEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGTPEnemyCharacter();

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
  UBehaviorTree *BehaviorTreeAsset;


protected:
	
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  ULMAHealthComponent *HealthComponent;

  virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
