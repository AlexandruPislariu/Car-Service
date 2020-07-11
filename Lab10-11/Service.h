#pragma once
#include "Repository.h"
#include "Valid.h"
#include <string>
#include "Domain.h"
#include "ServiceManager.h"
#include "Undo.h"
#include "Observer.h"

using std::string;
using std::unique_ptr;

class Service:public Observable
{
private:

	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	Repository& repo;
	ServiceManager cos;

public:
	/* Construiesc un service */
	Service(Repository& repo)noexcept :repo{ repo } {}

	Service(Service& ot) = delete;/* nu permit copierea service-ului */
	Service() = default;

	/* Functia valideaza masina introdusa de utilizator,iar daca este valida o adauga in repository */
	void srv_adauga(const string& nr_inmatriculare, const string& producator, const string& model, const string& tip);

	/* Functia valideaza numarul de inmatriculare introdus,iar daca este valid se incearca stergerea din repository */
	void srv_sterge(const string& nr_inmatriculare);

	/* Functia valideaza masina introdusa de utilizator,iar daca este valida se incearca modificarea din repository */
	void srv_modifica(const string& nr_inmatriculare, const string& producator, const string& model, const string& tip);

	/*
		Functia valideaza numarul de inmatriculare introdus,iar daca este valid se incearca cautarea in repository
		Daca masina este gasita, se returneaza
	*/
	Masina srv_cauta(const string& nr_inmatriculare);

	/*
		Functia preia toate masinile care au ca producator parametrul transmis de utilizator
	*/
	vector<Masina> srv_filtrare(const string& producator);

	/*
		Functia sorteaza lista masinilor crescator in functie de numarul de inmatriculare
	*/
	vector<Masina> srv_sortare_numar();
	vector<Masina> srv_sortare_producator();

	/* Functia preia din repository lista masinilor care pot fi inchiriate*/
	vector<Masina> srv_getAll();

	void addToCos(const std::string& numar_inmatriculare);

	void addRandom(size_t cate);

	void golesteCos() noexcept;

	const int toateDinCos() noexcept;

	const vector<Masina>& continutCos() noexcept;

	void exportaCosCVS(std::string fName) const;

	void undo();
};