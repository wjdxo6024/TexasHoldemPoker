#include "RectTransform.h"

RectTransform::RectTransform()
{
	m_posX = 0.0f;
	m_posY = 0.0f;

	m_AbsolutePosX = 0.0f;
	m_AbsolutePosY = 0.0f;

	m_scaleX = 1.0f;
	m_scaleY = 1.0f;

	m_rotateX = 0.0f;
	m_rotateY = 0.0f;

	m_width = 0.0f;
	m_height = 0.0f;
}

RectTransform::RectTransform(const RectTransform& other)
{

}

RectTransform::~RectTransform()
{

}

void RectTransform::Initialize(float posX, float posY, float width, float height, float scaleX, float scaleY, float rotateX, float rotateY)
{
	SetPosX(posX);
	SetPosY(posY);
	SetWidth(width);
	SetHeight(height);
	SetScaleX(scaleX);
	SetScaleY(scaleY);
	SetRotateX(rotateX);
	SetRotateY(rotateY);
}

float RectTransform::GetPosX()
{
	return m_posX;
}

void RectTransform::SetPosX(float x)
{
	m_posX = x;
}

float RectTransform::GetPosY()
{
	return m_posY;
}

void RectTransform::SetPosY(float y)
{
	m_posY = y;
}

float RectTransform::GetScaleX()
{
	return m_scaleX;
}

void RectTransform::SetScaleX(float x)
{
	m_scaleX = x;
}

float RectTransform::GetScaleY()
{
	return m_scaleY;
}

void RectTransform::SetScaleY(float y)
{
	m_scaleY = y;
}

float RectTransform::GetRotateX()
{
	return m_rotateX;
}

void RectTransform::SetRotateX(float x)
{
	m_rotateX = x;
}

float RectTransform::GetRotateY()
{
	return m_rotateY;
}

void RectTransform::SetRotateY(float y)
{
	m_rotateY = y;
}

float RectTransform::GetWidth()
{
	return m_width;
}

void RectTransform::SetWidth(float width)
{
	m_width = width;
}

float RectTransform::GetHeight()
{
	return m_height;
}

void RectTransform::SetHeight(float height)
{
	m_height = height;
}

float RectTransform::GetFinalWidth() // scaleX * width
{
	return m_width * m_scaleX;
}

float RectTransform::GetFinalHeight() // scaleY * height
{
	return m_height * m_scaleY;
}