#include "YvrBusinessBPLibrary.h"
#include "YvrBusinessWrapper.h"
#include "YvrBusiness.h"

UYvrBusinessBPLibrary::UYvrBusinessBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

FString UYvrBusinessBPLibrary::GetDeviceSn()
{
#if PLATFORM_ANDROID
	return YvrBusinessWrapper::GetDeviceSn();
#endif
	return FString("current platform is windows");
}

FString UYvrBusinessBPLibrary::GetDeviceModel()
{
#if PLATFORM_ANDROID
	return YvrBusinessWrapper::GetDeviceModel();
#endif
	return FString("current platform is windows");
}

FString UYvrBusinessBPLibrary::GetSoftwareVersion()
{
#if PLATFORM_ANDROID
	return YvrBusinessWrapper::GetSoftwareVersion();
#endif
	return FString("current platform is windows");
}
