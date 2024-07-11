#include "SettingsTab.h"
#include <KlemmUI/UI/UIDropdown.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../Elements/SettingsElement.hpp"
#include "../../Translation.h"
#include "../../Installer.h"
#include "../../FileUtil.h"
#include "../../Log.h"

using namespace KlemmUI;
using namespace nlohmann;

static json SettingsJson;
static const std::string SettingsFile = "app/saved/settings.json";

static json GetSettingsValue(std::string Name, std::string DefaultValue)
{
	if (SettingsJson.contains(Name))
	{
		return SettingsJson.at(Name);
	}
	return DefaultValue;
}

static void SetSettinsValue(std::string Name, json Value)
{
	spdlog::info("Set setting value: {} = {}", Name, Value.dump());
	if (SettingsJson.contains(Name))
	{
		SettingsJson.at(Name) = Value;
	}
	else
	{
		SettingsJson.update({ {Name, Value} });
	}
}

SettingsTab::SettingsTab()
	: AppTab("settings")
{
	TabBackground = new UIBackground(false, 0, 0.05f, Vector2f(1.25f, 0));

	TabBackground
		->SetOpacity(0.9f)
		->SetTryFill(true);

	TabBox
		->AddChild(TabBackground)
		->SetHorizontal(true)
		->SetHorizontalAlign(UIBox::Align::Centered);

	GenerateUI();
}

void SettingsTab::GenerateUI()
{
	TabBackground->DeleteChildren();

	GenerateDropdown({ "English", "Deutsch" }, "language", "English", [](std::string Option)
		{
		});

	GenerateDropdown({ "setting_title_bar_custom", "setting_title_bar_system" }, "title_bar_style", "custom", [](std::string Option)
		{
			Installer::UpdateWindowStyle();
		});
}

std::string SettingsTab::GetSettingString(std::string String)
{
	return GetSettingsValue(String, "");
}

int SettingsTab::GetSettingInt()
{
	return 0;
}

void SettingsTab::LoadSettingsFile()
{
	spdlog::info("Loading settings JSON from {}", SettingsFile);
	SettingsJson = json::parse(FileUtil::ReadFile(SettingsFile), nullptr, false, true);

	if (!SettingsJson.is_object())
	{
		spdlog::info("Settings JSON file doesn't exist or could not be parsed. Creating an empty JSON object for settings.");
		SettingsJson = json::object();
	}
}

void SettingsTab::GenerateDropdown(
	std::vector<std::string> Options,
	std::string SettingName,
	std::string DefaultValue,
	std::function<void(std::string SelectedOption)> OnSet)
{
	auto* Elem = new SettingsElement();

	Elem->SetName(Translate("settings_setting_" + SettingName));

	std::vector<UIDropdown::Option> DropdownOptions;

	std::string Value = GetSettingsValue(SettingName, DefaultValue);

	size_t it = 0, DefaultOption = 0;
	for (const auto& i : Options)
	{
		DropdownOptions.push_back(UIDropdown::Option{
			.Name = Translate(i)
			});
		if (i == Value)
		{
			DefaultOption = it;
		}
		it++;
	}

	auto* Dropdown = new UIDropdown(0, 0.25f, 1, 0, DropdownOptions, nullptr, AppUI::DefaultFont);
	Dropdown
		->SetTextSizeMode(UIBox::SizeMode::PixelRelative)
		->SetTextSize(10, 0.005f);
	Dropdown->SelectOption(DefaultOption);
	Dropdown->OnClickedFunctionIndex = [this, SettingName, Options, OnSet](int Index) 
		{
			std::string NewValue = Options[Index];
			SetSettinsValue(SettingName, NewValue);
			SaveSettings();
			OnSet(NewValue);
		};
	Dropdown->GenerateOptions();

	Elem->contentBox->AddChild(Dropdown);
	TabBackground->AddChild(Elem);
	TabBackground->SetHorizontalAlign(UIBox::Align::Centered);
}

void SettingsTab::SaveSettings()
{
	std::ofstream SaveJson = std::ofstream(SettingsFile);
	SaveJson << SettingsJson.dump(2);
	SaveJson.close();
}
