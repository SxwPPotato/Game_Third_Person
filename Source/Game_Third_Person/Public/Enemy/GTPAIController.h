// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GTPAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_THIRD_PERSON_API AGTPAIController : public AAIController
{
	GENERATED_BODY()
protected:
  virtual void OnPossess(APawn *InPawn) override;
	
};
