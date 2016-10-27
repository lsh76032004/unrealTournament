// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#include "UnrealTournament.h"
#include "UTLocalMessage.h"
#include "UTKillerMessage.h"

UUTKillerMessage::UUTKillerMessage(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Lifetime=3.0;
	bIsUnique = true;
	bCombineEmphasisText = true;
	MessageArea = FName(TEXT("Announcements"));
	MessageSlot = FName(TEXT("DeathMessage"));
	YouKilledPrefixText = NSLOCTEXT("UTKillerMessage","YouKilledPrefixText","You killed ");
	YouKilledPostfixText = NSLOCTEXT("UTKillerMessage", "YouKilledPostfixText", "");
	KillAssistedPrefixText = NSLOCTEXT("UTKillerMessage", "KillAssistedPrefixText", "Kill assist ");
	KillAssistedPostfixText = NSLOCTEXT("UTKillerMessage", "KillAssisted", "");
	SpecKilledText = NSLOCTEXT("UTKillerMessage", "SpecKilledText", "{Player1Name} killed {Player2Name}");
	bDrawAsDeathMessage = true;
	bDrawAtIntermission = false;
	FontSizeIndex = 1;
}

FLinearColor UUTKillerMessage::GetMessageColor_Implementation(int32 MessageIndex) const
{
	return FLinearColor::White;
}

void UUTKillerMessage::GetEmphasisText(FText& PrefixText, FText& EmphasisText, FText& PostfixText, FLinearColor& EmphasisColor, int32 Switch, class APlayerState* RelatedPlayerState_1, class APlayerState* RelatedPlayerState_2, class UObject* OptionalObject) const
{
	PrefixText = (Switch == 2) ? KillAssistedPrefixText : YouKilledPrefixText;
	PostfixText = (Switch == 2) ? KillAssistedPostfixText : YouKilledPostfixText;
	EmphasisText = RelatedPlayerState_2 ? FText::FromString(RelatedPlayerState_2->PlayerName) : FText::GetEmpty();
	AUTPlayerState* VictimPS = Cast<AUTPlayerState>(RelatedPlayerState_2);
	EmphasisColor = (VictimPS && VictimPS->Team) ? VictimPS->Team->TeamColor : FLinearColor::Red;
}

FText UUTKillerMessage::GetText(int32 Switch,bool bTargetsPlayerState1,class APlayerState* RelatedPlayerState_1,class APlayerState* RelatedPlayerState_2,class UObject* OptionalObject) const
{
	if (Switch == -99)
	{
		return GetDefault<UUTKillerMessage>(GetClass())->SpecKilledText;
	}
	return BuildEmphasisText(Switch, RelatedPlayerState_1, RelatedPlayerState_2, OptionalObject);
}
