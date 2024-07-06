#include "Installer.h"
#include "UI/AppUI.h"
#include "Translation.h"
#include "Log.h"
#include "Game/Game.h"
#include "Game/Profile.h"
#include "BackgroundTask.h"

#include <KlemmUI/Application.h>

KlemmUI::Window* Installer::AppWindow = nullptr;

static void CreateWindow()
{
	using namespace Installer;
	using KlemmUI::Window;

	spdlog::info("Creating app window");

	KlemmUI::Application::Initialize("app/shaders");

	KlemmUI::Application::Error::SetErrorCallback([](std::string Message) {
		spdlog::error("Internal UI error: {}", Message);
		});

	AppWindow = new Window("Tether v2", Window::WindowFlag::Resizable);
	AppWindow->Markup.SetGetStringFunction([](std::string str) -> std::string {
		return Translate(str);
		});
}

int main()
{
	using namespace Installer;

	Log::Init();

	LoadTranslation("English");
	Game::GetGameLocation();
	Game::Profile::Init();

	CreateWindow();
	AppUI::Create();

	while (AppWindow->UpdateWindow())
	{
		AppUI::Update();
		BackgroundTask::UpdateTasks();
	}

	return 0;
}

int WinMain()
{
	return main();
}
