// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController/GHAIControllerBase.h"
#include "GHNormalMonsterController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;
struct FAIStimulus;

UENUM()
enum class EAIStimulusType : uint8
{
	None	= 0,			// 0000
	Sight	= 1 << 0,		// 0001
	Sound	= 1 << 1,		// 0010
	Damage	= 1 << 2,		// 0100
	Other	= 1 << 3,		// 1000
};

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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

// BT, BB
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBlackboardData> BBAsset;

// AI Perception
private:
	uint8 bIsCheckedSight : 1;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	uint8 StimulusState = static_cast<uint8>(EAIStimulusType::None);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Damage> DamageConfig;


	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
	void OnActorPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void OnActorPerceptionForgetUpdated(AActor* Actor);

	UFUNCTION()
	void ProcessSight(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void ProcessHearing(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void ProcessDamage(AActor* Actor, FAIStimulus Stimulus);
};