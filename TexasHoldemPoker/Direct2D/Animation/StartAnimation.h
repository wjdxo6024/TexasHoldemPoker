#pragma once
#include "../../GameSound/EffectSound.h"
#include "../BasicUI/CRectangle.h"
#include "../AdvancedUI/TextOutputField.h"

// ȭ�鿡 ���� ������ ���� �߰��� ���� ȭ��� �۾��� �ö���鼭 �����ִٰ� �����
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

	int m_AnimationFrame; // �ִϸ��̼� ������
	int m_AnimationTime; // �ִϸ��̼� �ð�

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

