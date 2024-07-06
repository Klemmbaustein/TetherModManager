#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
class Separator : public KlemmUI::UIBox
{
	KlemmUI::AnyContainer Color = KlemmUI::AnyContainer(float(1));
	Vector2f Size = Vector2f(float(1), float(1));

public:
	KlemmUI::UIBackground* unnamed_0;
	Separator() : UIBox(true)
	{
	this->SetPadding((float)float(5));
	this->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	this->SetTryFill((bool)true);
	this->SetHorizontal(false);
	{
	auto* e_1 = new KlemmUI::UIBackground(true, 0, 1);
	e_1->SetMinSize(Vector2f(Size));
	e_1->SetMaxSize(Vector2f(Size));
	e_1->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_1->SetTryFill((bool)true);
	this->AddChild(e_1);
	unnamed_0 = e_1;
	}

	}

	void SetColor(KlemmUI::AnyContainer NewValue)
	{
		Color = NewValue;
	}
	void SetSize(Vector2f NewValue)
	{
		Size = NewValue;
		unnamed_0->SetMinSize(Vector2f(Size));
		unnamed_0->SetMaxSize(Vector2f(Size));
	}
};
