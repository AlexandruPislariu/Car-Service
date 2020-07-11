#pragma once
#include "Domain.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <string>

using std::vector;

class RepositoryAbstract
{
	/*
		friend class Repository;
	private:
		std::unordered_map <std::string, Masina> lista_masini;
	*/
public:

	RepositoryAbstract() = default;

	RepositoryAbstract(const RepositoryAbstract& ot) = delete;

	virtual ~RepositoryAbstract() = default;

	virtual void adaugaMasina(const Masina& masina_noua) = 0;
	virtual void stergeMasina(const Masina& masina_inchiriata) = 0;
	virtual void modificaMasina(const Masina& masina_inchiriata) = 0;
	virtual Masina cautaMasina(const Masina& masina_inchiriata) = 0;
	virtual vector<Masina> getAll() = 0;
};

class Repository : public RepositoryAbstract
{
private:
	std::unordered_map <std::string, Masina> lista_masini;

public:
	Repository() = default;

	Repository(const Repository& ot) = delete; /* nu permit sa se copieze repository */

	virtual ~Repository() = default;

	Masina read_no_comma(const std::string& line);
	/*
		Functia adauga o noua masina in lista masinilor date catre inchiriere
		Arunca exceptie daca masina se afla deja in lista
	*/
	void adaugaMasina(const Masina& masina_noua) override;

	/*
		Functia sterge o masina din lista masinilor date catre inchiriere
		Arunca exceptie daca masina nu se afla in lista
	*/
	void stergeMasina(const Masina& masina_inchiriata) override;

	/*
		Functia modifica o masina din lista masinilor date catre inchiriere
		Arunca exceptie daca masina nu se afla in lista
	*/
	void modificaMasina(const Masina& masina_existenta) override;

	/* Functia cauta o masina in lista masinilor date catre inchiriere
		Returneaza pozitia daca o gaseste sau -1 in sens contrar
	*/
	Masina cautaMasina(const Masina& masina_existenta) override;

	/* Functia returneaza lista masinilor care pot fi inchiriate*/
	vector<Masina> getAll() override;
};

class RepositoryFile : public Repository
{
private:
	std::string nume_fisier;
	void read_all_from_file();
	void write_all_in_file();

public:

	RepositoryFile(const std::string& fisier) : Repository(), nume_fisier{ fisier }
	{
		read_all_from_file();
	}

	void adaugaMasina(const Masina& m) override
	{
		Repository::adaugaMasina(m);
		write_all_in_file();
	}

	void stergeMasina(const Masina& m) override
	{
		Repository::stergeMasina(m);
		write_all_in_file();
	}

	void modificaMasina(const Masina& m) override
	{
		Repository::modificaMasina(m);
		write_all_in_file();
	}
};