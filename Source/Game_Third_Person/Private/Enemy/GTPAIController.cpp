// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Enemy/GTPAIController.h"
#include "Enemy/GTPEnemyCharacter.h"

void AGTPAIController::OnPossess(APawn *InPawn) {
  Super::OnPossess(InPawn);
  const auto AICharacter = Cast<AGTPEnemyCharacter>(InPawn);
  if (AICharacter) {
    RunBehaviorTree(AICharacter->BehaviorTreeAsset);
  }
}
