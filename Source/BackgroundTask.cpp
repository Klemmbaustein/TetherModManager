#include "BackgroundTask.h"
#include <cassert>
#include <iostream>
#include "Log.h"

thread_local BackgroundTask* BackgroundTask::ThisThreadPtr = nullptr;
std::vector<BackgroundTask*> BackgroundTask::AllTasks;

BackgroundTask::BackgroundTask(std::function<void()> Function, std::function<void()> Callback, std::string TaskName)
{
	AllTasks.push_back(this);
	this->Callback = Callback;
	this->Name = TaskName;

	Thread = new std::thread(TaskRun, Function, this);
}

BackgroundTask::~BackgroundTask()
{
	Thread->join();
	delete Thread;
}

void BackgroundTask::SetProgress(float Progress)
{
	assert(ThisThreadPtr);
	ThisThreadPtr->Progress = Progress;
}

void BackgroundTask::TaskRun(std::function<void()> Function, BackgroundTask* ThisTask)
{
	ThisThreadPtr = ThisTask;
	try
	{
		Function();
	}
	catch (std::exception& e)
	{
		spdlog::error("Background task {} failed: {}", ThisTask->Name, e.what());
	}
	ThisTask->Progress = 1;
}


bool BackgroundTask::IsBackgroundTask()
{
	return ThisThreadPtr;
}

void BackgroundTask::UpdateTasks()
{
	for (size_t i = 0; i < AllTasks.size(); i++)
	{
		if (AllTasks[i]->Progress >= 1)
		{
			auto Callback = AllTasks[i]->Callback;
			delete AllTasks[i];
			AllTasks.erase(AllTasks.begin() + i);
			if (Callback)
			{
				Callback();
			}
			break;
		}
	}
}

std::string BackgroundTask::GetCurrentTaskName()
{
	if (!IsBackgroundTask())
	{
		return "Main";
	}

	return ThisThreadPtr->Name;
}
