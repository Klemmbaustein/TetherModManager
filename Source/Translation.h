#pragma once
#include <string>

std::string Translate(std::string str);
std::string TranslateFormat(std::string str, ...);
void LoadTranslation(std::string Name);
void LoadDefaultTranslation();