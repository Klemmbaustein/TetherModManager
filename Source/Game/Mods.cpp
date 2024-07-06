#include "Mods.h"
#include <algorithm>
#include "../Log.h"
#include "Game.h"
#include "Profile.h"
#include <filesystem>

using namespace Game::Mods;

std::array<std::string, 5> Game::Mods::FilteringStrings = {
	"mods_filtering_installed",
	"mods_filtering_latest",
	"mods_filtering_last_changed",
	"mods_filtering_most_downloaded",
	"mods_filtering_top_rated"
};

std::vector<TsAPI::ModInfo> Game::Mods::GetAllMods(ModFiltering Filter)
{
	if (Filter == ModFiltering::Installed)
	{
		std::filesystem::path ProfileDir = Profile::Current.ProfilePath;

		if (!std::filesystem::exists(ProfileDir / "packages"))
		{
			return {};
		}

		std::vector<TsAPI::ModInfo> InstalledMods;

		for (const auto& i : std::filesystem::directory_iterator(ProfileDir / "packages"))
		{
			if (!std::filesystem::is_directory(i))
			{
				continue;
			}

			std::string Filename = i.path().filename().string();

			size_t FirstMinus = Filename.find_first_of("-");
			size_t LastMinus = Filename.find_last_of("-");

			std::string Author = Filename.substr(0, FirstMinus);
			std::string Name = Filename.substr(FirstMinus + 1, LastMinus - FirstMinus - 1);
			std::string Version = Filename.substr(LastMinus);

			InstalledMods.push_back(TsAPI::ModInfo{
				.Name = Name,
				.Author = Author,
				.ModPath = i.path().string(),
				.ImagePath = i.path().string() + "/icon.png",
				.ModVersion = Version,
				.LocalMod = true,
				});
		}

		return InstalledMods;
	}

	std::vector<TsAPI::ModInfo> OnlineMods = TsAPI::GetOnlineMods();

	std::sort(OnlineMods.begin(), OnlineMods.end(),
		[Filter](TsAPI::ModInfo a, TsAPI::ModInfo b) 
		{
			switch (Filter)
			{
			default:
				return a.Name > b.Name;
			case ModFiltering::Latest:
				return std::difftime(a.Created, b.Created) > 0;
			case ModFiltering::LastChanged:
				return std::difftime(a.LastChanged, b.LastChanged) > 0;
			case ModFiltering::MostDownloaded:
				return a.Downloads > b.Downloads;
			case ModFiltering::TopRated:
				return a.Ratings > b.Ratings;
			}
		});

	return OnlineMods;
}
