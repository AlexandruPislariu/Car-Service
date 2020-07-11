#include "Domain.h"
#include <vector>
#include <functional>
#include <numeric>

string Masina::getNrInmatriculare() const
{
	return this->nr_inmatriculare;
}

string Masina::getProducator() const
{
	return this->producator;
}

string Masina::getModel() const
{
	return this->model;
}

string Masina::getTip() const
{
	return this->tip;
}

std::ostream& operator<<(std::ostream& os, const Masina& m)
{
	std::vector<string> vectorAfisare;
	vectorAfisare.push_back(m.getNrInmatriculare());
	vectorAfisare.push_back(m.getProducator());
	vectorAfisare.push_back(m.getModel());
	vectorAfisare.push_back(m.getTip());

	std::string linie_afisare = std::accumulate(vectorAfisare.begin(), vectorAfisare.end(), std::string{},
		[](std::string& linie, const std::string& piece) { return linie += piece + " "; });
	//os << m.getNrInmatriculare() << " " << m.getProducator() << " " << m.getModel() << " " << m.getTip();
	os << linie_afisare;
	return os;
}

string Masina::toString()
{
	string masinaStr = "";
	masinaStr += nr_inmatriculare + " " + producator + " " + model + " " + tip;
	return masinaStr;
}