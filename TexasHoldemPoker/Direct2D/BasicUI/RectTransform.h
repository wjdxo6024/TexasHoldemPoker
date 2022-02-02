#pragma once
class RectTransform
{
private:
	float m_posX;
	float m_posY;

	float m_AbsolutePosX;
	float m_AbsolutePosY;

	float m_scaleX;
	float m_scaleY;

	float m_rotateX;
	float m_rotateY;

	float m_width;
	float m_height;

public:
	RectTransform();
	RectTransform(const RectTransform& other);
	virtual ~RectTransform();

	void Initialize(float posX, float posY, float width, float height, float scaleX, float scaleY, float rotateX, float rotateY);

	float GetPosX();
	void SetPosX(float x);

	float GetPosY();
	void SetPosY(float y);

	float GetScaleX();
	void SetScaleX(float x);

	float GetScaleY();
	void SetScaleY(float y);

	float GetRotateX();
	void SetRotateX(float x);

	float GetRotateY();
	void SetRotateY(float y);

	float GetWidth();
	void SetWidth(float width);

	float GetHeight();
	void SetHeight(float height);

	float GetFinalWidth(); // scaleX * width
	float GetFinalHeight(); // scaleY * height;
};

