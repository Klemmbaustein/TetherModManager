#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIText.h"
class SettingsElement : public KlemmUI::UIBox
{
	std::string Name;

public:
	KlemmUI::UIBox* contentBox;
	KlemmUI::UIText* unnamed_0;
	SettingsElement() : UIBox(true)
	{
	this->SetHorizontalAlign(KlemmUI::UIBox::Align::Centered);
	this->SetVerticalAlign(KlemmUI::UIBox::Align::Centered);
	this->SetTryFill((bool)true);
	{
	auto* e_1 = new KlemmUI::UIBox(true);
	e_1->SetMinSize(Vector2f(float(150)));
	e_1->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_1->SetVerticalAlign(KlemmUI::UIBox::Align::Centered);
	e_1->SetPadding((float)float(5));
	e_1->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_1->SetTryFill((bool)true);
	this->AddChild(e_1);
	{
	auto* e_2 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_2->SetText(Name);
	e_2->SetTextSize(float(11));
	e_2->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_2->WrapDistance = float(290);
	e_2->Wrap = true;
	e_2->WrapSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	e_2->SetPadding((float)float(5));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_1->AddChild(e_2);
	unnamed_0 = e_2;
	}
	contentBox = new KlemmUI::UIBox(true);
	contentBox->SetMinSize(Vector2f(float(300), float(0)));
	contentBox->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	contentBox->SetPadding((float)float(5));
	contentBox->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	this->AddChild(contentBox);
	}

	}

	void SetName(std::string NewValue)
	{
		Name = NewValue;
		unnamed_0->SetText(Name);
	}
};
