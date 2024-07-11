#pragma once
#include "AppTab.h"
#include <functional>

class SettingsTab : public AppTab
{
public:
	SettingsTab();

	void GenerateUI();

	KlemmUI::UIBackground* TabBackground = nullptr;

	static std::string GetSettingString(std::string String);
	static int GetSettingInt();

	static void LoadSettingsFile();

private:

	void GenerateDropdown(
		std::vector<std::string> Options,
		std::string SettingsName,
		std::string DefaultValue,
		std::function<void(std::string SelectedOption)> OnSet);

	void SaveSettings();
};