#pragma once
#include "AppTab.h"

class ProfileTab : public AppTab
{
public:
	ProfileTab();

	void Update() override;

	void GenerateButtons();

	KlemmUI::UIBackground* TabBackground = nullptr;
};