#include "ModsTab.h"
#include <filesystem>
#include <mutex>
#include <KlemmUI/UI/UIBackground.h>
#include <KlemmUI/Rendering/MarkdownRendering.h>
#include <KlemmUI/UI/UITextField.h>
#include "../Elements/ModEntry.hpp"
#include "../Elements/ModFilter.hpp"
#include "../Elements/ModPageButton.hpp"
#include "../Elements/ModInfoHeader.hpp"
#include "../Elements/AppButton.hpp"
#include "../../BackgroundTask.h"
#include "../../Log.h"
#include "../../Net/Net.h"
#include "../../Installer.h"
#include "../../Translation.h"
#include "../../StrUtil.h"

using namespace KlemmUI;

static std::mutex ImageLoadMutex;
static std::mutex DescriptionLoadMutex;

ModsTab::ModsTab()
	: AppTab("mods")
{
	TabBackground = new UIBackground(false, 0, 0.05f, Vector2f(1.5f, 0));

	TabBackground
		->SetOpacity(0.9f)
		->SetTryFill(true);

	TabBox
		->AddChild(TabBackground)
		->SetHorizontal(true)
		->SetHorizontalAlign(UIBox::Align::Centered);
	TabBox->UpdateElement();

	GenerateUI();

	LoadMods();
}

void ModsTab::Update()
{
	if (LoadNewImages)
	{
		while (!ModImages.empty())
		{
			std::string Image = DisplayedMods[ImageIndex].ImagePath;
			if (std::filesystem::exists(Image))
			{
				std::lock_guard Guard{ ImageLoadMutex };
				ModImages.front()->SetColor(1);
				ModImages.front()->SetUseTexture(true, Image);
				ImageIndex++;
				ModImages.pop();
			}
			else
			{
				break;
			}

		}
		LoadNewImages = false;
	}
	if (ContentBox->GetChildren().size())
	{
	}
}

void ModsTab::OnResized()
{
	if (!OnModPage)
	{
		GenerateModsList();
	}
	else
	{
		GenerateModPage(ModPageMod);
	}
}

void ModsTab::GenerateModPage(TsAPI::ModInfo Mod)
{
	ModPageMod = Mod;
	Log::UI->info("Displaying mod info for mod: {}", Mod.Name);
	OnModPage = true;

	TabBackground->DeleteChildren();

	auto* Header = new ModInfoHeader();
	Header->SetModName(StrUtil::GetPrettyName(Mod.Name));
	Header->SetModImage(Mod.ImagePath);
	Header->SetModDescription(Mod.Description);
	Header->SetModInfo(TranslateFormat("mods_page_info", Mod.Author.c_str(), Mod.Downloads, Mod.Ratings));
	Header->backButton->button->OnClickedFunction = [this]()
		{
			std::lock_guard Guard{ DescriptionLoadMutex };
			OnModPage = false;
			GenerateUI();
			GenerateModsList();
		};

	auto InstallButton = new AppButton();
	InstallButton->SetImage("app/images/download.png");
	InstallButton->SetText("Install");
	Header->actionsBox->AddChild(InstallButton);

	if (!Mod.ModPath.empty())
	{
		auto OpenInBrowser = new AppButton();
		OpenInBrowser->SetImage("app/images/open.png");
		OpenInBrowser->SetText("Open in browser");
		OpenInBrowser->button->OnClickedFunction = [Mod]()
			{
#if _WIN32
				system(("start " + Mod.ModPath).c_str());
#else
				system(("xdg-open " + Mod.ModPath + " &").c_str());
#endif
			};
		Header->actionsBox->AddChild(OpenInBrowser);
	}

	UIScrollBox* MarkdownBox = new UIScrollBox(false, 0, true);
	Header->UpdateElement();

	float MarkdownSize = TabBackground->GetUsedSize().X - 0.4f;

	Vector2f Size = Vector2f(MarkdownSize + 0.1f, 2 - Header->GetUsedSize().Y - 0.1f);

	new BackgroundTask(
		[this]()
		{
			std::lock_guard Guard{ DescriptionLoadMutex };
			if (!OnModPage)
			{
				return;
			}
			ModPageMod.GetMarkdownDescription();
		},
		[this, MarkdownBox]()
		{
			float MarkdownSize = TabBackground->GetUsedSize().X - 0.4f;

			KlemmUI::Markdown::MarkdownStyling Style;
			Style.Color = 1;
			Style.Width = MarkdownSize;
			Style.TextSize = 0.7f;
			Style.Text = AppUI::DefaultFont;
			Style.Code.BackgroundColor = 0;
			Style.Code.CodeText = AppUI::MonospaceFont;

			KlemmUI::Markdown::RenderMarkdown(ModPageMod.MarkdownDescription, MarkdownBox, Style);
			MarkdownBox->UpdateElement();
			MarkdownBox->GetScrollObject()->Percentage = 0;
			MarkdownBox->RedrawElement();
		}, 
		"GetMarkdownDescription");

	TabBackground->AddChild(Header);
	TabBackground->AddChild(MarkdownBox
		->SetPadding(0, 0, 0.15f, 0)
		->SetMinSize(Size)
		->SetMaxSize(Size));

}

void ModsTab::GenerateUI()
{
	if (OnModPage)
	{
		return;
	}

	TabBackground->DeleteChildren();
	ContentBox = new UIScrollBox(false, 0, true);

	UIBox* FilteringBox = new UIBox(true, 0);

	for (size_t i = 0; i < Game::Mods::FilteringStrings.size(); i++)
	{
		auto Filter = new ModFilter();
		Filter->SetText(Translate(Game::Mods::FilteringStrings[i]));
		Filter->SetColor(i == SelectedFiltering ? AppUI::HighlightColor : 1);

		Filter->button->OnClickedFunction = [this, i]()
			{
				CurrentPage = 0;
				SelectedFiltering = i;
				GenerateUI();
				LoadMods();
			};

		FilteringBox->AddChild(Filter);
	}

	UIBox* PageButtonsBox = new UIBox(true, 0);

	for (size_t i = 0; i < 10; i++)
	{
		auto Filter = new ModPageButton();
		Filter->SetText(std::to_string(i + 1));
		Filter->SetColor(i == CurrentPage ? AppUI::HighlightColor : 1);

		Filter->button->OnClickedFunction = [this, i]()
			{
				CurrentPage = i;
				GenerateUI();
				GenerateModsList();
			};

		PageButtonsBox->AddChild(Filter);
	}

	auto* SearchField = new UITextField(0, 0, AppUI::DefaultFont, nullptr);
	SearchField
		->SetText(ModsFilter)
		->SetHintText("Search")
		->SetTextSize(11)
		->SetTextSizeMode(UIBox::SizeMode::PixelRelative)
		->SetTryFill(true)
		->SetPadding(5)
		->SetPaddingSizeMode(UIBox::SizeMode::PixelRelative);

	SearchField->OnClickedFunction = [this, SearchField]()
		{
			ModsFilter = SearchField->GetText();
			GenerateModsList();
		};

	TabBackground
		->AddChild(FilteringBox)
		->AddChild(SearchField)
		->AddChild(ContentBox
			->SetTryFill(true))
		->AddChild(PageButtonsBox);

	TabBackground->GetAbsoluteParent()->UpdateElement();
}

void ModsTab::LoadMods()
{
	new BackgroundTask(
		[this]() {
			StopImageLoading = true;
			std::lock_guard Guard{ ImageLoadMutex };
			LoadedMods.clear();
			LoadedMods = Game::Mods::GetAllMods(Game::Mods::ModFiltering(SelectedFiltering));
		},

		[this]() {
			GenerateModsList();
		},
		
		"GetOnlineMods");
}

void ModsTab::LoadImages()
{
	new BackgroundTask(
		[this]() {
			LoadImagesAsync();
		}, nullptr, "LoadImagesAsync");
}

void ModsTab::LoadImagesAsync()
{
	std::filesystem::create_directories("app/temp");
	for (auto& i : DisplayedMods)
	{
		if (std::filesystem::exists(i.ImagePath))
		{
			continue;
		}

		std::string ImagePath = "app/temp/img_" + i.Name + ".png";

		if (!std::filesystem::exists(ImagePath))
		{
			Net::GetFile(i.ImagePath, ImagePath);
		}
		if (StopImageLoading)
		{
			return;
		}
		std::lock_guard Guard{ ImageLoadMutex };
		i.ImagePath = ImagePath;
		LoadNewImages = true;
	}
	LoadNewImages = true;
}

void ModsTab::GenerateModsList()
{
	ModImages = std::queue<UIBackground*>();
	ContentBox->DeleteChildren();
	ImageIndex = 0;
	LoadNewImages = false;

	UIBox* CurrentRow = new UIBox(true, 0);
	ContentBox->AddChild(CurrentRow);
	size_t it = 0;

	Vector2ui RowSize = Vector2ui::Max(
		Vector2ui((TabBackground->GetUsedSize() - UIBox::PixelSizeToScreenSize(Vector2f(0, 120), Installer::AppWindow))
			/ UIBox::PixelSizeToScreenSize(Vector2f(150, 210), Installer::AppWindow)),
		Vector2ui(2));

	if (ModsFilter.empty())
	{
		DisplayedMods = LoadedMods;
	}
	else
	{
		DisplayedMods.clear();
		std::string EffectiveFilter = StrUtil::Replace(ModsFilter, "_", "");
		EffectiveFilter = StrUtil::Replace(EffectiveFilter, " ", "");
		EffectiveFilter = StrUtil::Lower(EffectiveFilter);

		for (const auto& i : LoadedMods)
		{
			std::string EffectiveName = StrUtil::Replace(i.Name, "_", "");
			EffectiveName = StrUtil::Replace(EffectiveName, " ", "");
			EffectiveName = StrUtil::Lower(EffectiveName);

			if (EffectiveName.find(EffectiveFilter) != std::string::npos || StrUtil::Lower(i.Author).find(EffectiveFilter) != std::string::npos)
			{
				DisplayedMods.push_back(i);
			}
		}
	}

	DisplayedMods.erase(DisplayedMods.begin(), DisplayedMods.begin() + std::min(CurrentPage * RowSize.X * RowSize.Y, DisplayedMods.size()));

	if (DisplayedMods.size() > RowSize.X * RowSize.Y)
	{
		DisplayedMods.resize(RowSize.X * RowSize.Y);
	}

	Log::UI->info("Displaying {} mods...", DisplayedMods.size());

	for (const auto& i : DisplayedMods)
	{
		auto Entry = new ModEntry();
		Entry->SetName(StrUtil::GetPrettyName(i.Name));

		ModImages.push(Entry->image);
		CurrentRow->AddChild(Entry);

		if (std::filesystem::exists(i.ImagePath))
		{
			Entry->SetImage(i.ImagePath);
		}
		else
		{
			Entry->image->SetColor(0.15f);
		}

		Entry->button->OnClickedFunction = [this, &i]()
			{
				GenerateModPage(i);
			};

		it++;

		if (it >= RowSize.X)
		{
			CurrentRow = new UIBox(true, 0);
			ContentBox->AddChild(CurrentRow);
			it = 0;
		}
	}

	ContentBox->SetMaxSize(Vector2f(ContentBox->GetMaxSize().X, TabBackground->GetUsedSize().Y));
	StopImageLoading = false;
	LoadImages();
}
