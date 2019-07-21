#pragma once

struct Animation
{

	int m_Index = 0;
	int m_Frames = 0;
	int m_Speed = 0;

	Animation() {}
	Animation(int i, int f, int s)
		:m_Index(i),m_Frames(f),m_Speed(s)
	{
		
	}

};