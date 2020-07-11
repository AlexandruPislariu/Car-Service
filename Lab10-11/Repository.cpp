#include "Repository.h"
#include "Exceptii.h"
#include <exception>
#include <assert.h>
#include <fstream>
#include <iostream>

vector<Masina> Repository::getAll()
{
	vector <Masina> lista;
	for (const auto& iterator : lista_masini)
		lista.push_back(iterator.second);

	return lista;
}

Masina Repository::cautaMasina(const Masina& masina_existenta)
{
	auto iterator = lista_masini.find(masina_existenta.getNrInmatriculare());
	if (iterator != lista_masini.end())
		return iterator->second;

	return Masina("", "", "", "");
}

void Repository::adaugaMasina(const Masina& masina_noua)
{/* Verific daca masina se afla deja in lista */
	if (Repository::cautaMasina(masina_noua).getNrInmatriculare() != "") /* masina se afla in lista*/
		throw RepoException("Masina se afla deja in lista! \n");

	this->lista_masini.insert({ masina_noua.getNrInmatriculare(),masina_noua });
}

void Repository::stergeMasina(const Masina& masina_existenta)
{
	Masina m = Repository::cautaMasina(masina_existenta);
	if (m.getNrInmatriculare() == "") /* masina nu se afla in lista */
		throw RepoException("Masina nu exista! \n");
	else
		lista_masini.erase(m.getNrInmatriculare());
}

void Repository::modificaMasina(const Masina& masina_existenta)
{
	Masina m = Repository::cautaMasina(masina_existenta);
	if (m.getNrInmatriculare() == "") /* masina nu se afla in lista */
		throw RepoException("Masina nu exista! \n");

	lista_masini.at(m.getNrInmatriculare()) = masina_existenta;
}

Masina Repository::read_no_comma(const std::string& line)
{
	std::string nrI = "";
	std::string producator = "";
	std::string model = "";
	std::string tip = "";

	std::string cuvant = "";

	unsigned int iterator = 0;
	while (iterator < line.size())
	{
		if (line[iterator] != ',')
			cuvant += line[iterator];
		else
		{
			if (nrI == "")
				nrI = cuvant;
			else
				if (producator == "")
					producator = cuvant;
				else
					if (model == "")
						model = cuvant;
			cuvant.clear();
		}

		iterator++;
	}

	tip = cuvant;
	return Masina(nrI, producator, model, tip);
}

void RepositoryFile::read_all_from_file()
{

	std::ifstream in(nume_fisier);

	while (!in.eof())
	{
		std::string continut_linie;
		getline(in, continut_linie, '\n');
		Masina m = read_no_comma(continut_linie);

		if (m.getNrInmatriculare() != "")
			Repository::adaugaMasina(m);
	}

	in.close();
}

void RepositoryFile::write_all_in_file()
{
	std::ofstream out(nume_fisier);

	const std::vector<Masina>& lista = getAll();
	for (const auto& m : lista)
		out << m.getNrInmatriculare() << "," << m.getProducator() << "," << m.getModel() << "," << m.getTip() << '\n';

	out.close();
}