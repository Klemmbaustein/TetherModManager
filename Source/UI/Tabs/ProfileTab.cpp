#include "ProfileTab.h"
#include <KlemmUI/UI/UITextField.h>
#include "../../Game/Profile.h"
#include "../Elements/ProfileListElement.hpp"

using namespace KlemmUI;

ProfileTab::ProfileTab()
	: AppTab("profiles")
{
	TabBackground = new UIBackground(false, 0, 0.05f, Vector2f(1.25f, 0));

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
	TabBackground->DeleteChildren();
	for (Game::Profile::ProfileInfo i : Game::Profile::GetAllProfiles())
	{
		bool Selected = i.DisplayName == Game::Profile::Current.DisplayName;

		auto* Element = new ProfileListElement();
		Element->SetColor(Selected ? AppUI::HighlightColor : 1);

		auto* TextField = new UITextField(0, Selected ? AppUI::HighlightColor : 1, AppUI::DefaultFont, nullptr);
		TextField
			->SetText(i.DisplayName)
			->SetTextSize(12)
			->SetTextSizeMode(UIBox::SizeMode::PixelRelative)
			->SetTextColor(0)
			->SetOpacity(1)
			->SetMinSize(Vector2f(340, 0))
			->SetSizeMode(UIBox::SizeMode::PixelRelative);

		TextField->OnClickedFunction = [this, TextField, i]() mutable
			{
				if (i.DisplayName != "R2Northstar")
				{
					i.Rename(TextField->GetText());
				}
				else
				{
					GenerateButtons();
				}
			};

		Element->textFieldBox->AddChild(TextField);

		if (i.DisplayName == "R2Northstar")
		{
			delete Element->deleteButton;
		}

		Element->profileButton->OnClickedFunction = [this, i]()
			{
				Game::Profile::SetCurrent(i);
			};

		Element->copyButton->button->OnClickedFunction = []()
			{

			};

		Element->descriptionBox->SetText(i.ProfilePath.string());
		TabBackground->AddChild(Element);
	}
}
