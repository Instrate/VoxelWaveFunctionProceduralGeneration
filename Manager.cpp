#include "Manager.h"

#include <set>

Manager::Manager(const unsigned short int& amount) {
	workersAmount = amount == 0 ? std::thread::hardware_concurrency() : amount;
}

Manager& Manager::CreateAndDistribute(
	const std::function<void(void)>& func,
	const unsigned short int& amount,
	const unsigned short int& departments,
	const bool& shouldDetach
) {
	Manager manager(amount);
	unsigned short int size = manager.workersAmount;	
	unsigned short int shared_workers = size % departments;
	unsigned short int delta = departments;

	for (int i = 0; i < size; i += delta) {
		for (int j = 0; j < delta; j++) {
			manager.Work(func, shouldDetach);
		}
		if (i + delta > size) {
			delta = delta - 1;
		}
	}
	return manager;
}

void Manager::Wrap(
	Manager* manufacturer,
	const std::function<void(void)>& func
) {
	func();
	// use another method decrementer
	manufacturer->workersWorking--;
	manufacturer->hasFreeWorker = true;
}

void Manager::Work(const std::function<void(void)>& func, const bool& shouldDetach) {
	while (workersWorking == workersAmount);
	bool isWorkGiven = false;
	while (!isWorkGiven) {
		if (workersWorking < workersAmount) {
			factory.push_back(std::thread(Wrap, this, func));
			if (shouldDetach) {
				factory[factory.size() - 1].detach();
			}
			isWorkGiven = true;
		}
		else {
			WaitUntilAnyComplete();
		}
	}
	workersWorking++;
}

void Manager::WaitUntilAnyComplete() {
	bool hasJoinable = false;
	int ind;
	for (int i = 0; i < factory.size() && !hasJoinable; i++) {
		if (factory[i].joinable()) {
			hasJoinable = true;
			ind = i;
		}

	}
	if (hasJoinable) {
		factory[ind].join();
	}
	else {
		while (!hasFreeWorker);
	}
}

void Manager::WaitUntilComplete(const bool& waitForDetached) {

	std::set<int> indexesOfDetached;

	for (int i = 0; i < factory.size(); i++) {
		if (factory[i].joinable()) {
			factory[i].join();
		}
		else {
			indexesOfDetached.insert(i);
		}
	}

	if (waitForDetached) {
		while (workersWorking != 0);
		factory.clear();
	}
	else {
		std::vector<std::thread> factoryNew;
		factoryNew.resize(indexesOfDetached.size());
		int j = 0;
		for (const int& i : indexesOfDetached) {
			factoryNew[j] = std::move(factory[i]);
			j++;
		}
		factory = std::move(factoryNew);
	}
}