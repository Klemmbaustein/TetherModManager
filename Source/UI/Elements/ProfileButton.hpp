#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIButton.h"
class ProfileButton : public KlemmUI::UIBox
{
	std::string Icon;

public:
	KlemmUI::UIButton* button;
	ProfileButton() : UIBox(true)
	{
	this->SetPadding((float)float(5));
	this->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	{
	button = new KlemmUI::UIButton(true, 0, 1, nullptr);
	button->SetColor(Vector3f(float(0.2)));
	button->SetHoveredColor(Vector3f(float(0.2)) * 0.75f);
	button->SetPressedColor(Vector3f(float(0.2)) * 0.5f);
	button->SetUseTexture(true, Icon);
	button->SetMinSize(Vector2f(float(32)));
	button->SetMaxSize(Vector2f(float(32)));
	button->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	this->AddChild(button);
	}

	}

	void SetIcon(std::string NewValue)
	{
		Icon = NewValue;
		button->SetUseTexture(true, Icon);
	}
};
