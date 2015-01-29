// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Object.h"
#include "UnrealString.h"
#include "../Public/AudioDevice.h"
#include "UTAudioSettings.generated.h"

UENUM(BlueprintType)
namespace EUTSoundClass
{
	enum Type
	{
		Master UMETA(DisplayName = "Master"),
		Music UMETA(DisplayName = "Music"),
		SFX UMETA(DisplayName = "SFX"),
		Voice UMETA(DisplayName = "Voice"),
		// should always be last, used to size arrays
		MAX UMETA(Hidden)
	};
}

UCLASS()
class UUTAudioSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	virtual void SetSoundClassVolume(EUTSoundClass::Type SoundClass, float NewVolume);
protected:
	virtual void SetSoundClassVolumeByName(const FString& SoundClassName, float NewVolume);
};
