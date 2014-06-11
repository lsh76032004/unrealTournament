// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UnrealTournament.h"
#include "UTGameMode.h"
#include "UTPlayerState.h"
#include "Net/UnrealNetwork.h"

AUTPlayerState::AUTPlayerState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bWaitingPlayer = false;
	bReadyToPlay = false;
	LastKillTime = 0.0f;
	int32 Kills = 0;
	bOutOfLives = false;
	int32 Deaths = 0;

	// We want to be ticked.
	PrimaryActorTick.bCanEverTick = true;

}


void AUTPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUTPlayerState, bWaitingPlayer);
	DOREPLIFETIME(AUTPlayerState, bReadyToPlay);
	DOREPLIFETIME(AUTPlayerState, bOutOfLives);
	DOREPLIFETIME(AUTPlayerState, Kills);
	DOREPLIFETIME(AUTPlayerState, Deaths);

}



void AUTPlayerState::SetWaitingPlayer(bool B)
{
	bIsSpectator = B;
	bWaitingPlayer = B;
	ForceNetUpdate();
}

void AUTPlayerState::IncrementKills(bool bEnemyKill )
{
	if ( bEnemyKill )
	{
		LastKillTime = GetWorld()->TimeSeconds;
		Kills++;
	}
}

void AUTPlayerState::IncrementDeaths()
{
	Deaths += 1;
	UE_LOG(UT,Log, TEXT("Increment Deaths"));

	SetNetUpdateTime(FMath::Min(NetUpdateTime, GetWorld()->TimeSeconds + 0.3f * FMath::FRand()));

	if (Role == ROLE_Authority)
	{
		// Trigger it locally
		OnDeathsReceived();
	}

}

void AUTPlayerState::AdjustScore(int ScoreAdjustment)
{
	Score += ScoreAdjustment;
	ForceNetUpdate();
}

void AUTPlayerState::OnDeathsReceived()
{
	UE_LOG(UT,Log, TEXT("OnDeathsReceived %s"), *GetNameSafe(GetWorld()->GetGameState<AUTGameState>()));
	AUTGameState* UTGameState = GetWorld()->GetGameState<AUTGameState>();
	if (UTGameState != NULL)
	{
		RespawnTime = UTGameState->RespawnWaitTime;
	}
}

void AUTPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If we are waiting to respawn then count down
	if (RespawnTime > 0.0f)
	{
		RespawnTime -= DeltaTime;
	}
}