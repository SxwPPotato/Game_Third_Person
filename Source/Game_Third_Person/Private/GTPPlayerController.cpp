// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Player/GTPPlayerController.h"

/*AGTPPlayerController::AGTPPlayerController() 
{
}*/

void AGTPPlayerController::BeginPlay() {
  Super::BeginPlay();

  SetInputMode(FInputModeGameOnly());
  bShowMouseCursor = false;
}