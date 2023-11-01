// Copyright 2020-2023 Yvr Technology Co., Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IStereoLayers.h"
#include "XRSwapChain.h"

struct FYvrXRLayer
{
	IStereoLayers::FLayerDesc	Desc;
	FXRSwapChainPtr				Swapchain;
	FXRSwapChainPtr				LeftSwapchain;
	FVector2D					SwapchainSize;
	bool						bUpdateTexture;

	FYvrXRLayer(const IStereoLayers::FLayerDesc& InLayerDesc)
		: Desc(InLayerDesc)
		, Swapchain()
		, LeftSwapchain()
		, bUpdateTexture(false)
	{ }

	void SetLayerId(uint32 InId) { Desc.SetLayerId(InId); }
	uint32 GetLayerId() const { return Desc.GetLayerId(); }

	bool NeedReAllocateTexture();
	bool NeedReAllocateLeftTexture();

	FIntRect GetViewport() const;
	FVector2D GetQuadSize() const;
};

bool GetLayerDescMember(const FYvrXRLayer& Layer, IStereoLayers::FLayerDesc& OutLayerDesc);
void SetLayerDescMember(FYvrXRLayer& OutLayer, const IStereoLayers::FLayerDesc& InLayerDesc);
void MarkLayerTextureForUpdate(FYvrXRLayer& Layer);
