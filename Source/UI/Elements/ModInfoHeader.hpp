#pragma once
#include "AppButton.hpp"
#include "KlemmUI/Markup/Markup.h"
#include "KlemmUI/UI/UIBackground.h"
#include "KlemmUI/UI/UIBox.h"
#include "KlemmUI/UI/UIText.h"
#include "Separator.hpp"
class ModInfoHeader : public KlemmUI::UIBox
{
	std::string ModDescription;
	std::string ModImage;
	std::string ModInfo;
	std::string ModName;

public:
	AppButton* backButton;
	KlemmUI::UIBackground* modImage;
	KlemmUI::UIBox* actionsBox;
	KlemmUI::UIText* unnamed_0;
	KlemmUI::UIText* unnamed_1;
	KlemmUI::UIText* unnamed_2;
	ModInfoHeader() : UIBox(true)
	{
	this->SetUpPadding((float)float(10));
	this->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	this->SetTryFill((bool)true);
	this->SetHorizontal(false);
	{
	backButton = new AppButton();
	backButton->SetText(KlemmUI::MarkupLanguageManager::GetActive()->GetString("mods_page_back"));
	backButton->SetImage("app/images/back.png");
	this->AddChild(backButton);
	auto* e_2 = new Separator();
	this->AddChild(e_2);
	auto* e_3 = new KlemmUI::UIBox(true);
	e_3->SetHorizontal(true);
	this->AddChild(e_3);
	{
	modImage = new KlemmUI::UIBackground(true, 0, 1);
	modImage->SetUseTexture(true, ModImage);
	modImage->SetMinSize(Vector2f(float(150)));
	modImage->SetMaxSize(Vector2f(float(150)));
	modImage->SetSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	modImage->SetPadding((float)float(5));
	modImage->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_3->AddChild(modImage);
	auto* e_5 = new KlemmUI::UIBox(true);
	e_5->SetPadding((float)float(5));
	e_5->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_5->SetHorizontal(false);
	e_3->AddChild(e_5);
	{
	auto* e_6 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_6->SetText(ModName);
	e_6->SetTextSize(float(20));
	e_6->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_6->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_5->AddChild(e_6);
	unnamed_0 = e_6;
	auto* e_7 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_7->SetText(ModDescription);
	e_7->SetColor(Vector3f(float(0.9)));
	e_7->SetTextSize(float(14));
	e_7->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_7->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_7->WrapDistance = float(2.0);
	e_7->Wrap = true;
	e_7->SetUpPadding((float)float(10));
	e_7->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_5->AddChild(e_7);
	unnamed_1 = e_7;
	auto* e_8 = new KlemmUI::UIText(1, 1, "", nullptr);
	e_8->SetText(ModInfo);
	e_8->SetColor(Vector3f(float(0.9)));
	e_8->SetTextSize(float(14));
	e_8->SetTextSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_8->SetFont(KlemmUI::MarkupLanguageManager::GetActive()->GetFont(""));
	e_8->WrapDistance = float(2.0);
	e_8->Wrap = true;
	e_8->SetUpPadding((float)float(10));
	e_8->SetPaddingSizeMode(KlemmUI::UIBox::SizeMode::PixelRelative);
	e_5->AddChild(e_8);
	unnamed_2 = e_8;
	}
	}
	actionsBox = new KlemmUI::UIBox(true);
	this->AddChild(actionsBox);
	auto* e_10 = new Separator();
	this->AddChild(e_10);
	}

	}

	void SetModDescription(std::string NewValue)
	{
		ModDescription = NewValue;
		unnamed_1->SetText(ModDescription);
	}
	void SetModImage(std::string NewValue)
	{
		ModImage = NewValue;
		modImage->SetUseTexture(true, ModImage);
	}
	void SetModInfo(std::string NewValue)
	{
		ModInfo = NewValue;
		unnamed_2->SetText(ModInfo);
	}
	void SetModName(std::string NewValue)
	{
		ModName = NewValue;
		unnamed_0->SetText(ModName);
	}
};
