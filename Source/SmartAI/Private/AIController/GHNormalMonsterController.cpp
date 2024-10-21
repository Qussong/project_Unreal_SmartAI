// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/GHNormalMonsterController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AISenseConfig_Sight.h"

AGHNormalMonsterController::AGHNormalMonsterController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/_SmartAI/Monster/Zombie/AI/BT_NormalMonster.BT_NormalMonster'"));
	if (BTAssetRef.Succeeded())
	{
		BTAsset = BTAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/_SmartAI/Monster/Zombie/AI/BB_NormalMonster.BB_NormalMonster'"));
	if (BBAssetRef.Succeeded())
	{
		BBAsset = BBAssetRef.Object;
	}
}

void AGHNormalMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AGHNormalMonsterController::OnUnPossess()
{
	Super::OnUnPossess();

}
