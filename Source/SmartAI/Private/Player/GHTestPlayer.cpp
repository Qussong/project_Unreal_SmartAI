// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GHTestPlayer.h"

AGHTestPlayer::AGHTestPlayer()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		BodyMeshRef(TEXT(""));
	if (BodyMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		HeadMeshRef(TEXT(""));
	if (HeadMeshRef.Succeeded())
	{
		HeadMesh->SetSkeletalMesh(BodyMeshRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		ClothMeshRef(TEXT(""));
	if (ClothMeshRef.Succeeded())
	{
		ClothMesh->SetSkeletalMesh(ClothMeshRef.Object);
	}

}
