#include "Sidebar.h"
#include "Tabs/AppTab.h"

using namespace KlemmUI;

Sidebar::Sidebar()
{
	SidebarBackground = new UIBackground(false, -1, 0.075f, Vector2f(0, 2.0f));

	for (size_t i = 0; i < AppTab::AllTabs.size(); i++)
	{
		auto* btn = new SidebarButton();

		btn->button->OnClickedFunction = [i]() {
			AppTab::SelectedTab = i;
			};

		btn->SetIcon("app/images/tab_" + AppTab::AllTabs[i]->GetName() + ".png");
		
		SidebarBackground
			->SetOpacity(0.9f)
			->AddChild(btn);
		Buttons.push_back(btn);
	}
}

void Sidebar::Update()
{
	for (size_t i = 0; i < Buttons.size(); i++)
	{
		Buttons[i]->SetColor(i == AppTab::SelectedTab ? AppUI::HighlightColor : 1);
	}
}

float Sidebar::GetWidth() const
{
	return SidebarBackground->GetUsedSize().X;
}
