#include "Profile.h"
#include "Game.h"
#include "../FileUtil.h"
#include "../Log.h"

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
	
	spdlog::info("Looking for profiles...");

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
				spdlog::info("    Found profile '{}'", GameDir.path().string());
				break;
			}
		}
	}

	return Found;
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