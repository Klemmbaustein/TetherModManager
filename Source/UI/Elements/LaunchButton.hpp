#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIButton.h"
#include "KlemmUI/UI/UIText.h"
class LaunchButton : public KlemmUI::UIBox
{

public:
	KlemmUI::UIButton* button;
	KlemmUI::UIText* text;
	LaunchButton() : UIBox(true)
	{
	{
	button = new KlemmUI::UIButton(true, 0, 1, nullptr);
	button->SetColor(Vector3f(float(1)));
	button->SetHoveredColor(Vector3f(float(1)) * 0.75f);
	button->SetPressedColor(Vector3f(float(1)) * 0.5f);
	button->BoxBorder = KlemmUI::UIBox::BorderType::Rounded;
	button->BorderRadius = float(10);
	button->BorderSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	button->SetPadding((float)float(25));
	button->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	this->AddChild(button);
	{
	text = new KlemmUI::UIText(1, 1, "", nullptr);
	text->SetText(KlemmUI::MarkupLanguageManager::GetActive()->GetString("play_launch_northstar"));
	text->SetColor(Vector3f(float(0)));
	text->SetTextSize(float(25));
	text->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	text->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	text->SetPadding((float)float(8));
	text->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	button->AddChild(text);
	}
	}

	}

};
