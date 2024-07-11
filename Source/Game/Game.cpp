#include "Game.h"
#include "../WindowsFunctions.h"

#if _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winreg.h>
#endif
#include <spdlog/spdlog.h>
#include <filesystem>
#include "../Translation.h"
#include "../FileUtil.h"
#include <fstream>

namespace Game
{
	static std::string GameDir = "";
	static bool ShowedWriteProtectWarning = false;
	static std::string GamePathFile = "app/saved/game_path.txt";
}

void Game::SaveGameDir(std::string NewDir)
{
	GameDir = NewDir;

	std::ofstream PathFile = std::ofstream(GamePathFile);
	PathFile << GameDir;
	PathFile.close();
}

static bool IsValidTitanfallLocation(std::filesystem::path p)
{
	// Show an error if the game location is write-protected.
	// The default EA install location for games is write protected.
	if ((std::filesystem::status(p).permissions() & std::filesystem::perms::owner_write) != std::filesystem::perms::owner_write
		&& !Game::ShowedWriteProtectWarning)
	{
		Windows::ErrorBox(Translate("game_path_write_protected"));
		return false;
	}

	return std::filesystem::exists(p.string() + "/Titanfall2.exe") && std::filesystem::exists(p.string() + "/gameversion.txt");
}

#if _WIN32

static LONG GetStringRegKey(HKEY Key, const std::wstring& ValueName, std::wstring& Value, const std::wstring& DefaultValue)
{
	Value = DefaultValue;
	WCHAR Buffer[512] = {};
	DWORD BufferSize = sizeof(Buffer);
	ULONG Error;
	Error = RegQueryValueExW(Key, ValueName.c_str(), 0, NULL, (LPBYTE)Buffer, &BufferSize);
	if (ERROR_SUCCESS == Error)
	{
		Value = Buffer;
	}
	return Error;
}

#endif

std::string Game::GetGameLocation()
{
	if (!GameDir.empty())
	{
		return GameDir;
	}

	if (std::filesystem::exists(GamePathFile))
	{
		std::string FileContent = FileUtil::ReadFile(GamePathFile);

		if (IsValidTitanfallLocation(FileContent))
		{
			return FileContent;
		}
	}

#if _WIN32

	HKEY RegKey;
	LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Respawn\\Titanfall2", 0, KEY_READ, &RegKey);
	if (lRes == ERROR_SUCCESS)
	{
		std::wstring GameDir, GameDirDefault;
		LONG KeyResult = GetStringRegKey(RegKey, L"Install Dir", GameDir, GameDirDefault);
		if (KeyResult == ERROR_SUCCESS && IsValidTitanfallLocation(GameDir))
		{
			std::string UTF8GameDir;
			char* szTo = new char[GameDir.size() + 1];
			szTo[GameDir.size()] = '\0';
			WideCharToMultiByte(CP_UTF8, 0, GameDir.c_str(), -1, szTo, (int)GameDir.size(), NULL, NULL);
			UTF8GameDir = szTo;
			delete[] szTo;

			spdlog::info("Found Titanfall 2 in the Windows Registry: '{}'", UTF8GameDir);
			SaveGameDir(UTF8GameDir);
			return UTF8GameDir;
		}
	}
	else
	{
		spdlog::error("Cannot open reg key 'SOFTWARE\\Respawn\\Titanfall2'");
	}
#endif
	return "";
}
