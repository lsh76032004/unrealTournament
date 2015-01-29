// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#if !UE_SERVER
class SUWindowsStyle 
{
public:
	static void Initialize();
	static void Shutdown();
	static void Reload();
	
	static const ISlateStyle& Get();
	static FName GetStyleSetName();

private:
	static TSharedRef<class FSlateStyleSet> Create();
	static TSharedPtr<class FSlateStyleSet> UWindowsStyleInstance;
};
#endif
