// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UTDmgType_BlockedTelefrag.generated.h"

UCLASS(CustomConstructor)
class UUTDmgType_BlockedTelefrag : public UUTDamageType
{
	GENERATED_UCLASS_BODY()

	UUTDmgType_BlockedTelefrag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	{
		bCausedByWorld = true;
		ConsoleDeathMessage = NSLOCTEXT("UTDeathMessages", "DeathMessage_BlockedTelefrag", "{Player2Name} found out that Shieldbelts block telefrags the hard way.");
		MaleSuicideMessage = NSLOCTEXT("UTDeathMessages", "MaleSuicideMessage_BlockedTelefrag", "{Player2Name} found out that Shieldbelts block telefrags the hard way.");
		FemaleSuicideMessage = NSLOCTEXT("UTDeathMessages", "FemaleSuicideMessage_BlockedTelefrag", "{Player2Name} found out that Shieldbelts block telefrags the hard way.");
		GibHealthThreshold = 10000000;
	}
};