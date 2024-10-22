// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AnimNotify_PlayerMakeNoise.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"

#include "Sound/SoundBase.h"

UAnimNotify_PlayerMakeNoise::UAnimNotify_PlayerMakeNoise()
{
}

void UAnimNotify_PlayerMakeNoise::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

    AActor* Instigator = MeshComp->GetOwner();              // 소리의 발신자 (플레이어)
    FVector NoiseLocation = Instigator->GetActorLocation(); // 소리의 위치 (플레이어 위치)
    float Loudness = 1.f;
    UWorld* World = GEngine->GetWorldFromContextObject(Instigator, EGetWorldErrorMode::LogAndReturnNull);

    // 소리 이벤트 보고
    UAISense_Hearing::ReportNoiseEvent(
        World,          // 월드 참조
        NoiseLocation,  // 소리 위치
        Loudness,       // 소리 크기
        Instigator,     // 발신자
        1000.0f         // 최대 감지 범위
    );

    // 소리 재생
    UGameplayStatics::PlaySoundAtLocation(
        World,          // 월드 참조
        Sound,          // 재생할 소리
        NoiseLocation,  // 소리 위치
        1.0f,           // 볼륨
        1.0f            // 피치
    );

}
