#pragma once
#include <spdlog/spdlog.h>
#include <memory>

namespace Log
{
	void Init();

	extern std::shared_ptr<spdlog::logger> Main;
	extern std::shared_ptr<spdlog::logger> UI;
	extern std::shared_ptr<spdlog::logger> Net;
}