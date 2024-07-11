#include "Installer.h"
#include "UI/AppUI.h"
#include "Translation.h"
#include "Log.h"
#include "Game/Game.h"
#include "Game/Profile.h"
#include "BackgroundTask.h"
#include "WindowsFunctions.h"
#include "UI/Tabs/SettingsTab.h"

#include <KlemmUI/Application.h>

using KlemmUI::Window;

Window* Installer::AppWindow = nullptr;

static Window::WindowFlag GetWindowFlags()
{
	Window::WindowFlag Flags = Window::WindowFlag::Resizable;

	if (SettingsTab::GetSettingString("title_bar_style") == "setting_title_bar_custom")
	{
		Flags = Flags | Window::WindowFlag::Borderless;
	}

	return Flags;
}

static void CreateWindow()
{
	using namespace Installer;

	spdlog::info("Creating app window");

	KlemmUI::Application::Initialize("app/shaders");

	KlemmUI::Application::Error::SetErrorCallback([](std::string Message) {
		Windows::ErrorBox("Internal UI error: " + Message);
		});

	AppWindow = new Window("Tether v2", GetWindowFlags());
	AppWindow->Markup.SetGetStringFunction([](std::string str) -> std::string {
		return Translate(str);
		});
	AppWindow->SetMinSize(Vector2ui(800, 600));
}

int main()
{
	using namespace Installer;

	Log::Init();

	SettingsTab::LoadSettingsFile();
	LoadDefaultTranslation();
	Game::GetGameLocation();
	Game::Profile::Init();

	CreateWindow();
	AppUI::Create();

	do
	{
		AppUI::Update();
		BackgroundTask::UpdateTasks();
	} while (AppWindow->UpdateWindow());

	return 0;
}

int WinMain()
{
	return main();
}

void Installer::UpdateWindowStyle()
{
	AppWindow->SetWindowFlags(GetWindowFlags());

	if (AppUI::AppTitleBar)
	{
		AppUI::AppTitleBar->Visible = SettingsTab::GetSettingString("title_bar_style") == "setting_title_bar_custom";
	}
}
