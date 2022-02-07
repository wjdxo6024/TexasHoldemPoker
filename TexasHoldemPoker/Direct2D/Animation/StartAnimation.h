#pragma once
#include "../../GameSound/EffectSound.h"
#include "../BasicUI/CRectangle.h"
#include "../AdvancedUI/TextOutputField.h"

// 화면에 각각 페이즈 마다 중간에 검은 화면과 글씨가 올라오면서 보여주다가 사라짐
//

class StartAnimation
{
private:
	EffectSound* m_EffectSound;
	CRectangle* m_BannerBackground;
	TextOutputField* m_TextForDraw;

	Direct2DEngine* extD2DEngine;
	GameOption* extGameOption;
	AudioEngine* extAudioEngine;

	int m_AnimationFrame; // 애니메이션 프레임
	int m_AnimationTime; // 애니메이션 시간

	float m_AnimationValue;
	float m_TempValue;
	bool m_IsAnimate;
public:
	StartAnimation();
	StartAnimation(const StartAnimation& other);
	virtual ~StartAnimation();

	bool Initialize(Direct2DEngine* D2DEngine, GameOption* gameOption, AudioEngine* audioEngine);
	bool Render();
	bool Update(double deltaTime);
	bool Release();

	bool Start();
	bool Stop();

	bool SetText(const WCHAR* text);
	bool IsAnimate();
};

