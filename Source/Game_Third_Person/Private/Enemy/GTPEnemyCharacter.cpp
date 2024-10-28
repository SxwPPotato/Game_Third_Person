// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Enemy/GTPEnemyCharacter.h"
#include "Components/LMAHealthComponent.h"

AGTPEnemyCharacter::AGTPEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
    HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
}

void AGTPEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGTPEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


