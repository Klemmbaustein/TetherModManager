#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIText.h"
#include "TitleBarButton.hpp"
class TitleBar : public KlemmUI::UIBox
{
	std::string Title = std::string("Title");

public:
	KlemmUI::UIText* unnamed_0;
	TitleBar() : UIBox(true)
	{
	{
	auto* e_1 = new KlemmUI::UIBackground(true, 0, 1);
	e_1->SetColor(Vector3f(float(0.1)));
	e_1->SetMinSize(Vector2f(float(0), float(32px)));
	e_1->SetVerticalAlign(KlemmUI::UIBox::Align::Centered);
	this->AddChild(e_1);
	{
	auto* e_2 = new KlemmUI::UIBox(true);
	e_2->SetMinSize(Vector2f(float(1.5), float(0)));
	e_2->SetMaxSize(Vector2f(float(1.5), float(2)));
	e_1->AddChild(e_2);
	{
	auto* e_3 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_3->SetText(Title);
	e_3->SetTextSize(float(12));
	e_3->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_3->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_2->AddChild(e_3);
	unnamed_0 = e_3;
	}
	auto* e_4 = new KlemmUI::UIBox(true);
	e_4->SetMinSize(Vector2f(float(0.5), float(0)));
	e_4->SetMaxSize(Vector2f(float(0.5), float(2)));
	e_4->SetHorizontalAlign(KlemmUI::UIBox::Align::Reverse);
	e_1->AddChild(e_4);
	{
	auto* e_5 = new TitleBarButton();
	->SetIcon("app/images/window_min.png");
	e_4->AddChild(e_5);
	}
	}
	}

	}

	void SetTitle(std::string NewValue)
	{
		Title = NewValue;
		unnamed_0->SetText(Title);
	}
};
