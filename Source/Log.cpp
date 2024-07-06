#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/hourly_file_sink.h>
#include "spdlog/pattern_formatter.h"
#include "BackgroundTask.h"

std::shared_ptr<spdlog::logger> Log::Main = nullptr;
std::shared_ptr<spdlog::logger> Log::UI = nullptr;
std::shared_ptr<spdlog::logger> Log::Net = nullptr;

class BackgroundTaskFlag : public spdlog::custom_flag_formatter
{
public:
    void format(const spdlog::details::log_msg&, const std::tm&, spdlog::memory_buf_t& dest) override
    {
        std::string TaskName = BackgroundTask::GetCurrentTaskName();
        dest.append(TaskName.data(), TaskName.data() + TaskName.size());
    }

    std::unique_ptr<custom_flag_formatter> clone() const override
    {
        auto New = spdlog::details::make_unique<BackgroundTaskFlag>();
        return New;
    }
};


void Log::Init()
{
    const char* LogFormat = "[%H:%M:%S] [%n] [Thread/%*] [%^%l%$] %v";

    auto StdOutFormatter = std::make_unique<spdlog::pattern_formatter>();
    StdOutFormatter->add_flag<BackgroundTaskFlag>('*').set_pattern(LogFormat);

    std::shared_ptr<spdlog::sinks::sink> StdOutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    StdOutSink->set_formatter(std::move(StdOutFormatter));

    auto LogFileFormatter = std::make_unique<spdlog::pattern_formatter>();
    LogFileFormatter->add_flag<BackgroundTaskFlag>('*').set_pattern(LogFormat);
    auto LogSink = std::make_shared<spdlog::sinks::hourly_file_sink_mt>("app/saved/logs/tether.txt", true);
    LogSink->set_formatter(std::move(LogFileFormatter));

	Main = std::make_shared<spdlog::logger>("Main", spdlog::sinks_init_list{StdOutSink, LogSink});
	UI = std::make_shared<spdlog::logger>("UI  ", spdlog::sinks_init_list{ StdOutSink, LogSink });
	Net = std::make_shared<spdlog::logger>("Net ", spdlog::sinks_init_list{ StdOutSink, LogSink });
	spdlog::set_default_logger(Main);
}
