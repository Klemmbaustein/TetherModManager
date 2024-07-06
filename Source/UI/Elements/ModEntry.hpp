#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIButton.h"
#include "KlemmUI/UI/UIText.h"
class ModEntry : public KlemmUI::UIBox
{
	std::string Image;
	std::string Name;

public:
	KlemmUI::UIBackground* image;
	KlemmUI::UIButton* button;
	KlemmUI::UIText* unnamed_0;
	ModEntry() : UIBox(true)
	{
	this->SetPadding((float)float(5));
	this->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	{
	button = new KlemmUI::UIButton(true, 0, 1, nullptr);
	button->BoxBorder = KlemmUI::UIBox::BorderType::Rounded;
	button->BorderRadius = float(5);
	button->BorderSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	button->SetMinSize(Vector2f(float(140), float(200)));
	button->SetMaxSize(Vector2f(float(140), float(200)));
	button->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	button->SetHorizontal(false);
	this->AddChild(button);
	{
	auto* e_2 = new KlemmUI::UIBackground(true, 0, 1);
	e_2->SetColor(Vector3f(float(0.1)));
	button->AddChild(e_2);
	{
	image = new KlemmUI::UIBackground(true, 0, 1);
	image->SetUseTexture(true, Image);
	image->SetMinSize(Vector2f(float(140)));
	image->SetMaxSize(Vector2f(float(140)));
	image->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->AddChild(image);
	}
	auto* e_4 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_4->SetText(Name);
	e_4->SetColor(Vector3f(float(0)));
	e_4->SetTextSize(float(10));
	e_4->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_4->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_4->WrapDistance = float(260);
	e_4->Wrap = true;
	e_4->WrapSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	e_4->SetPadding((float)float(2));
	e_4->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	button->AddChild(e_4);
	unnamed_0 = e_4;
	}
	}

	}

	void SetImage(std::string NewValue)
	{
		Image = NewValue;
		image->SetUseTexture(true, Image);
	}
	void SetName(std::string NewValue)
	{
		Name = NewValue;
		unnamed_0->SetText(Name);
	}
};
