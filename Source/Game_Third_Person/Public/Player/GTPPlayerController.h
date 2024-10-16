// Game_Third_Person Game by Netologiya. All RightsReserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GTPPlayerController.generated.h"

UCLASS()
class GAME_THIRD_PERSON_API AGTPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
 // AGTPPlayerController();

protected:
  virtual void BeginPlay() override;
  virtual void BeginSpectatingState() override;
};
