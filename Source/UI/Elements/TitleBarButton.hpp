#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIButton.h"
class TitleBarButton : public KlemmUI::UIBox
{
	std::string Icon;

public:
	KlemmUI::UIBackground* unnamed_0;
	KlemmUI::UIButton* button;
	TitleBarButton() : UIBox(true)
	{
	{
	button = new KlemmUI::UIButton(true, 0, 1, nullptr);
	button->SetColor(Vector3f(float(0.1)));
	button->SetHoveredColor(Vector3f(float(0.1)) * 0.75f);
	button->SetPressedColor(Vector3f(float(0.1)) * 0.5f);
	this->AddChild(button);
	{
	auto* e_2 = new KlemmUI::UIBackground(true, 0, 1);
	e_2->SetUseTexture(true, Icon);
	e_2->SetMinSize(Vector2f(float(14)));
	e_2->SetMaxSize(Vector2f(float(14)));
	e_2->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetPadding((float)float(8));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetLeftPadding((float)float(15));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetRightPadding((float)float(15));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	button->AddChild(e_2);
	unnamed_0 = e_2;
	}
	}

	}

	void SetIcon(std::string NewValue)
	{
		Icon = NewValue;
		unnamed_0->SetUseTexture(true, Icon);
	}
};
