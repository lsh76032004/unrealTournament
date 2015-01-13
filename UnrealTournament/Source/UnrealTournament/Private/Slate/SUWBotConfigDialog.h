// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "SlateBasics.h"
#include "STableRow.h"
#include "SUWDialog.h"

#if !UE_SERVER

/** version of STableRow that allows multi-select by single clicking without modifier keys */
template<typename ItemType>
class SSimpleMultiSelectTableRow : public STableRow<ItemType>
{
public:
	SLATE_BEGIN_ARGS(SSimpleMultiSelectTableRow<ItemType>)
	: _Style(&FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row"))
	, _Padding(FMargin(0))
	, _ShowSelection(true)
	, _Content()
	{}

	SLATE_STYLE_ARGUMENT(FTableRowStyle, Style)

	SLATE_EVENT(FOnDragDetected, OnDragDetected)
	SLATE_EVENT(FOnTableRowDragEnter, OnDragEnter)
	SLATE_EVENT(FOnTableRowDragLeave, OnDragLeave)
	SLATE_EVENT(FOnTableRowDrop, OnDrop)

	SLATE_ATTRIBUTE(FMargin, Padding)

	SLATE_ARGUMENT(bool, ShowSelection)

	SLATE_DEFAULT_SLOT(typename SSimpleMultiSelectTableRow<ItemType>::FArguments, Content)

	SLATE_END_ARGS()

	void Construct(const typename SSimpleMultiSelectTableRow<ItemType>::FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
	{
		STableRow<ItemType>::Construct( STableRow<ItemType>::FArguments()
			.Style(InArgs._Style).OnDragDetected(InArgs._OnDragDetected).OnDragEnter(InArgs._OnDragEnter).OnDragLeave(InArgs._OnDragLeave).OnDrop(InArgs._OnDrop).Padding(InArgs._Padding).ShowSelection(InArgs._ShowSelection).Content()[InArgs._Content.Widget],
			InOwnerTableView );
	}

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
	{
		TSharedPtr< ITypedTableView<ItemType> > OwnerWidget = OwnerTablePtr.Pin();
		if (OwnerWidget->Private_GetSelectionMode() != ESelectionMode::Multi)
		{
			return STableRow<ItemType>::OnMouseButtonDown(MyGeometry, MouseEvent);
		}
		else
		{
			ChangedSelectionOnMouseDown = false;

			checkSlow(OwnerWidget.IsValid());

			if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
			{
				const ItemType* MyItem = OwnerWidget->Private_ItemFromWidget(this);
				const bool bIsSelected = OwnerWidget->Private_IsItemSelected(*MyItem);

				check(MyItem != nullptr);

				if (MouseEvent.IsShiftDown())
				{
					OwnerWidget->Private_SelectRangeFromCurrentTo(*MyItem);
					ChangedSelectionOnMouseDown = true;
				}
				else
				{
					OwnerWidget->Private_SetItemSelection(*MyItem, !bIsSelected, true);
					ChangedSelectionOnMouseDown = true;
				}

				return FReply::Handled()
					.DetectDrag(SharedThis(this), EKeys::LeftMouseButton)
					.SetUserFocus(OwnerWidget->AsWidget(), EFocusCause::Mouse)
					.CaptureMouse(SharedThis(this));
			}
			else
			{
				return FReply::Unhandled();
			}
		}
	}
};

class SUWBotConfigDialog : public SUWDialog, public FGCObject
{
public:
	SLATE_BEGIN_ARGS(SUWBotConfigDialog)
	{}
	SLATE_ARGUMENT(TSubclassOf<AUTGameMode>, GameClass)
	SLATE_ARGUMENT(TWeakObjectPtr<UUTLocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(int32, NumBots) // number of bots that will be added to the game we're setting up
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObjects(WeaponList);
	}
protected:
	TSubclassOf<AUTGameMode> GameClass;
	int32 MaxSelectedBots;
	/** index in UTGameMode's array of bot currently being customized */
	int32 CurrentlyEditedIndex;
	TArray< TSharedPtr< FString > > BotNames;
	TArray<UClass*> WeaponList;
	TSharedPtr< SListView< TSharedPtr<FString> > > BotIncludeList;
	TSharedPtr< SComboBox< TSharedPtr<FString> > > BotToConfigure;
	TSharedPtr<STextBlock> CustomizedBotName;

	TSharedPtr<SSlider> SkillModifier;
	TSharedPtr<SSlider> Aggressiveness;
	TSharedPtr<SSlider> Tactics;
	TSharedPtr<SSlider> Jumpiness;
	TSharedPtr<SSlider> MovementAbility;
	TSharedPtr<SSlider> ReactionTime;
	TSharedPtr<SSlider> Accuracy;
	TSharedPtr<SSlider> Alertness;
	TSharedPtr<SSlider> MapAwareness;
	TSharedPtr< SComboBox<UClass*> > FavoriteWeapon;
	TSharedPtr<STextBlock> SelectedFavWeapon;

	void SaveCustomizedBot();

	SVerticalBox::FSlot& CreateBotSlider(const FText& Desc, TSharedPtr<SSlider>& Slider);
	TSharedRef<ITableRow> GenerateBotListRow(TSharedPtr<FString> BotName, const TSharedRef<STableViewBase>& OwningList);
	TSharedRef<SWidget> GenerateBotNameWidget(TSharedPtr<FString> BotName);
	TSharedRef<SWidget> GenerateWeaponListWidget(UClass* WeaponClass);
	void OnFavoriteWeaponChange(UClass* WeaponClass, ESelectInfo::Type SelectInfo);
	void OnCustomizedBotChange(TSharedPtr<FString> BotName, ESelectInfo::Type SelectInfo);
	void BotListClick(TSharedPtr<FString> BotName);
	void NewBotNameResult(TSharedPtr<SCompoundWidget> Dialog, uint16 ButtonPressed);
	FReply NewBotClick();
	FReply DeleteBotClick();
	FReply OKClick();

	inline float ConvertToSliderValue(float SavedValue) const
	{
		return (SavedValue + 1.0f) * 0.5f;
	}
	inline float ConvertFromSliderValue(float SliderValue) const
	{
		return (SliderValue * 2.0f) - 1.0f;
	}
};

#endif