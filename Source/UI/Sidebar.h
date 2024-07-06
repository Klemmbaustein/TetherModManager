#pragma once
#include <KlemmUI/UI/UIBackground.h>
#include "Elements/SidebarButton.hpp"

class Sidebar
{
public:
	Sidebar();

	void Update();

	float GetWidth() const;

	std::vector<SidebarButton*> Buttons;
	KlemmUI::UIBackground* SidebarBackground = nullptr;
};