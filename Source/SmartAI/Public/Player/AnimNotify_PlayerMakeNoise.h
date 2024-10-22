// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PlayerMakeNoise.generated.h"

class USoundBase;

/**
 * 
 */
UCLASS()
class SMARTAI_API UAnimNotify_PlayerMakeNoise : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_PlayerMakeNoise();
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> Sound;
};
