/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassEntityConfigAsset.h"
#include "MEDeveloperSettings.generated.h"

/*
 *	Currently is being used for providing mass entity config asset for MESubsystem
 */

UCLASS(Config= "Game", DefaultConfig, ClassGroup= "Mass Extender", meta=(DisplayName= "Mass Extender Setting"))
class MASSEXTENDER_API UMEDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category= "ME|Assets")
	TMap<FName, TSoftObjectPtr<UMassEntityConfigAsset>> MassEntityConfigAssets;
};
