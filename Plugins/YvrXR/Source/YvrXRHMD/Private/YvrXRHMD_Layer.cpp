// Copyright 2020-2023 Yvr Technology Co., Ltd. All Rights Reserved.

#include "YvrXRHMD_Layer.h"
#include "YvrXRCore.h"
#include "YvrXRPlatformRHI.h"

bool FYvrXRLayer::NeedReAllocateTexture()
{
	if (!Desc.Texture.IsValid())
	{
		return false;
	}

	FRHITexture2D* Texture = Desc.Texture->GetTexture2D();
	if (!Texture)
	{
		return false;
	}

	if (!Swapchain.IsValid())
	{
		return true;
	}

	return SwapchainSize != Texture->GetSizeXY();
}

bool FYvrXRLayer::NeedReAllocateLeftTexture()
{
	if (!Desc.LeftTexture.IsValid())
	{
		return false;
	}

	FRHITexture2D* Texture = Desc.LeftTexture->GetTexture2D();
	if (!Texture)
	{
		return false;
	}

	if (!Swapchain.IsValid())
	{
		return true;
	}

	return SwapchainSize != Texture->GetSizeXY();
}

FIntRect FYvrXRLayer::GetViewport() const
{
	FBox2D Viewport(SwapchainSize * Desc.UVRect.Min, SwapchainSize * Desc.UVRect.Max);
	return FIntRect(Viewport.Min.IntPoint(), Viewport.Max.IntPoint());
}

FVector2D FYvrXRLayer::GetQuadSize() const
{
	if (Desc.Flags & IStereoLayers::LAYER_FLAG_QUAD_PRESERVE_TEX_RATIO)
	{
		float AspectRatio = SwapchainSize.Y / SwapchainSize.X;
		return FVector2D(Desc.QuadSize.X, Desc.QuadSize.X * AspectRatio);
	}
	return Desc.QuadSize;
}

// TStereoLayerManager helper functions

bool GetLayerDescMember(const FYvrXRLayer& Layer, IStereoLayers::FLayerDesc& OutLayerDesc)
{
	OutLayerDesc = Layer.Desc;
	return true;
}

void SetLayerDescMember(FYvrXRLayer& Layer, const IStereoLayers::FLayerDesc& Desc)
{
	Layer.Desc = Desc;
}

void MarkLayerTextureForUpdate(FYvrXRLayer& Layer)
{
	// If the swapchain is static we need to re-allocate it before it can be updated
	if (!(Layer.Desc.Flags & IStereoLayers::LAYER_FLAG_TEX_CONTINUOUS_UPDATE))
	{
		Layer.Swapchain.Reset();
		Layer.LeftSwapchain.Reset();
	}
	Layer.bUpdateTexture = true;
}
