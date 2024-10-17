
#include "Monster/GHMonsterBase.h"

AGHMonsterBase::AGHMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGHMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGHMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGHMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

