// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "UTDmg_SniperHeadshot.generated.h"

UCLASS(CustomConstructor)
class UUTDmg_SniperHeadshot : public UUTDamageType
{
	GENERATED_UCLASS_BODY()

	TSubclassOf<ULocalMessage> MessageClass;

	UUTDmg_SniperHeadshot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	{
		static ConstructorHelpers::FObjectFinder<UClass> MessageContentClass(TEXT("Class'/Game/RestrictedAssets/Blueprints/HeadShotMessage.HeadShotMessage_C'"));

		MessageClass = MessageContentClass.Object;

		GibHealthThreshold = -10000000;
		GibDamageThreshold = 1000000;
	}

	virtual void ScoreKill_Implementation(AUTPlayerState* KillerState, AUTPlayerState* VictimState, APawn* KilledPawn) const
	{
		AUTPlayerController* PC = Cast<AUTPlayerController>(KillerState->GetOwner());
		if (PC != NULL)
		{
			PC->ClientReceiveLocalizedMessage(MessageClass);
		}
	}

	virtual void PlayDeathEffects_Implementation(AUTCharacter* DyingPawn) const override
	{
		DyingPawn->SpawnGib(DyingPawn->HeadBone);
		DyingPawn->SetHeadScale(0.0f);
	}
};