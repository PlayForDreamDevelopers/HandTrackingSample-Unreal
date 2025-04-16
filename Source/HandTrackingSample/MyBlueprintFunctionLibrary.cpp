// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "YvrXRInputFunctionLibrary.h"

void UMyBlueprintFunctionLibrary::GetBoneBeam(UPoseableMeshComponent* target, const FString& BoneName, FVector& BeamStart, FVector& BeamEnd)
{
	
		FTransform transform = target->GetBoneTransformByName(FName(BoneName), EBoneSpaces::Type::WorldSpace);
		const FTransform TransformByPose = UYvrXRInputFunctionLibrary::GetPointerPose(BoneName.StartsWith("L")?EYvrXRHandType::HandLeft:EYvrXRHandType::HandRight);
		BeamStart = transform.GetLocation();
		FVector Direction = TransformByPose.GetRotation().GetAxisX();
		Direction *= 1000;
		BeamEnd = BeamStart + Direction;
}

UHandGrabComponent* UMyBlueprintFunctionLibrary::GetGrabComponentNearHand(const UObject* WorldContextObject, const USceneComponent* component, float GrabRadiusFromGripPosition,bool IsLeftHand,bool enableRayCatching)
{
	float NearestComponentDistance = TNumericLimits< float >::Max();
	UHandGrabComponent* NearestGrabComponent = nullptr;
	const FVector HandLocation = component->K2_GetComponentLocation();
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody) };
	FHitResult Result;
	TArray<UHandGrabComponent*> Ret;
	// direct grab
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(WorldContextObject,
		HandLocation, HandLocation,
		GrabRadiusFromGripPosition, ObjectTypes, false, {}, EDrawDebugTrace::Type::None, Result, true)) {
		Result.GetActor()->GetComponents(Ret);
		if (Ret.Num()) {
			for (UHandGrabComponent* grabComponent : Ret) {
				const float Dist = UKismetMathLibrary::VSizeSquared(grabComponent->K2_GetComponentLocation() - HandLocation);
				if (Dist <= NearestComponentDistance) {
					NearestComponentDistance = Dist;
					NearestGrabComponent = grabComponent;
				}
			}
		}
	}
	// beam grab
	else if(enableRayCatching)
	{
		if(const auto PoseComponent= Cast<UPoseableMeshComponent>(component))
		{
			FVector BeamEnd;
			FVector BeamStart;
			GetBoneBeam(const_cast<UPoseableMeshComponent*>(PoseComponent),IsLeftHand?"L_INDEX_TIP":"R_INDEX_TIP",BeamStart,BeamEnd);
			if(UKismetSystemLibrary::SphereTraceSingleForObjects(WorldContextObject,BeamStart,BeamEnd,GrabRadiusFromGripPosition,ObjectTypes,false,{},EDrawDebugTrace::Type::None,Result,true))
			{
				Result.GetActor()->GetComponents(Ret);
				if (Ret.Num()) {
					for (UHandGrabComponent* GrabComponent : Ret) {
						if(GrabComponent->GrabType==EGrabType::Snap)
						{
							continue;
						}
						const float Dist = UKismetMathLibrary::VSizeSquared(GrabComponent->K2_GetComponentLocation() - HandLocation);
						if (Dist <= NearestComponentDistance) {
							NearestComponentDistance = Dist;
							NearestGrabComponent = GrabComponent;
						}
					}
				}
			}
		}
	}
	return NearestGrabComponent;
}