// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GTPDamageActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class GAME_THIRD_PERSON_API AGTPDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGTPDamageActor();
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USphereComponent *SphereComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UStaticMeshComponent *StaticMesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
  float Damage = 5.0f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
  float SphereRadius = 100.0f;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
