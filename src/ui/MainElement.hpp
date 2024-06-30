#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIText.h"
class MainElement : public KlemmUI::UIBox
{
	std::string Message;

public:
	KlemmUI::UIText* unnamed_0;
	MainElement() : UIBox(true)
	{
	this->SetPosition(Vector2f(float(-1), float(-1)));
	{
	auto* e_1 = new KlemmUI::UIBackground(true, 0, 1);
	e_1->SetColor(Vector3f(float(0.05), float(0.05), float(0.15)));
	e_1->SetMinSize(Vector2f(float(2), float(2)));
	e_1->SetMaxSize(Vector2f(float(2), float(2)));
	e_1->SetVerticalAlign(KlemmUI::UIBox::Align::Centered);
	e_1->SetHorizontalAlign(KlemmUI::UIBox::Align::Centered);
	this->AddChild(e_1);
	{
	auto* e_2 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_2->SetText(Message);
	e_2->SetColor(Vector3f(float(1)));
	e_2->SetTextSize(float(40));
	e_2->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_1->AddChild(e_2);
	unnamed_0 = e_2;
	}
	}

	}

	void SetMessage(std::string NewValue)
	{
		Message = NewValue;
		unnamed_0->SetText(Message);
	}
};
