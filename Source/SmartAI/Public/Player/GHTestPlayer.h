// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/GHPlayerBase.h"
#include "GHTestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API AGHTestPlayer : public AGHPlayerBase
{
	GENERATED_BODY()
	
public:
	AGHTestPlayer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	TObjectPtr<USkeletalMeshComponent> HeadMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> ClothMesh;
	
};
