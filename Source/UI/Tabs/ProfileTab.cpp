#include "ProfileTab.h"
#include <KlemmUI/UI/UITextField.h>
#include "../../Game/Profile.h"
#include "../Elements/ProfileListElement.hpp"

using namespace KlemmUI;

ProfileTab::ProfileTab()
	: AppTab("profiles")
{
	TabBackground = new UIBackground(false, 0, 0.05f, Vector2f(1.5f, 0));

	TabBackground
		->SetOpacity(0.9f)
		->SetTryFill(true);

	TabBox
		->AddChild(TabBackground)
		->SetHorizontal(true)
		->SetHorizontalAlign(UIBox::Align::Centered);
	TabBox->UpdateElement();
	GenerateButtons();
}

void ProfileTab::Update()
{
}

void ProfileTab::GenerateButtons()
{
	for (const auto& i : Game::Profile::GetAllProfiles())
	{
		auto* Element = new ProfileListElement();

		auto* TextField = new UITextField(0, 1, AppUI::DefaultFont, nullptr);
		TextField
			->SetText(i.DisplayName)
			->SetTextSize(12)
			->SetTextSizeMode(UIBox::SizeMode::PixelRelative)
			->SetTextColor(0)
			->SetOpacity(1)
			->SetMinSize(Vector2f(340, 0))
			->SetSizeMode(UIBox::SizeMode::PixelRelative);
		Element->textFieldBox->AddChild(TextField);

		Element->descriptionBox->SetText(i.ProfilePath.string());
		TabBackground->AddChild(Element);
	}
}
