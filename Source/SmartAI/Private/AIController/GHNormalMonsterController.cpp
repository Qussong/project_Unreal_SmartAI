// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/GHNormalMonsterController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"

#include "Perception/AIPerceptionSystem.h"

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
	
	// Sight Config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.f;
	SightConfig->PeripheralVisionAngleDegrees = 45.f;
	SightConfig->DetectionByAffiliation = FAISenseAffiliationFilter(1, 1, 1);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 300.f;
	SightConfig->PointOfViewBackwardOffset = 50.f;
	SightConfig->NearClippingRadius = 50.f;

	// Hearing Config
	 HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	 HearingConfig->HearingRange = 1500.f;
	 HearingConfig->LoSHearingRange = HearingConfig->HearingRange + 500.f;
	 HearingConfig->bUseLoSHearing = false;
	 HearingConfig->DetectionByAffiliation = FAISenseAffiliationFilter(1, 1, 1);

	// AI Perception
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->ConfigureSense(*HearingConfig);
	AIPerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());	// Prioritize Sight

}

void AGHNormalMonsterController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AIPerceptionComp))
	{
		AIPerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AGHNormalMonsterController::OnPerceptionUpdated);
		AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AGHNormalMonsterController::OnActorPerceptionUpdated);
		AIPerceptionComp->OnTargetPerceptionForgotten.AddDynamic(this, &AGHNormalMonsterController::OnActorPerceptionForgetUpdated);
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

void AGHNormalMonsterController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		//UE_LOG(LogTemp, Warning, TEXT("OnPerceptionUpdated"));
	}
}

void AGHNormalMonsterController::OnActorPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	FActorPerceptionBlueprintInfo Info;
	AIPerceptionComp->GetActorsPerception(Actor, Info);

	UObject* WorldContextObject = GetWorld();
	for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
	{
		TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(WorldContextObject, Stimulus);

		if (UAISense_Sight::StaticClass() == SenseClass)
		{
			ProcessSight(Actor, Stimulus);
		}
		else if (UAISense_Hearing::StaticClass() == SenseClass)
		{
			ProcessHearing(Actor, Stimulus);
		}
	}
}

void AGHNormalMonsterController::OnActorPerceptionForgetUpdated(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("OnActorPerceptionForgetUpdated"));
}

void AGHNormalMonsterController::ProcessSight(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("Sight detected!"));
}

void AGHNormalMonsterController::ProcessHearing(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("Hearing  detected!"));
}
