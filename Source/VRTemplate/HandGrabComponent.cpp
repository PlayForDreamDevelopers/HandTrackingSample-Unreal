// Fill out your copyright notice in the Description page of Project Settings.

#include "HandGrabComponent.h"

#include "YvrXRHandComponent.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values for this component's properties
UHandGrabComponent::UHandGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHandGrabComponent::BeginPlay()
{
	Super::BeginPlay();
	setShouldSimulateOnDrop();
	if(UPrimitiveComponent* p=Cast<UPrimitiveComponent>(GetAttachParent()))
	{
		p->SetCollisionProfileName("PhysicsActor");
	}
	// ...
}


// Called every frame
void UHandGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHandGrabComponent::setPrimitiveCompPhysics(bool simulate)
{
	if (UPrimitiveComponent* p = Cast<UPrimitiveComponent>(GetAttachParent()))
	{
		p->SetSimulatePhysics(simulate);
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Cast attachparent to primitiveComponent failed");
	}
}

void UHandGrabComponent::attachParentToSceneComponent(USceneComponent* component)
{
	UKismetSystemLibrary::PrintString(GetWorld(),UKismetSystemLibrary::GetDisplayName(component));
	if(const auto HandComponent=Cast<UYvrXRHandComponent>(component))
	{
		UKismetSystemLibrary::PrintString(GetWorld(),"Trying to attach to hand");
		GetAttachParent()->AttachToComponent(HandComponent,FAttachmentTransformRules::KeepWorldTransform,"HandSocket");
		return;
	}
	bool ret=GetAttachParent()->K2_AttachToComponent(component,FName(),EAttachmentRule::KeepWorld,EAttachmentRule::KeepWorld,EAttachmentRule::KeepWorld,true);
	if (!ret)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "attach to parent failed");
	}
}

void UHandGrabComponent::setShouldSimulateOnDrop()
{
	if (UPrimitiveComponent* parent = Cast<UPrimitiveComponent>(GetAttachParent()))
	{
		if (parent->IsAnySimulatingPhysics())
		{
			bSimulateOnDrop = true;
		}
	}
}


void UHandGrabComponent::TryGrab(USceneComponent* component)
{
	switch (GrabType)
	{
	case Free:
		{
			setPrimitiveCompPhysics(false);
			attachParentToSceneComponent(component);
			isHeld = true;
			break;
		}
	case Snap:
		{
			setPrimitiveCompPhysics(false);
			attachParentToSceneComponent(component);
			isHeld = true;
			break;
		}
	case Custom:
		{
			isHeld = true;
			break;
		}
	default:
		{
			break;
		};
	}
}

bool UHandGrabComponent::TryRelease(USceneComponent* component)
{
	isHeld=true;
	switch (GrabType)
	{
	case Free:
	case Snap:
		{
			if (bSimulateOnDrop)
			{
				this->setPrimitiveCompPhysics(true);
				isHeld = false;
			}
			else
			{
				GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				isHeld = false;
			}
			break;
		}
	default:
		{
			isHeld = false;
			break;
		}
	}
	if (isHeld)
	{
		return false;
	}
	return true;
}
