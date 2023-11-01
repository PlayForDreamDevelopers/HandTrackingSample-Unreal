// Copyright 2020-2023 Yvr Technology Co., Ltd. All Rights Reserved.

#pragma once

#include "IMotionController.h"
#include "InputCoreTypes.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"

namespace YvrXRInput
{
	enum EYvrControllerButton : uint32_t
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		Start = 4,
		Reserved = 5,
		LIndexTrigger = 6,
		RIndexTrigger = 7,
		LHandTrigger = 8,
		RHandTrigger = 9,
		LThumbstick = 10,
		RThumbstick = 11,
		LThumbstickUp = 12,
		LThumbstickDown = 13,
		LThumbstickLeft = 14,
		LThumbstickRight = 15,
		RThumbstickUp = 16,
		RThumbstickDown = 17,
		RThumbstickLeft = 18,
		RThumbstickRight = 19,
		Total
	};

	struct FYvrKey
	{
		static const FKey Yvr_Left_X_Click;
		static const FKey Yvr_Left_Y_Click;
		static const FKey Yvr_Left_X_Touch;
		static const FKey Yvr_Left_Y_Touch;
		static const FKey Yvr_Left_Menu_Click;
		static const FKey Yvr_Left_Grip_Click;
		static const FKey Yvr_Left_Grip_Axis;
		static const FKey Yvr_Left_Trigger_Click;
		static const FKey Yvr_Left_Trigger_Axis;
		static const FKey Yvr_Left_Trigger_Touch;
		static const FKey Yvr_Left_Thumbstick_X;
		static const FKey Yvr_Left_Thumbstick_Y;
		static const FKey Yvr_Left_Thumbstick_Click;
		static const FKey Yvr_Left_Thumbstick_Touch;
		static const FKey Yvr_Left_Thumbstick_Up;
		static const FKey Yvr_Left_Thumbstick_Down;
		static const FKey Yvr_Left_Thumbstick_Left;
		static const FKey Yvr_Left_Thumbstick_Right;
		static const FKey Yvr_Right_A_Click;
		static const FKey Yvr_Right_B_Click;
		static const FKey Yvr_Right_A_Touch;
		static const FKey Yvr_Right_B_Touch;
		static const FKey Yvr_Right_System_Click;
		static const FKey Yvr_Right_Grip_Click;
		static const FKey Yvr_Right_Grip_Axis;
		static const FKey Yvr_Right_Trigger_Click;
		static const FKey Yvr_Right_Trigger_Axis;
		static const FKey Yvr_Right_Trigger_Touch;
		static const FKey Yvr_Right_Thumbstick_X;
		static const FKey Yvr_Right_Thumbstick_Y;
		static const FKey Yvr_Right_Thumbstick_Click;
		static const FKey Yvr_Right_Thumbstick_Touch;
		static const FKey Yvr_Right_Thumbstick_Up;
		static const FKey Yvr_Right_Thumbstick_Down;
		static const FKey Yvr_Right_Thumbstick_Left;
		static const FKey Yvr_Right_Thumbstick_Right;
	};

	struct FYvrKeyNames
	{
		static const FName Yvr_Left_X_Click;
		static const FName Yvr_Left_Y_Click;
		static const FName Yvr_Left_X_Touch;
		static const FName Yvr_Left_Y_Touch;
		static const FName Yvr_Left_Menu_Click;
		static const FName Yvr_Left_Grip_Click;
		static const FName Yvr_Left_Grip_Axis;
		static const FName Yvr_Left_Trigger_Click;
		static const FName Yvr_Left_Trigger_Axis;
		static const FName Yvr_Left_Trigger_Touch;
		static const FName Yvr_Left_Thumbstick_X;
		static const FName Yvr_Left_Thumbstick_Y;
		static const FName Yvr_Left_Thumbstick_Click;
		static const FName Yvr_Left_Thumbstick_Touch;
		static const FName Yvr_Left_Thumbstick_Up;
		static const FName Yvr_Left_Thumbstick_Down;
		static const FName Yvr_Left_Thumbstick_Left;
		static const FName Yvr_Left_Thumbstick_Right;
		static const FName Yvr_Right_A_Click;
		static const FName Yvr_Right_B_Click;
		static const FName Yvr_Right_A_Touch;
		static const FName Yvr_Right_B_Touch;
		static const FName Yvr_Right_System_Click;
		static const FName Yvr_Right_Grip_Click;
		static const FName Yvr_Right_Grip_Axis;
		static const FName Yvr_Right_Trigger_Click;
		static const FName Yvr_Right_Trigger_Axis;
		static const FName Yvr_Right_Trigger_Touch;
		static const FName Yvr_Right_Thumbstick_X;
		static const FName Yvr_Right_Thumbstick_Y;
		static const FName Yvr_Right_Thumbstick_Click;
		static const FName Yvr_Right_Thumbstick_Touch;
		static const FName Yvr_Right_Thumbstick_Up;
		static const FName Yvr_Right_Thumbstick_Down;
		static const FName Yvr_Right_Thumbstick_Left;
		static const FName Yvr_Right_Thumbstick_Right;
	};

	struct FYvrButtonState
	{
		/** The Unreal button this maps to.  Different depending on whether this is the Left or Right hand controller */
		FName Key;

		/** Whether we're pressed or not.  While pressed, we will generate repeat presses on a timer */
		bool bIsPressed;

		/** Next time a repeat event should be generated for each button */
		double NextRepeatTime;

		/** Default constructor that just sets sensible defaults */
		FYvrButtonState()
			: Key(NAME_None),
			bIsPressed(false),
			NextRepeatTime(0.0)
		{
		}
	};


	struct FYvrControllerState
	{
		/** Button states */
		FYvrButtonState Buttons[EYvrControllerButton::Total];
		FYvrButtonState Touches[EYvrControllerButton::Total];

		float IndexTriggerAxis;
		float ThumbstickAxis[2];

		float HapticAmplitude;
		float HapticFrequency;

		FYvrControllerState()
		{
			IndexTriggerAxis = 0.0;
			ThumbstickAxis[0] = 0.0;
			ThumbstickAxis[1] = 0.0;

			HapticAmplitude = 0.0;
			HapticFrequency = 0.0;

			for (FYvrButtonState& Button : Buttons)
			{
				Button.bIsPressed = false;
				Button.NextRepeatTime = 0.0;
			}

			Buttons[(int32)EYvrControllerButton::A].Key = FYvrKeyNames::Yvr_Right_A_Click;
			Buttons[(int32)EYvrControllerButton::B].Key = FYvrKeyNames::Yvr_Right_B_Click;
			Buttons[(int32)EYvrControllerButton::X].Key = FYvrKeyNames::Yvr_Left_X_Click;
			Buttons[(int32)EYvrControllerButton::Y].Key = FYvrKeyNames::Yvr_Left_Y_Click;
			Buttons[(int32)EYvrControllerButton::Start].Key = FYvrKeyNames::Yvr_Left_Menu_Click;
			//Buttons[(int32)EYvrControllerButton::Reserved].Key = FYvrKeyNames::YvrButton_Reserved;
			Buttons[(int32)EYvrControllerButton::LIndexTrigger].Key = FYvrKeyNames::Yvr_Left_Trigger_Click;
			Buttons[(int32)EYvrControllerButton::RIndexTrigger].Key = FYvrKeyNames::Yvr_Right_Trigger_Click;
			Buttons[(int32)EYvrControllerButton::LHandTrigger].Key = FYvrKeyNames::Yvr_Left_Grip_Click;
			Buttons[(int32)EYvrControllerButton::RHandTrigger].Key = FYvrKeyNames::Yvr_Right_Grip_Click;
			Buttons[(int32)EYvrControllerButton::LThumbstick].Key = FYvrKeyNames::Yvr_Left_Thumbstick_Click;
			Buttons[(int32)EYvrControllerButton::RThumbstick].Key = FYvrKeyNames::Yvr_Right_Thumbstick_Click;
			Buttons[(int32)EYvrControllerButton::LThumbstickUp].Key = FYvrKeyNames::Yvr_Left_Thumbstick_Up;
			Buttons[(int32)EYvrControllerButton::LThumbstickDown].Key = FYvrKeyNames::Yvr_Left_Thumbstick_Down;
			Buttons[(int32)EYvrControllerButton::LThumbstickLeft].Key = FYvrKeyNames::Yvr_Left_Thumbstick_Left;
			Buttons[(int32)EYvrControllerButton::LThumbstickRight].Key = FYvrKeyNames::Yvr_Left_Thumbstick_Right;
			Buttons[(int32)EYvrControllerButton::RThumbstickUp].Key = FYvrKeyNames::Yvr_Right_Thumbstick_Up;
			Buttons[(int32)EYvrControllerButton::RThumbstickDown].Key = FYvrKeyNames::Yvr_Right_Thumbstick_Down;
			Buttons[(int32)EYvrControllerButton::RThumbstickLeft].Key = FYvrKeyNames::Yvr_Right_Thumbstick_Left;
			Buttons[(int32)EYvrControllerButton::RThumbstickRight].Key = FYvrKeyNames::Yvr_Right_Thumbstick_Right;


			for (FYvrButtonState& Touch : Touches)
			{
				Touch.bIsPressed = false;
				Touch.NextRepeatTime = 0.0;
			}

			Touches[(int32)EYvrControllerButton::A].Key = FYvrKeyNames::Yvr_Right_A_Touch;
			Touches[(int32)EYvrControllerButton::B].Key = FYvrKeyNames::Yvr_Right_B_Touch;
			Touches[(int32)EYvrControllerButton::X].Key = FYvrKeyNames::Yvr_Left_X_Touch;
			Touches[(int32)EYvrControllerButton::Y].Key = FYvrKeyNames::Yvr_Left_Y_Touch;

			Touches[(int32)EYvrControllerButton::LIndexTrigger].Key = FYvrKeyNames::Yvr_Left_Trigger_Touch;
			Touches[(int32)EYvrControllerButton::RIndexTrigger].Key = FYvrKeyNames::Yvr_Right_Trigger_Touch;
			Touches[(int32)EYvrControllerButton::LThumbstick].Key = FYvrKeyNames::Yvr_Left_Thumbstick_Touch;
			Touches[(int32)EYvrControllerButton::RThumbstick].Key = FYvrKeyNames::Yvr_Right_Thumbstick_Touch;
		}
	};
}