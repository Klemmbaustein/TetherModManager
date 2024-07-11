#include "Profile.h"
#include "Game.h"
#include "../FileUtil.h"
#include "../Log.h"
#include "../UI/Tabs/ProfileTab.h"
#include "../UI/Tabs/ModsTab.h"
#include <fstream>

Game::Profile::ProfileInfo Game::Profile::Current;

static std::string ProfileTextFile = "app/saved/profile.txt";

static std::string GetSavedProfileName()
{
	if (std::filesystem::exists(ProfileTextFile))
	{
		return FileUtil::ReadFile(ProfileTextFile);
	}

	return "R2Northstar";
}

std::vector<Game::Profile::ProfileInfo> Game::Profile::GetAllProfiles()
{
	static std::vector<std::string> ProfileDirectories =
	{
		"mods/",
		"packages/",
		"plugins/"
	};

	std::string GamePath = Game::GetGameLocation();

	if (!std::filesystem::exists(GamePath))
	{
		return {};
	}

	std::vector<ProfileInfo> Found;
	
	for (const auto& GameDir : std::filesystem::directory_iterator(GamePath))
	{
		for (const std::string& PossibleDir : ProfileDirectories)
		{
			if (std::filesystem::exists(GameDir.path() / PossibleDir))
			{
				Found.push_back(ProfileInfo{
					.ProfilePath = GameDir.path(),
					.DisplayName = GameDir.path().filename().string()
					});
				break;
			}
		}
	}

	return Found;
}

void Game::Profile::SetCurrent(ProfileInfo NewCurrent)
{
	Current = NewCurrent;
	AppTab::GetTabByName<ModsTab>("mods")->OnResized();
	AppTab::GetTabByName<ProfileTab>("profiles")->GenerateButtons();

	std::ofstream Out = std::ofstream(ProfileTextFile);
	Out << NewCurrent.DisplayName;
	Out.close();
}

void Game::Profile::Init()
{
	std::vector<ProfileInfo> AllProfiles = GetAllProfiles();

	std::string SavedName = GetSavedProfileName();
	for (const auto& i : AllProfiles)
	{
		if (i.DisplayName == SavedName)
		{
			Current = i;
		}
	}
}

void Game::Profile::ProfileInfo::Rename(std::string NewName)
{
	bool IsCurrent = Current.ProfilePath == ProfilePath;

	std::filesystem::path New = ProfilePath / ".." / NewName;

	// This might throw an exception, for example if the new name is 'con' on Windows.
	// Windows is a very sane and normal operating system.
	try
	{
		if (std::filesystem::exists(New))
		{
			spdlog::warn("Rename profile failed: {} already exists ", New.string());
			AppTab::GetTabByName<ProfileTab>("profiles")->GenerateButtons();
			return;
		}
	}
	catch (std::filesystem::filesystem_error& e)
	{
		spdlog::warn("Rename profile failed: Failed checking for already existing directory: {}", e.what());
		AppTab::GetTabByName<ProfileTab>("profiles")->GenerateButtons();
		return;
	}

	spdlog::info("Rename profile: {} -> {}", DisplayName, NewName);

	try
	{
		std::filesystem::rename(ProfilePath, New);
	}
	catch (std::filesystem::filesystem_error& e)
	{
		spdlog::warn("Rename profile failed: Failed to rename profile dir: {}", e.what());
		AppTab::GetTabByName<ProfileTab>("profiles")->GenerateButtons();
		return;
	}

	ProfilePath = std::filesystem::canonical(New);

	if (IsCurrent)
	{
		SetCurrent(*this);
	}
	else
	{
		AppTab::GetTabByName<ProfileTab>("profiles")->GenerateButtons();
	}
}
