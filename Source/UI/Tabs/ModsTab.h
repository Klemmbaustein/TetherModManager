#pragma once
#include "AppTab.h"
#include <queue>
#include <KlemmUI/UI/UIScrollBox.h>
#include "../../Game/Mods.h"

class ModsTab : public AppTab
{
public:
	ModsTab();

	KlemmUI::UIScrollBox* ContentBox = nullptr;
	KlemmUI::UIBackground* TabBackground = nullptr;

	bool OnModPage = false;
	TsAPI::ModInfo ModPageMod;
	bool StopImageLoading = false;

	std::queue<KlemmUI::UIBackground*> ModImages;
	size_t ImageIndex = 0;
	size_t CurrentPage = 0;
	size_t SelectedFiltering = 0;
	std::string ModsFilter;
	std::vector<TsAPI::ModInfo> LoadedMods;
	std::vector<TsAPI::ModInfo> DisplayedMods;
	bool LoadNewImages = false;

	virtual void Update() override;
	virtual void OnResized() override;

	void GenerateModPage(TsAPI::ModInfo Mod);

	void GenerateUI();
	void LoadMods();
	void LoadImages();
	void LoadImagesAsync();
	void GenerateModsList();
};