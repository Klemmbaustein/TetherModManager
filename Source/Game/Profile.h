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

		void Rename(std::string NewName);
	};

	std::vector<ProfileInfo> GetAllProfiles();

	void SetCurrent(ProfileInfo NewCurrent);
	void Init();

	extern ProfileInfo Current;
}