// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/GHNormalMonsterController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionSystem.h"
#include "Player/GHPlayerBase.h"

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
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 0.f;// 300.f;
	SightConfig->PointOfViewBackwardOffset = 50.f;
	SightConfig->NearClippingRadius = 50.f;

	// Hearing Config
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 1500.f;
	HearingConfig->LoSHearingRange = HearingConfig->HearingRange + 500.f;
	HearingConfig->bUseLoSHearing = false;
	HearingConfig->DetectionByAffiliation = FAISenseAffiliationFilter(1, 1, 1);

	// Damage Config	
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));

	// AI Perception
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->ConfigureSense(*HearingConfig);
	AIPerceptionComp->ConfigureSense(*DamageConfig);
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

void AGHNormalMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsCheckedSight = StimulusState & static_cast<uint8>(EAIStimulusType::Sight);
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
		// Player Check
		AGHPlayerBase* Player = CastChecked<AGHPlayerBase>(Actor);
		if (!IsValid(Player)) return;

		// Stimulus 종류별로 작업
		FActorPerceptionBlueprintInfo Info;
		AIPerceptionComp->GetActorsPerception(Actor, Info);
		for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
		{
			TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);

			if (UAISense_Sight::StaticClass() == SenseClass)
			{
				ProcessSight(Actor, Stimulus);
			}
			else if (UAISense_Hearing::StaticClass() == SenseClass)
			{
				ProcessHearing(Actor, Stimulus);
			}
			else if (UAISense_Damage::StaticClass() == SenseClass)
			{
				ProcessDamage(Actor, Stimulus);
			}
		}
	}
}

void AGHNormalMonsterController::OnActorPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//

}

void AGHNormalMonsterController::OnActorPerceptionForgetUpdated(AActor* Actor)
{
	//
	UE_LOG(LogTemp, Warning, TEXT("ForgetUpdate"));
}

void AGHNormalMonsterController::ProcessSight(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && !bIsCheckedSight)
	{
		StimulusState |= static_cast<uint8>(EAIStimulusType::Sight);
		UE_LOG(LogTemp, Warning, TEXT("Sight Detected!"));
	}
	else if(Stimulus.WasSuccessfullySensed())
	{
		//
	}
	else
	{
		StimulusState &= ~static_cast<uint8>(EAIStimulusType::Sight);
		AIPerceptionComp->ForgetActor(Actor);
	}
}

void AGHNormalMonsterController::ProcessHearing(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && !bIsCheckedSight)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hearing Detected!"));
		// 위치값 받아와서 저장
		

		// 객체 잊기
		AIPerceptionComp->ForgetActor(Actor);

		// 해당 위치로 시야를 회전하고 이동

	}
}

void AGHNormalMonsterController::ProcessDamage(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && !bIsCheckedSight)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage Detected!"));
		// 위치값 받아와서 저장


		// 객체 잊기
		AIPerceptionComp->ForgetActor(Actor);

		// 해당 위치로 시야를 회전하고 이동

	}
}
