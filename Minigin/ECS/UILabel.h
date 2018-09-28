#pragma once

#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>



class TransformComponent;


class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour);
	
	~UILabel();
	void SetLabelText(std::string text, std::string font);
	//void update() override;
	void draw() ;
	UILabel(const UILabel& other) = delete;
	UILabel(UILabel&& other) = delete;
	UILabel& operator=(const UILabel& other) = delete;
	UILabel& operator=(UILabel&& other) = delete;

private:
	SDL_Rect m_Position;
	std::string m_LabelText;
	std::string m_LabelFont;
	SDL_Color m_TextColour;
	SDL_Texture* m_pLabelTexture;
	
	bool m_NeedsUpdate;
};
