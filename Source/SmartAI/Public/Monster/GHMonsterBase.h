
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GHMonsterBase.generated.h"

UCLASS()
class SMARTAI_API AGHMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGHMonsterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
