
#include "Monster/GHMonsterBase.h"
#include "Perception/AISense_Damage.h"

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

float AGHMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// ������ ����


	// AI Perception Component �� Ʈ����
	UAISense_Damage::ReportDamageEvent(GetWorld(), 
									   this, 
									   DamageCauser, 
									   DamageAmount, 
									   DamageCauser->GetActorLocation(), 
									   GetActorLocation());

	return 0.0f;
}