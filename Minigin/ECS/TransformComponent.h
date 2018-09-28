#pragma once
#include "./Components.h"
#include "../Vector2D.h"

class TransformComponent final : public Component
{
public:
	

	TransformComponent();
	TransformComponent(int sc);
	TransformComponent(float x, float y);
	TransformComponent(float x, float y, int h, int w, int sc);
	const Vector2D& GetPosition() const { return m_Position; }	
	const int& GetScale() const { return m_Scale; }
	const int& GetHeight() const { return m_Height; }
	const int& GetWidth() const { return m_Width; }
	void Translate(float x, float y);
	void Translate(const Vector2D& position);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetScale(int scale);
	void SetHeight(int height);
	void SetWidth(int Width);
	Vector2D m_Position;
	void init() override;
	void update() override;
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;
private:

	//Vector2D m_Velocity;

	int m_Height = 32;
	int m_Width = 32;
	int m_Scale = 1;
	



};