#include "AppUI.h"
#include "../Log.h"
#include "../Installer.h"
#include "../Translation.h"
#include "Elements/SidebarButton.hpp"

#include "Tabs/LaunchTab.h"
#include "Tabs/ModsTab.h"
#include "Tabs/ProfileTab.h"
#include "Tabs/SettingsTab.h"

#include <KlemmUI/Rendering/Texture.h>
using namespace KlemmUI;

UIBox* AppUI::AppBackground = nullptr;
unsigned int AppUI::BackgroundImage = 0;
Sidebar* AppUI::AppSidebar = nullptr;
TitleBar* AppUI::AppTitleBar = nullptr;
KlemmUI::Font* AppUI::DefaultFont;
KlemmUI::Font* AppUI::MonospaceFont;
Vector3f AppUI::HighlightColor = Vector3f(0.3f, 0.4f, 1.0f);

void AppUI::Create()
{
	Log::UI->info("Loading UI");

	LoadBackgroundImage("app/images/default_background.png");

	Installer::AppWindow->OnResizedCallback = [](Window* win) {
		spdlog::info("Resized window to {}x{}px", win->GetSize().X, win->GetSize().Y);
		for (AppTab* i : AppTab::AllTabs)
		{
			i->OnResized();
		}
		};

	DefaultFont = new Font("app/fonts/Roboto.ttf");
	MonospaceFont = new Font("app/fonts/Roboto-Mono.ttf");
	Installer::AppWindow->Markup.SetDefaultFont(DefaultFont);

	Installer::AppWindow->IsAreaGrabbableCallback = [](KlemmUI::Window*) -> bool
		{
			return AppTitleBar->TitleElement->IsBeingHovered();
		};
	Installer::AppWindow->BorderColor = 0.5f;
	AppTitleBar = new TitleBar();

	new LaunchTab();
	new ModsTab();
	new ProfileTab();
	new SettingsTab();

	AppSidebar = new Sidebar();
}

void AppUI::Update()
{
	AppTab::UpdateAllTabs();
	AppSidebar->Update();
	AppTitleBar->Update();

}

void AppUI::LoadBackgroundImage(std::string Path)
{
	if (AppBackground)
	{
		delete AppBackground;
		Texture::UnloadTexture(BackgroundImage);
		AppBackground = nullptr;
	}

	Texture::TextureInfo Image = Texture::LoadTextureWithInfo(Path);

	Vector2f ImageSize = Vector2f(float(Image.Width) / float(Image.Height), 1) * 2.0f;

	if (ImageSize.X < 1)
	{
		ImageSize = ImageSize * ImageSize.X;
	}

	AppBackground = (new UIBox(true, -1))
		->SetMinSize(2)
		->SetMaxSize(2)
		->SetHorizontalAlign(UIBox::Align::Centered)
		->SetVerticalAlign(UIBox::Align::Centered)
		->AddChild((new UIBackground(true, ImageSize / -2.0f, 1, ImageSize))
			->SetUseTexture(true, Image.ID)
			->SetSizeMode(UIBox::SizeMode::AspectRelative));
}
