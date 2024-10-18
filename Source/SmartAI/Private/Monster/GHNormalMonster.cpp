
#include "Monster/GHNormalMonster.h"

AGHNormalMonster::AGHNormalMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshRef(TEXT(""));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimRef(TEXT(""));
	if (AnimRef.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimRef.Class);
	}

}

void AGHNormalMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AGHNormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
