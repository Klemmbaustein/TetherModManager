#include "AppTab.h"
#include "../AppUI.h"
#include "../../Log.h"

std::vector<AppTab*> AppTab::AllTabs;
size_t AppTab::SelectedTab = 0;

void AppTab::UpdateSize()
{
	float SidebarSize = 0;

	if (AppUI::AppSidebar)
	{
		SidebarSize = AppUI::AppSidebar->GetWidth();
	}

	TabBox->SetMinSize(Vector2f(2) - Vector2f(SidebarSize, AppUI::AppTitleBar->GetUsedSize()));
	TabBox->SetPosition(Vector2f(-1, -1) + Vector2f(SidebarSize, 0));
}

AppTab::AppTab(std::string Name)
{
	TabBox = new KlemmUI::UIBox(false, 0);
	
	Log::UI->info("Creating tab: 'tab_{}'", Name);
	this->Name = Name;
	AllTabs.push_back(this);
	UpdateSize();
}

AppTab::~AppTab()
{
	for (size_t i = 0; i < AllTabs.size(); i++)
	{
		if (AllTabs[i] == this)
		{
			AllTabs.erase(AllTabs.begin() + i);
			break;
		}
	}
}

void AppTab::Update()
{
}

void AppTab::OnResized()
{
}

void AppTab::UpdateAllTabs()
{
	for (size_t i = 0; i < AllTabs.size(); i++)
	{
		AppTab* Tab = AllTabs[i];
		Tab->UpdateSize();
		Tab->TabBox->IsVisible = i == SelectedTab;
		Tab->Update();
	}
}
