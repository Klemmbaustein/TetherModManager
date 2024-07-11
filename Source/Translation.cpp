#include "Translation.h"
#include "FileUtil.h"
#include <nlohmann/json.hpp>
#include "Log.h"
#include <fstream>
#include <cstdarg>
#include "UI/Tabs/SettingsTab.h"

using namespace nlohmann;

static json TranslationFile;
static std::string LoadedTranslation = "English";

std::string Translate(std::string str)
{
	if (!TranslationFile.contains(str) || !TranslationFile.at(str).is_string())
	{
		return str;
	}
	return TranslationFile.at(str);
}

std::string TranslateFormat(std::string str, ...)
{
	str = Translate(str);
	int Size = (int)str.size() + 50, NewSize = Size;
	char* Buffer = nullptr;
	do
	{
		Size = NewSize;
		if (Buffer)
		{
			delete[] Buffer;
		}
		Buffer = new char[Size](0);
		va_list va;
		va_start(va, str);
		NewSize = vsnprintf(Buffer, Size, str.c_str(), va);
		va_end(va);

	} while (NewSize > Size);


	std::string StrBuffer = Buffer;
	delete[] Buffer;
	return StrBuffer;
}

static std::string GetTranslationFile(std::string TranslationName)
{
	std::vector<std::string> Found;
	for (const auto& i : std::filesystem::directory_iterator("app/translation"))
	{
		try
		{
			if (json::parse(FileUtil::ReadFile(i.path().string()), nullptr, true, true).at("name") == TranslationName)
			{
				return i.path().string();
			}
		}
		catch (json::exception&)
		{
		}
	}
	return "";
}


void LoadTranslation(std::string Name)
{
	LoadedTranslation = Name;
	try
	{
		spdlog::info("Loading translation JSON for language: '{}'", Name);
		TranslationFile = json::parse(FileUtil::ReadFile(GetTranslationFile(Name)), nullptr, true, true);
	}
	catch (json::exception& e)
	{
		spdlog::error("Failed to parse JSON file for language '{}': Error: {}", Name, e.what());
	}
}

void LoadDefaultTranslation()
{
	std::string Language = SettingsTab::GetSettingString("language");
	if (Language.empty())
	{
		Language = "English";
	}

	LoadTranslation(Language);
}
