#include <KlemmUI/Application.h>
#include <KlemmUI/Window.h>

#include "ui/MainElement.hpp"
namespace kui = KlemmUI;

int main()
{
	kui::Application::Initialize("app/shaders");

	kui::Window appWindow = kui::Window("KlemmUI Project Template", kui::Window::WindowFlag::Resizable);
	appWindow.Markup.SetDefaultFont(new kui::Font("app/fonts/IBMPlexSans-Medium.ttf"));

	auto appElement = new MainElement();
	appElement->SetMessage("Hello, World!");

	while (appWindow.UpdateWindow())
	{
	}

	return 0;
}

int WinMain()
{
	return main();
}
