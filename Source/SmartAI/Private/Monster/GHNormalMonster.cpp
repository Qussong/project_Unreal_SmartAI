
#include "Monster/GHNormalMonster.h"
#include "Components/CapsuleComponent.h"
#include "AIController/GHNormalMonsterController.h"

AGHNormalMonster::AGHNormalMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/_SmartAI/Monster/Zombie/Mesh/SM_Zombie.SM_Zombie'"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimRef(TEXT("/Game/_SmartAI/Monster/Zombie/ABP_Zombie.ABP_Zombie_C"));
	if (AnimRef.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimRef.Class);
	}
	GetCapsuleComponent()->SetCapsuleSize(25.f, 90.f);

	// AI Controller
	AIControllerClass = AGHNormalMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void AGHNormalMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AGHNormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AGHNormalMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}
