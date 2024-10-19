// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GTPReloadFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifyReloadFinishedSignature, USkeletalMeshComponent*);

UCLASS()
class GAME_THIRD_PERSON_API UGTPReloadFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
	public:
        virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

        FOnNotifyReloadFinishedSignature OnNotifyReloadFinisheds;
};
