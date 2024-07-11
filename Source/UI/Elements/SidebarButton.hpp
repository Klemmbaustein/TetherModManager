#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIButton.h"
class SidebarButton : public KlemmUI::UIBox
{
	Vector3f Color = Vector3f(float(0.3), float(0.4), float(1));
	std::string Icon;

public:
	KlemmUI::UIBackground* icon;
	KlemmUI::UIButton* button;
	SidebarButton() : UIBox(true)
	{
	this->SetPadding((float)float(4));
	this->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	{
	button = new KlemmUI::UIButton(true, 0, 1, nullptr);
	button->SetColor(Vector3f(Color));
	button->SetHoveredColor(Vector3f(Color) * 0.75f);
	button->SetPressedColor(Vector3f(Color) * 0.5f);
	button->SetHoveredColor(Vector3f(float(0.7), float(0.8), float(1)));
	button->SetPressedColor(Vector3f(float(0.3), float(0.4), float(1)));
	button->BoxBorder = KlemmUI::UIBox::BorderType::Rounded;
	button->BorderRadius = float(5);
	button->BorderSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	this->AddChild(button);
	{
	icon = new KlemmUI::UIBackground(true, 0, 1);
	icon->SetColor(Vector3f(float(0)));
	icon->SetUseTexture(true, Icon);
	icon->SetMinSize(Vector2f(float(60)));
	icon->SetMaxSize(Vector2f(float(60)));
	icon->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	icon->SetPadding((float)float(2));
	icon->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	button->AddChild(icon);
	}
	}

	}

	void SetColor(Vector3f NewValue)
	{
		Color = NewValue;
		button->SetColor(Vector3f(Color));
		button->SetHoveredColor(Vector3f(Color) * 0.75f);
		button->SetPressedColor(Vector3f(Color) * 0.5f);
	}
	void SetIcon(std::string NewValue)
	{
		Icon = NewValue;
		icon->SetUseTexture(true, Icon);
	}
};
