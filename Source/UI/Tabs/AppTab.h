#pragma once
#include <string>
#include <vector>
#include <KlemmUI/UI/UIBox.h>
#include "../AppUI.h"

class AppTab
{
	std::string Name;
	void UpdateSize();
public:
	AppTab(std::string Name);
	AppTab(const AppTab&) = delete;
	virtual ~AppTab();

	virtual void Update();
	virtual void OnResized();

	static void UpdateAllTabs();
	static std::vector<AppTab*> AllTabs;
	static size_t SelectedTab;

	const std::string& GetName()
	{
		return Name;
	}
protected:
	KlemmUI::UIBox* TabBox = nullptr;
};