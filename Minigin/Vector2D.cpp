#include "MiniginPCH.h"
#include "Vector2D.h"

Vector2D::Vector2D()
{
	m_X = 0.0f;
	m_Y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->m_X = x;
	this->m_Y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->m_X += vec.m_X;
	this->m_Y += vec.m_Y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->m_X -= vec.m_X;
	this->m_Y -= vec.m_Y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->m_X *= vec.m_X;
	this->m_Y *= vec.m_Y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->m_X /= vec.m_X;
	this->m_Y /= vec.m_Y;

	return *this;
}

Vector2D Vector2D::operator+ (const Vector2D& vec)
{
	Vector2D result;
	result.m_X = this->m_X + vec.m_X;
	result.m_Y = this->m_Y + vec.m_Y;
	return result;
}

Vector2D Vector2D::operator- (const Vector2D& vec)
{
	Vector2D result;
	result.m_X = this->m_X - vec.m_X;
	result.m_Y = this->m_Y - vec.m_Y;
	return result;
}

Vector2D Vector2D::operator* (const Vector2D& vec)
{
	Vector2D result;
	result.m_X = this->m_X * vec.m_X;
	result.m_Y = this->m_Y * vec.m_Y;
	return result;
}

Vector2D Vector2D::operator/ (const Vector2D& vec)
{
	Vector2D result;
	result.m_X = this->m_X / vec.m_X;
	result.m_Y = this->m_Y / vec.m_Y;
	return result;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->m_X *= i;
	this->m_Y *= i;

	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->m_X = 0;
	this->m_Y = 0;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.m_X << "," << vec.m_Y << ")";
	return stream;
}