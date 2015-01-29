// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 

/**
 *
 **/

#include "UTHUDWidget_WeaponInfo.generated.h"

UCLASS()
class UUTHUDWidget_WeaponInfo : public UUTHUDWidget
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Draw_Implementation(float DeltaTime);
	virtual void InitializeWidget(AUTHUD* Hud);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderObject")
	FHUDRenderObject_Texture BackgroundSlate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderObject")
	FHUDRenderObject_Texture BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderObject")
	FHUDRenderObject_Text AmmoText;

	UFUNCTION(BlueprintNativeEvent, Category = "RenderObject")
	FText GetAmmoAmount();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderObject")
	float AmmoFlashTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderObject")
	FLinearColor AmmoFlashColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderObject")
	FLinearColor WeaponChangeFlashColor;

private:
	float FlashTimer;
	int32 LastAmmoAmount;

	UPROPERTY()
	AUTWeapon* LastWeapon;
};
