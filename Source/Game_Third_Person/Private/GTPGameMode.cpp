// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "GTPGameMode.h"
#include "Player/GTPDefaultCharacter.h"
#include "Player/GTPPlayerController.h"

AGTPGameMode::AGTPGameMode(){
  DefaultPawnClass = AGTPDefaultCharacter::StaticClass();
  PlayerControllerClass = AGTPPlayerController::StaticClass();

}