#pragma once
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIButton.h"
#include "KlemmUI/UI/UIText.h"
#include "ProfileButton.hpp"
class ProfileListElement : public KlemmUI::UIBox
{
	Vector3f Color = Vector3f(float(1));
	std::string ProfileDescription;

public:
	KlemmUI::UIBox* textFieldBox;
	KlemmUI::UIButton* profileButton;
	KlemmUI::UIText* descriptionBox;
	ProfileButton* copyButton;
	ProfileButton* deleteButton;
	ProfileListElement() : UIBox(true)
	{
	this->SetPadding((float)float(5));
	this->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	this->SetTryFill((bool)true);
	this->SetHorizontal(false);
	{
	profileButton = new KlemmUI::UIButton(true, 0, 1, nullptr);
	profileButton->SetColor(Vector3f(Color));
	profileButton->SetHoveredColor(Vector3f(Color) * 0.75f);
	profileButton->SetPressedColor(Vector3f(Color) * 0.5f);
	profileButton->BoxBorder = KlemmUI::UIBox::BorderType::Rounded;
	profileButton->BorderRadius = float(5);
	profileButton->BorderSizeMode = KlemmUI::UIBox::SizeMode::PixelRelative;
	profileButton->SetVerticalAlign(KlemmUI::UIBox::Align::Centered);
	profileButton->SetTryFill((bool)true);
	profileButton->SetHorizontal(true);
	this->AddChild(profileButton);
	{
	auto* e_2 = new KlemmUI::UIBox(true);
	e_2->SetPadding((float)float(5));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetLeftPadding((float)float(30));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetRightPadding((float)float(30));
	e_2->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->SetHorizontal(false);
	profileButton->AddChild(e_2);
	{
	textFieldBox = new KlemmUI::UIBox(true);
	textFieldBox->SetPadding((float)float(2));
	textFieldBox->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->AddChild(textFieldBox);
	descriptionBox = new KlemmUI::UIText(1, 1, "", nullptr);
	descriptionBox->SetText(ProfileDescription);
	descriptionBox->SetColor(Vector3f(float(0)));
	descriptionBox->SetTextSize(float(11));
	descriptionBox->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	descriptionBox->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	descriptionBox->SetPadding((float)float(2));
	descriptionBox->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	descriptionBox->SetLeftPadding((float)float(15));
	descriptionBox->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_2->AddChild(descriptionBox);
	}
	copyButton = new ProfileButton();
	copyButton->SetIcon("app/images/copy.png");
	profileButton->AddChild(copyButton);
	deleteButton = new ProfileButton();
	deleteButton->SetIcon("app/images/delete.png");
	profileButton->AddChild(deleteButton);
	auto* e_7 = new KlemmUI::UIBox(true);
	e_7->SetMinSize(Vector2f(float(30), float(0)));
	e_7->SetMaxSize(Vector2f(float(30), float(0)));
	e_7->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	profileButton->AddChild(e_7);
	}
	}

	}

	void SetColor(Vector3f NewValue)
	{
		Color = NewValue;
		profileButton->SetColor(Vector3f(Color));
		profileButton->SetHoveredColor(Vector3f(Color) * 0.75f);
		profileButton->SetPressedColor(Vector3f(Color) * 0.5f);
	}
	void SetProfileDescription(std::string NewValue)
	{
		ProfileDescription = NewValue;
		descriptionBox->SetText(ProfileDescription);
	}
};
