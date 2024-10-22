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

    AActor* Instigator = MeshComp->GetOwner();              // �Ҹ��� �߽��� (�÷��̾�)
    FVector NoiseLocation = Instigator->GetActorLocation(); // �Ҹ��� ��ġ (�÷��̾� ��ġ)
    float Loudness = 1.f;
    UWorld* World = GEngine->GetWorldFromContextObject(Instigator, EGetWorldErrorMode::LogAndReturnNull);

    // �Ҹ� �̺�Ʈ ����
    UAISense_Hearing::ReportNoiseEvent(
        World,          // ���� ����
        NoiseLocation,  // �Ҹ� ��ġ
        Loudness,       // �Ҹ� ũ��
        Instigator,     // �߽���
        1000.0f         // �ִ� ���� ����
    );

    // �Ҹ� ���
    UGameplayStatics::PlaySoundAtLocation(
        World,          // ���� ����
        Sound,          // ����� �Ҹ�
        NoiseLocation,  // �Ҹ� ��ġ
        1.0f,           // ����
        1.0f            // ��ġ
    );

}
