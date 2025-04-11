// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/PoseableMeshComponent.h"
#include "HandGrabComponent.h"
#include "MyBlueprintFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()  
class HANDTRACKINGSAMPLE_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "HandTracking|Pawn")
	static void GetBoneBeam(UPoseableMeshComponent* target, const FString& BoneName, FVector& BeamStart, FVector& BeamEnd);
	UFUNCTION(BlueprintCallable, Category = "HandTracking|Pawn", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject"))
	static UHandGrabComponent* GetGrabComponentNearHand(const UObject* WorldContextObject, const USceneComponent* component, float GrabRadiusFromGripPosition,bool IsLeftHand,bool enableRayCatching=true);
};
