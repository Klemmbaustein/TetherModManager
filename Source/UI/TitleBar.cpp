#include "TitleBar.h"
#include "../Installer.h"
#include "../Translation.h"
#include "Tabs/AppTab.h"
#include "Tabs/SettingsTab.h"

TitleBar::TitleBar()
{
	TitleElement = new TitleBarElement();
	TitleElement->UpdateElement();
	TitleElement->closeButton->button->SetHoveredColor(Vector3f(0.6f, 0.0f, 0.0f));
	TitleElement->closeButton->button->SetPressedColor(Vector3f(0.5f, 0.1f, 0.1f));

	TitleElement->minimizeButton->button->OnClickedFunction = []()
		{
			Installer::AppWindow->SetMinimized(true);
		};

	TitleElement->maximizeButton->button->OnClickedFunction = []()
		{
			Installer::AppWindow->SetWindowFullScreen(true);
		};

	TitleElement->closeButton->button->OnClickedFunction = []()
		{
			Installer::AppWindow->Close();
		};

	Visible = SettingsTab::GetSettingString("title_bar_style") == "setting_title_bar_custom";
}

void TitleBar::Update()
{
	TitleElement->SetPosition(Vector2f(-1, 1 - TitleElement->GetUsedSize().Y));

	std::string TitleString = TranslateFormat("app_title", Translate("tab_" + AppTab::AllTabs[AppTab::SelectedTab]->GetName()).c_str());

	TitleElement->IsVisible = Visible;
	TitleElement->SetTitle(TitleString);
	Installer::AppWindow->SetTitle(TitleString);
}

float TitleBar::GetUsedSize()
{
	return Visible ? TitleElement->GetUsedSize().Y : 0;
}
