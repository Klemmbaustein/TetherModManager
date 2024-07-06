#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace Game::Profile
{
	struct ProfileInfo
	{
		std::filesystem::path ProfilePath;
		std::string DisplayName;
	};

	std::vector<ProfileInfo> GetAllProfiles();

	void Init();

	extern ProfileInfo Current;
}