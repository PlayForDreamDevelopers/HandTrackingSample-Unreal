// Copyright 2020-2023 Yvr Technology Co., Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "YvrBusinessBPLibrary.generated.h"

UCLASS()
class UYvrBusinessBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "YvrLibrary")
	static FString GetDeviceSn();
	UFUNCTION(BlueprintPure, Category = "YvrLibrary")
	static FString GetDeviceModel();
	UFUNCTION(BlueprintPure, Category = "YvrLibrary")
	static FString GetSoftwareVersion();
};
