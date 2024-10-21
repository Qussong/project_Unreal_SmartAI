// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController/GHAIControllerBase.h"
#include "GHNormalMonsterController.generated.h"

class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class SMARTAI_API AGHNormalMonsterController : public AGHAIControllerBase
{
	GENERATED_BODY()

public:
	AGHNormalMonsterController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBlackboardData> BBAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

};
