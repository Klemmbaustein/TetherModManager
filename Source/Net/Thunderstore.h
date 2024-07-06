#pragma once
#include <string>
#include <vector>
#include <ctime>

namespace TsAPI
{
	struct ModInfo
	{
		std::string Name;
		std::string Author;
		std::string Description;
		std::string MarkdownDescription;
		// Mod URL if not a local mod.
		std::string ModPath;
		std::string ImagePath;
		std::string ModVersion;
		bool LocalMod = false;

		std::time_t Created = 0;
		std::time_t LastChanged = 0;

		int Downloads = 0;
		int Ratings = 0;

		bool IsInstalled();

		void Install();
		void UnInstall();

		std::string GetMarkdownDescription();
	};

	std::vector<ModInfo> GetOnlineMods();
}