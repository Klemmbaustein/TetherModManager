#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIText.h"
#include "TitleBarButton.hpp"
class TitleBarElement : public KlemmUI::UIBox
{
	std::string Title = std::string("Title");

public:
	KlemmUI::UIText* unnamed_0;
	TitleBarButton* closeButton;
	TitleBarButton* maximizeButton;
	TitleBarButton* minimizeButton;
	TitleBarElement() : UIBox(true)
	{
	{
	auto* e_1 = new KlemmUI::UIBackground(true, 0, 1);
	e_1->SetColor(Vector3f(float(0.1)));
	e_1->SetVerticalAlign(KlemmUI::UIBox::Align::Centered);
	this->AddChild(e_1);
	{
	auto* e_2 = new KlemmUI::UIBox(true);
	e_2->SetMinSize(Vector2f(float(1.5), float(0)));
	e_2->SetMaxSize(Vector2f(float(1.5), float(2)));
	e_2->SetVerticalAlign(KlemmUI::UIBox::Align::Centered);
	e_1->AddChild(e_2);
	{
	auto* e_3 = new KlemmUI::UIBackground(true, 0, 1);
	e_3->SetMinSize(Vector2f(float(16)));
	e_3->SetMaxSize(Vector2f(float(16)));
	e_3->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_3->SetPadding((float)float(5));
	e_3->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->AddChild(e_3);
	auto* e_4 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_4->SetText(Title);
	e_4->SetTextSize(float(12));
	e_4->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_4->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_2->AddChild(e_4);
	unnamed_0 = e_4;
	}
	auto* e_5 = new KlemmUI::UIBox(true);
	e_5->SetMinSize(Vector2f(float(0.5), float(0)));
	e_5->SetMaxSize(Vector2f(float(0.5), float(2)));
	e_5->SetHorizontalAlign(KlemmUI::UIBox::Align::Reverse);
	e_1->AddChild(e_5);
	{
	closeButton = new TitleBarButton();
	closeButton->SetIcon("app/images/window_close.png");
	e_5->AddChild(closeButton);
	maximizeButton = new TitleBarButton();
	maximizeButton->SetIcon("app/images/window_max_1.png");
	e_5->AddChild(maximizeButton);
	minimizeButton = new TitleBarButton();
	minimizeButton->SetIcon("app/images/window_min.png");
	e_5->AddChild(minimizeButton);
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
