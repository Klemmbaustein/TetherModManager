#pragma once
#include <atomic>
#include <string>
#include <thread>
#include <functional>
#include <vector>

struct BackgroundTask
{
	size_t Type = 0;
	std::atomic<float> Progress = 0;
	std::string Name;
	std::thread* Thread = nullptr;
	std::function<void()> Callback;
	// Will point to the task that is being executed right now.
	thread_local static BackgroundTask* ThisThreadPtr;

	BackgroundTask(std::function<void()> Function, std::function<void()> Callback = nullptr, std::string TaskName = "Unknown");
	BackgroundTask(const BackgroundTask&) = delete;
	~BackgroundTask();

	static void SetProgress(float Progress);
	static bool IsBackgroundTask();
	static void UpdateTasks();
	static std::string GetCurrentTaskName();

	static std::vector<BackgroundTask*> AllTasks;

private:
	static void TaskRun(std::function<void()> Function, BackgroundTask* Task);
};