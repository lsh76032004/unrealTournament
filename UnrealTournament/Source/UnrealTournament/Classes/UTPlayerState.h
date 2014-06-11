// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UTPlayerState.generated.h"

UCLASS()
class AUTPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

	/** Whether this player is waiting to enter match */
	UPROPERTY(replicated)
	uint32 bWaitingPlayer:1;

	/** Whether this player has confirmed ready to play */
	UPROPERTY(replicated)
	uint32 bReadyToPlay:1;

	UPROPERTY()
	float LastKillTime;

	/** Kills by this player.  Not replicated but calculated client-side */
	UPROPERTY(replicated)
	int32 Kills;

	/** Can't respawn once out of lives */
	UPROPERTY(replicated)
	uint32 bOutOfLives:1;

	/** How many times associated player has died */
	UPROPERTY(replicated, ReplicatedUsing=OnDeathsReceived)
	int32 Deaths;

	// How long until this player can repawn.  It's not directly replicated to the clients instead it's set
	// locally via OnDeathsReceived.  It will be set to the value of "GameState.RespawnWaitTime"

	UPROPERTY()
	float RespawnTime;

	UFUNCTION()
	void OnDeathsReceived();


	UFUNCTION()
	virtual void SetWaitingPlayer(bool B);
	virtual void IncrementKills(bool bEnemyKill);
	virtual void IncrementDeaths();
	virtual void AdjustScore(int ScoreAdjustment);

	virtual void Tick(float DeltaTime) OVERRIDE;
};



