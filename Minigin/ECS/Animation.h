#pragma once

struct Animation
{

	int m_Index;
	int m_Frames;
	int m_Speed;

	Animation() {}
	Animation(int i, int f, int s)
		:m_Index(i),m_Frames(f),m_Speed(s)
	{
		
	}

};