#pragma once

enum class ButtonEvent
{
	ButtonEvent_Empty = -1,

	ButtonEvent_No,
	ButtonEvent_Yes,
	ButtonEvent_Cancel,
	ButtonEvent_Confirm,

	// MainMenu
	ButtonEvent_MainMenu_GoToSinglePlay,
	ButtonEvent_MainMenu_GoToMultiPlay,
	ButtonEvent_MainMenu_GoToOption,
	ButtonEvent_MainMenu_GoToExit,

	// SinglePlay
	ButtonEvent_SinglePlay_Back,
	ButtonEvent_SinglePlay_Fold,
	ButtonEvent_SinglePlay_Call,
	ButtonEvent_SinglePlay_Raise,

	// MultiPlay
	ButtonEvent_MultiPlay_Back,
	ButtonEvent_MultiPlay_Fold,
	ButtonEvent_MultiPlay_Call,
	ButtonEvent_MultiPlay_Raise,
	// Option
	ButtonEvent_Option_Back,

	ButtonEvent_Option_EffectSoundVolumeUp,
	ButtonEvent_Option_EffectSoundVolumeMoreUp,
	ButtonEvent_Option_EffectSoundVolumeDown,
	ButtonEvent_Option_EffectSoundVolumeMoreDown,
	ButtonEvent_Option_BackGroundSoundVolumeUp,
	ButtonEvent_Option_BackGroundSoundVolumeMoreUp,
	ButtonEvent_Option_BackGroundSoundVolumeDown,
	ButtonEvent_Option_BackGroundSoundVolumeMoreDown,

	ButtonEvent_Option_WindowSizeUp,
	ButtonEvent_Option_WindowSizeDown,
	// Exit
	ButtonEvent_Exit_Back,
	ButtonEvent_Exit_Yes,
	ButtonEvent_Exit_No

};