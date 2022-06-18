#pragma once

#include <thread>
#include <vector>
#include <functional>


class Manager
{
private:

	static void Wrap(Manager* manufacturer, const std::function<void(void)>& func);

public:

	// TODO: make private
	unsigned short int workersWorking = 0;
	unsigned short int workersAmount;
	bool hasFreeWorker = false;

	std::vector<std::thread> factory;

	explicit Manager(const unsigned short int& amount = 0);

	static Manager& CreateAndDistribute(
		const std::function<void(void)>& func,
		const unsigned short int& amount = 0,
		const unsigned short int& departments = 1,
		const bool& shouldDetach = false
	);

	void Work(const std::function<void(void)>& func, const bool& shouldDetach = false);

	void WaitUntilAnyComplete();

	void WaitUntilComplete(const bool& waitForDetached = false);
};