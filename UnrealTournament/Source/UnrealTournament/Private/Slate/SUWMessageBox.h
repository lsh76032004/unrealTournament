// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "SlateBasics.h"
#include "SUWDialog.h"

#if !UE_SERVER

class SUWMessageBox : public SUWDialog
{
	SLATE_BEGIN_ARGS(SUWMessageBox)
	: _DialogSize(FVector2D(400,200))
	, _bDialogSizeIsRelative(false)
	, _DialogPosition(FVector2D(0.5f,0.5f))
	, _DialogAnchorPoint(FVector2D(0.5f,0.5f))
	, _ContentPadding(FVector2D(10.0f, 5.0f))
	, _ButtonMask(UTDIALOG_BUTTON_OK)
	, _MessageTextStyleName(TEXT("UWindows.Standard.Dialog.TextStyle"))
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class UUTLocalPlayer>, PlayerOwner)			
	SLATE_ARGUMENT(FText, DialogTitle)											
	SLATE_ARGUMENT(FVector2D, DialogSize)										
	SLATE_ARGUMENT(bool, bDialogSizeIsRelative)									
	SLATE_ARGUMENT(FVector2D, DialogPosition)									
	SLATE_ARGUMENT(FVector2D, DialogAnchorPoint)								
	SLATE_ARGUMENT(FVector2D, ContentPadding)									
	SLATE_ARGUMENT(uint16, ButtonMask)											
	SLATE_EVENT(FDialogResultDelegate, OnDialogResult)							

	SLATE_ARGUMENT(FText, MessageText)
	SLATE_ARGUMENT(FString, MessageTextStyleName)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);
};

#endif