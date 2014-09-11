// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Slate.h"
#include "Slate/SlateGameResources.h"

class SUWindowsDesktop : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SUWindowsDesktop)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<UUTLocalPlayer>, PlayerOwner)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	/**
	 *	Will be called from the Local Player when the menu has been opened
	 **/
	virtual void OnMenuOpened();
	virtual void OnMenuClosed();
	virtual void CloseMenus();

	virtual FReply OnMenuConsoleCommand(FString Command, TSharedPtr<SComboButton> MenuButton);
	virtual void ConsoleCommand(FString Command);

protected:
	TWeakObjectPtr<class UUTLocalPlayer> PlayerOwner;
	TSharedPtr<class SWidget> GameViewportWidget;

	virtual void CreateDesktop();

	virtual bool SupportsKeyboardFocus() const override;
	virtual FReply OnKeyboardFocusReceived( const FGeometry& MyGeometry, const FKeyboardFocusEvent& InKeyboardFocusEvent ) override;
	virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyboardEvent& InKeyboardEvent ) override;
	virtual FReply OnKeyUp( const FGeometry& MyGeometry, const FKeyboardEvent& InKeyboardEvent ) override;

	virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
};

