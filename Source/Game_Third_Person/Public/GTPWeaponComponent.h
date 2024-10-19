// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GTPWeaponComponent.generated.h"

class AGTPBaseWeapon;
class UAnimMontage;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_THIRD_PERSON_API UGTPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGTPWeaponComponent();

	void Fire();
    void StopFire();
    void Reload();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<AGTPBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    UAnimMontage *ReloadMontage;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

    UPROPERTY()
    AGTPBaseWeapon *Weapon = nullptr;
    bool weap;

    bool AnimReloading = false;

	void SpawnWeapon();
    void InitAnimNotify();

    void OnNotifyReloadFinished(USkeletalMeshComponent *SkeletalMesh);
    bool CanReload() const;
    
		
};
