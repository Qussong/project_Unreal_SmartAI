#pragma once

#include "CoreMinimal.h"
#include "Monster/GHMonsterBase.h"
#include "GHNormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API AGHNormalMonster : public AGHMonsterBase
{
	GENERATED_BODY()
	
public:
	AGHNormalMonster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:

};
