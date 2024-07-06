#pragma once
#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include "../Net/Thunderstore.h"

namespace Game::Mods
{
	enum class ModFiltering
	{
		Installed,
		Latest,
		LastChanged,
		MostDownloaded,
		TopRated
	};

	extern std::array<std::string, 5> FilteringStrings;

	std::vector<TsAPI::ModInfo> GetAllMods(ModFiltering Filter);
}