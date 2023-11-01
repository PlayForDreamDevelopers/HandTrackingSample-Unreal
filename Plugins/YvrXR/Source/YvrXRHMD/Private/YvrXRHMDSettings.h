// Copyright 2020-2023 Yvr Technology Co., Ltd. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "YvrXRFunctionLibrary.h"
#include "YvrXRHMDSettings.generated.h"

UENUM()
enum class EYvrXRHandTrackingSupport : uint8
{
	ControllersOnly,
	ControllersAndHands,
	HandsOnly
};


/**
* Implements the settings for the YvrVR plugin.
*/
UCLASS(config = Engine, defaultconfig)
class YVRXRHMD_API UYvrXRHMDSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/** Whether the Splash screen is enabled. */
	//UPROPERTY(config, EditAnywhere, Category = SplashScreen)
	//	bool bAutoEnabled;

	/** An array of splash screen descriptors listing textures to show and their positions. */
	//UPROPERTY(config, EditAnywhere, Category = SplashScreen)
	//	TArray<FYvrSplashDesc> SplashDescs;

	/** If enabled, the target HMD will perform a color space transformation */
	//UPROPERTY(config, EditAnywhere, Category = General)
	//	bool bEnableSpecificColorGamut;

	/** The target color space */
	//UPROPERTY(config, EditAnywhere, Category = General)
		//EYvrColorSpace	ColorSpace;

	/** Default CPU level controlling CPU frequency on the mobile device */
	UPROPERTY(config, EditAnywhere, Category = General)
		EPerformanceLevel CPULevel;

	/** Default GPU level controlling GPU frequency on the mobile device */
	UPROPERTY(config, EditAnywhere, Category = General)
		EPerformanceLevel GPULevel;

	/** Default Fixed Foveated Rendering level for Yvr device*/
	UPROPERTY(config, EditAnywhere, Category = General)
		EYvrFixedFoveatedRenderingLevel FFRLevel;

	UPROPERTY(config, EditAnywhere, Category = General)
		bool FFRDynamic;

	UPROPERTY(Config, EditAnywhere, Category = General)
		bool bUseHWsRGBEncoding;

	UPROPERTY(Config, EditAnywhere, Category = General)
		bool bUseSpaceWarp;

	/** Compensates in the compositor for chromatic aberration, at a higher GPU cost but without the color fringes on the sides of the lenses */
	//UPROPERTY(config, EditAnywhere, Category = Mobile)
	//	bool bChromaCorrection;

	/** Recenters the HMD too when the controller recenter button is pressed */
	//UPROPERTY(config, EditAnywhere, Category = Mobile)
	//	bool bRecenterHMDWithController;

	/** If enabled the app will be focus aware. This will keep the app in foreground when the User presses the Yvr button (needs the app to handle input focus loss!) */
	//UPROPERTY(config, EditAnywhere, Category = Mobile)
	//	bool bFocusAware;

	/** If enabled the app will use the Yvr system keyboard for input fields. This requires that the app be focus aware. */
	//UPROPERTY(config, EditAnywhere, Category = Mobile)
	//	bool bRequiresSystemKeyboard;

	UPROPERTY(config, EditAnywhere, Category = General, meta = (DisplayName = "OS Splash Screen", FilePathFilter = "png"))
		FFilePath OSSplashScreen;

	UPROPERTY(config)
		bool bUsingOSSplash;

	/** Whether controllers and/or hands can be used with the app */
	UPROPERTY(Config, EditAnywhere, Category = Controller)
		EYvrXRHandTrackingSupport HandTrackingSupport;

	//Base Settings
	float PixelDensity;
	float DisplayRefreshRate;
	FVector BasePosition;
	FQuat BaseOrientation;
	bool bApplyColorScaleAndOffsetToAllLayers;
	FLinearColor ColorScale;
	FLinearColor ColorOffset;

	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void HandlesRGBHWSupport();
private:
	void ResetsRGBConfig();
#endif
};
