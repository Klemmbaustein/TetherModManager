#include "Launch.h"
#include "Game.h"
#include "../Log.h"

#if _WIN32
#include <Windows.h>

static void LaunchGame_Impl(std::string Args)
{
	std::string GamePath = Game::GetGameLocation();
	GamePath.append("/NorthstarLauncher.exe");

	spdlog::info("Launching game. Executable: '{}'", GamePath);

	STARTUPINFOA Startup;
	PROCESS_INFORMATION pi;
	ZeroMemory(&Startup, sizeof(Startup));
	Startup.cb = sizeof(Startup);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcessA(GamePath.c_str(),
		(LPSTR)(" -profile=\""
			"R2Northstar"
			"\" "
			+ Args
			).c_str(),
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&Startup,
		&pi);

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

#else

static void LaunchGame_Impl(std::string Args)
{
	// 1 full rewrite of this software later, still untested.
	std::string Command = "steam://run/1237970/-northstar -profile=\\\""
		"R2Northstar"
		"\\\" "
		+ Args;

	system(("xdg-open \"" + Command + "\"").c_str());
}

#endif

void Game::Launch::LaunchGame(std::string Args)
{
	LaunchGame_Impl(Args);
}
