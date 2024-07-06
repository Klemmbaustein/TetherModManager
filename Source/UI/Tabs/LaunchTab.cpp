#include "LaunchTab.h"
#include <KlemmUI/UI/UIBackground.h>
#include <KlemmUI/UI/UIButton.h>
#include <KlemmUI/UI/UIText.h>
#include "../../Log.h"
#include "../../Translation.h"
#include "../../Game/Game.h"
#include "../../Game/Launch.h"
#include "../../BackgroundTask.h"

#include "../Elements/LaunchButton.hpp"

using namespace KlemmUI;

LaunchTab::LaunchTab()
	: AppTab("play")
{
	auto* TabBackground = new UIBackground(false, 0, 0.05f, 0);

	auto* Button = new LaunchButton();

	Button->button->OnClickedFunction = []() {
			new BackgroundTask([]() {
				Game::Launch::LaunchGame("-novid");
				}, nullptr, "Launch");
		};

	TabBackground
		->SetOpacity(0.9f)
		->SetTryFill(true)
		->SetHorizontalAlign(UIBox::Align::Centered)
		->SetVerticalAlign(UIBox::Align::Centered)
		->AddChild(Button);

	TabBox->AddChild(TabBackground);
	TabBox->SetVerticalAlign(UIBox::Align::Default);
}