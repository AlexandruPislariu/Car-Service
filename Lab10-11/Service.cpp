#include "Service.h"
#include "Exceptii.h"
#include <algorithm>
#include <fstream>
#include <exception>

void Service::srv_adauga(const string& nr_inmatriculare, const string& producator, const string& model, const string& tip)
{
	Masina m{ nr_inmatriculare,producator,model,tip };
	if (validare_masina(m))
	{
		this->repo.adaugaMasina(m);
		undoActions.push_back(std::make_unique<UndoAdauga>(repo, m));
	}

}

void Service::srv_sterge(const string& nr_inmatriculare)
{
	Masina m{ nr_inmatriculare,"Dacia","Logan","Sedan" };
	if (validare_masina(m))
	{	
		m = repo.cautaMasina(m);
		this->repo.stergeMasina(m);
		undoActions.push_back(std::make_unique<UndoSterge>(repo, m));
	}
}

void Service::srv_modifica(const string& nr_inmatriculare, const string& producator, const string& model, const string& tip)
{
	Masina m{ nr_inmatriculare,producator,model,tip };
	if (validare_masina(m))
	{
		Masina masinaNemodificata = repo.cautaMasina(m);
		this->repo.modificaMasina(m);
		undoActions.push_back(std::make_unique<UndoModifica>(repo, masinaNemodificata));
	}
}

Masina Service::srv_cauta(const string& nr_inmatriculare)
{
	Masina m{ nr_inmatriculare,"Dacia","Logan","Sedan" };
	validare_masina(m);

	Masina m_cauta = repo.cautaMasina(m);
	if (m_cauta.getNrInmatriculare() == "") /* masina nu se afla in lista */
		throw RepoException("Masina nu se afla in lista!\n");

	return m_cauta;

}

vector<Masina> Service::srv_filtrare(const string& producator)
{
	const vector<Masina>& lista_masini = repo.getAll();
	vector<Masina> masini_producator;
	copy_if(lista_masini.begin(), lista_masini.end(), back_inserter(masini_producator), [=](const Masina& m) {return m.getProducator() == producator; });


	return masini_producator;
}

vector<Masina> Service::srv_sortare_numar()
{
	vector<Masina> lista_masini = repo.getAll();/* nu pot lucra cu adrese ale variabilelor locale */

	sort(lista_masini.begin(), lista_masini.end(), [=](const Masina& m1, const Masina& m2) {return m1.getNrInmatriculare() < m2.getNrInmatriculare(); });
	return lista_masini;
}
vector<Masina> Service::srv_sortare_producator()
{
	vector<Masina> lista_masini = repo.getAll();
	sort(lista_masini.begin(), lista_masini.end(), [=](const Masina& m1, const Masina& m2) {return m1.getProducator() < m2.getProducator(); });

	return lista_masini;
}
vector<Masina> Service::srv_getAll()
{
	return repo.getAll();
}

void Service::addToCos(const std::string& numar_inmatriculare)
{
	notify();
	Masina m{ numar_inmatriculare,"Dacia","Logan","Sedan" };
	validare_masina(m);

	Masina m_cauta = repo.cautaMasina(m);
	if (m_cauta.getNrInmatriculare() == "") /* masina nu se afla in lista */
		throw RepoException("Masina nu se afla in lista!\n");

	cos.srv_adauga_masina(m_cauta);
	notify();
}

void Service::addRandom(size_t cate)
{	
	cos.srv_golire_lista();
	cos.srv_generare_lista(cate, repo.getAll());
	notify();
}

void Service::golesteCos() noexcept
{	
	cos.srv_golire_lista();
	notify();
}

const int Service::toateDinCos() noexcept
{	
	return cos.srv_numar_masini();
}

const vector<Masina>& Service::continutCos() noexcept
{	
	return cos.cos_manager();
}

void Service::exportaCosCVS(string nume_fisier) const
{
	std::ofstream fisier;
	fisier.open(nume_fisier);

	const vector<Masina>& lista = repo.getAll();

	for (const auto& iterator : lista)
		fisier << iterator.getNrInmatriculare() << "," << iterator.getProducator() << "," << iterator.getModel() << "," << iterator.getTip() << '\n';

	fisier.close();
}

void Service::undo()
{
	if (undoActions.empty())
		throw RepoException("Nu se poate face undo! \n");

	undoActions.back()->doUndo();
	undoActions.pop_back();
}