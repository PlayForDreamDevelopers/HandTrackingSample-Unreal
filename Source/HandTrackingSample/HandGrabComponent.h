// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ActorComponent.h"
#include "HandGrabComponent.generated.h"

UENUM()
enum EGrabType
{
	None,
	Free,
	Snap,
	Custom
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HANDTRACKINGSAMPLE_API UHandGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHandGrabComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void TryGrab(USceneComponent* component);
	UFUNCTION(BlueprintCallable)
	bool TryRelease(USceneComponent* component);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isHeld;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGrabType> GrabType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSimulateOnDrop;
	void setPrimitiveCompPhysics(bool simulate);
	void attachParentToSceneComponent(USceneComponent* component);
	void setShouldSimulateOnDrop();
};
