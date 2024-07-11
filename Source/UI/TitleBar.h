#pragma once
#include <KlemmUI/UI/UIBackground.h>
#include "Elements/TitleBarElement.hpp"

class TitleBar
{
public:
	TitleBar();
	void Update();
	
	float GetUsedSize();
	bool Visible = true;

	TitleBarElement* TitleElement = nullptr;
};