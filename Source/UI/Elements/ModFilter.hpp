#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIButton.h"
#include "KlemmUI/UI/UIText.h"
class ModFilter : public KlemmUI::UIBox
{
	Vector3f Color;
	std::string Text;

public:
	KlemmUI::UIButton* button;
	KlemmUI::UIText* unnamed_0;
	ModFilter() : UIBox(true)
	{
	this->SetPadding((float)float(5));
	this->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	{
	button = new KlemmUI::UIButton(true, 0, 1, nullptr);
	button->SetColor(Vector3f(Color));
	button->SetHoveredColor(Vector3f(Color) * 0.75f);
	button->SetPressedColor(Vector3f(Color) * 0.5f);
	button->BoxBorder = KlemmUI::UIBox::BorderType::Rounded;
	button->BorderRadius = float(5);
	button->BorderSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	button->SetMinSize(Vector2f(float(100), float(0)));
	button->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	button->SetHorizontalAlign(KlemmUI::UIBox::Align::Centered);
	this->AddChild(button);
	{
	auto* e_2 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_2->SetText(Text);
	e_2->SetColor(Vector3f(float(0)));
	e_2->SetTextSize(float(10));
	e_2->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_2->SetPadding((float)float(5));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	button->AddChild(e_2);
	unnamed_0 = e_2;
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
	void SetText(std::string NewValue)
	{
		Text = NewValue;
		unnamed_0->SetText(Text);
	}
};
