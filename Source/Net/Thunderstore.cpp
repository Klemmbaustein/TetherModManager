#include "Thunderstore.h"
#include "Net.h"
#include <nlohmann/json.hpp>
#include "../Log.h"
#include "../FileUtil.h"

using namespace nlohmann;

namespace TsAPI
{
	static const std::string TargetUrl = "https://thunderstore.io/c/northstar/";
}

bool TsAPI::ModInfo::IsInstalled()
{
	return false;
}

void TsAPI::ModInfo::Install()
{
}

void TsAPI::ModInfo::UnInstall()
{
}

std::string TsAPI::ModInfo::GetMarkdownDescription()
{
	if (!MarkdownDescription.empty())
	{
		return MarkdownDescription;
	}

	if (LocalMod)
	{
		MarkdownDescription = FileUtil::ReadFile(ModPath + "/README.md");
		return MarkdownDescription;
	}

	// I'm using the experimental API here because there doesn't seem to be another way to do this.
	// If any of this fails, (as it probably will), it shouldn't matter that much.
	// It will fall back to the short description otherwise.
	try
	{
		auto Response = json::parse(Net::Get("https://thunderstore.io/api/experimental/frontend/c/northstar/p/"
			+ Author
			+ "/"
			+ Name
			+ "/"));
		MarkdownDescription = Response.at("markdown");
		return MarkdownDescription;
	}
	catch (json::exception e)
	{
		Log::Net->warn("Failed to get markdown description for mod {}", Name);
	}
	return Description;
}

static std::time_t ParseTimePoint(std::string TimePointString)
{
	std::tm tm;
	std::stringstream ss(TimePointString);
	ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
	return std::mktime(&tm);
}

std::vector<TsAPI::ModInfo> TsAPI::GetOnlineMods()
{
	auto PackagesJson = json::parse(Net::Get(TargetUrl + "api/v1/package"));

	Log::Net->info("Found {} mods on {}", PackagesJson.size(), TargetUrl);

	std::vector<ModInfo> Mods;

	for (const json& Mod : PackagesJson)
	{
		if (Mod.at("is_pinned"))
		{
			continue;
		}

		const json& LatestVersion = Mod.at("versions")[0];

		int Downloads = 0;

		for (const auto& Version : Mod.at("versions"))
		{
			Downloads += Version.at("downloads").get<int>();
		}

		Mods.push_back(ModInfo{
			.Name = Mod.at("name"),
			.Author = Mod.at("owner"),
			.Description = LatestVersion.at("description"),
			.ModPath = Mod.at("package_url"),
			.ImagePath = LatestVersion.at("icon"),
			.ModVersion = LatestVersion.at("version_number"),
			.Created = ParseTimePoint(Mod.at("date_created")),
			.LastChanged = ParseTimePoint(LatestVersion.at("date_created")),
			.Downloads = Downloads,
			.Ratings = Mod.at("rating_score"),
			});
	}

	return Mods;
}
