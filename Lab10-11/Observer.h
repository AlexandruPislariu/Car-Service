#pragma once
#include <algorithm>
#include <vector>
using std::vector;

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
	vector<Observer*> interesati;

protected:
	void notify()
	{
		for (auto obs : interesati)
			obs->update();

	}

public:
	void addObserver(Observer* a)
	{
		interesati.push_back(a);

	}
	void removeObserver(Observer* a)
	{
		interesati.erase(std::remove(interesati.begin(), interesati.end(), a));
	}
};