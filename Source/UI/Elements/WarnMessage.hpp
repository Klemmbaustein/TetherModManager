#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIText.h"
class WarnMessage : public KlemmUI::UIBox
{
	Vector3f Color = Vector3f(float(1), float(0.7), float(0.1));
	std::string Image = std::string("app/images/warning.png");
	std::string Text;
	Vector3f TextColor = Vector3f(float(0));

public:
	KlemmUI::UIBackground* unnamed_0;
	KlemmUI::UIBackground* unnamed_1;
	KlemmUI::UIText* unnamed_2;
	WarnMessage() : UIBox(true)
	{
	this->SetPadding((float)float(20));
	this->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	this->SetTryFill((bool)true);
	{
	auto* e_1 = new KlemmUI::UIBackground(true, 0, 1);
	e_1->SetColor(Vector3f(Color));
	e_1->BoxBorder = KlemmUI::UIBox::BorderType::Rounded;
	e_1->BorderRadius = float(5);
	e_1->BorderSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	e_1->SetMinSize(Vector2f(float(400), float(0)));
	e_1->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	this->AddChild(e_1);
	unnamed_0 = e_1;
	{
	auto* e_2 = new KlemmUI::UIBackground(true, 0, 1);
	e_2->SetColor(Vector3f(TextColor));
	e_2->SetUseTexture(true, Image);
	e_2->SetMinSize(Vector2f(float(64)));
	e_2->SetMaxSize(Vector2f(float(64)));
	e_2->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetPadding((float)float(5));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_1->AddChild(e_2);
	unnamed_1 = e_2;
	auto* e_3 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_3->SetText(Text);
	e_3->SetColor(Vector3f(TextColor));
	e_3->SetTextSize(float(11));
	e_3->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_3->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_3->WrapDistance = float(600);
	e_3->Wrap = true;
	e_3->WrapSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	e_3->SetPadding((float)float(10));
	e_3->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_1->AddChild(e_3);
	unnamed_2 = e_3;
	}
	}

	}

	void SetColor(Vector3f NewValue)
	{
		Color = NewValue;
		unnamed_0->SetColor(Vector3f(Color));
	}
	void SetImage(std::string NewValue)
	{
		Image = NewValue;
		unnamed_1->SetUseTexture(true, Image);
	}
	void SetText(std::string NewValue)
	{
		Text = NewValue;
		unnamed_2->SetText(Text);
	}
	void SetTextColor(Vector3f NewValue)
	{
		TextColor = NewValue;
		unnamed_1->SetColor(Vector3f(TextColor));
		unnamed_2->SetColor(Vector3f(TextColor));
	}
};
