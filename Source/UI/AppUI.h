#pragma once
#include <KlemmUI/UI/UIBackground.h>
#include "Sidebar.h"
#include <KlemmUI/UI/UIText.h>

class AppUI
{
public:
	static void Create();
	static void Update();
	static void LoadBackgroundImage(std::string Path);

	static Sidebar* AppSidebar;
	static KlemmUI::Font* DefaultFont;
	static KlemmUI::Font* MonospaceFont;
	static Vector3f HighlightColor;

private:
	static KlemmUI::UIBox* AppBackground;
	static unsigned int BackgroundImage;
};