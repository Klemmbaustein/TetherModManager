#include "Game.h"

#if _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winreg.h>
#endif
#include <spdlog/spdlog.h>
#include <filesystem>

static bool IsValidTitanfallLocation(std::filesystem::path p)
{
	return std::filesystem::exists(p.string() + "/Titanfall2.exe") && std::filesystem::exists(p.string() + "/gameversion.txt");
}

#if _WIN32

static LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
{
	strValue = strDefaultValue;
	WCHAR szBuffer[512] = {};
	DWORD dwBufferSize = sizeof(szBuffer);
	ULONG nError;
	nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
	if (ERROR_SUCCESS == nError)
	{
		strValue = szBuffer;
	}
	return nError;
}

#endif

std::string Game::GetGameLocation()
{
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
			WideCharToMultiByte(CP_ACP, 0, GameDir.c_str(), -1, szTo, (int)GameDir.size(), NULL, NULL);
			UTF8GameDir = szTo;
			delete[] szTo;

			spdlog::info("Found Titanfall 2 in the Windows Registry: '{}'", UTF8GameDir);
			//SaveGameDir(UTF8GameDir);
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
