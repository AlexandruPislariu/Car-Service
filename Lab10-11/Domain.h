#pragma once
#include <string>
#include <iostream>

using std::string;

class Masina
{
private:
	string nr_inmatriculare;
	string producator;
	string model;
	string tip;

public:
	/* Constructorul unei masini */
	Masina(string nrInmatriculare, string producator, string model, string tip) :nr_inmatriculare{ nrInmatriculare }, producator{ producator }, model{ model }, tip{ tip }{}

	/* Constructor default */
	Masina()
	{
		nr_inmatriculare = "";
		producator = "";
		model = "";
		tip = "";
	}

	/* Returneaza numarul de inmatriculare al masinii */
	string getNrInmatriculare() const;

	/* Returneaza producatorul masinii */
	string getProducator() const;

	/* Returneaza modelul masinii */
	string getModel() const;

	/* Returneaza tipul masinii */
	string getTip() const;

	friend std::ostream& operator<<(std::ostream& os, const Masina& m);

	string toString();
};