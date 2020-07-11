#pragma once
#pragma once
#include <string>
#include "Domain.h"
#include <vector>

using std::vector;

class ServiceManager
{
	vector<Masina> cos;

public:

	ServiceManager() = default;

	/* Nu permit copierea service-ului */
	ServiceManager(const ServiceManager& other) = delete;

	/* Metoda goleste lista entitatilor */
	void srv_golire_lista() noexcept;

	/* Metoda creeaza o masina, iar daca este valida se incearca adaugarea in Repository */
	void srv_adauga_masina(const Masina& m);

	/* Metoda preia numarul de masini din repository */
	int srv_numar_masini() const noexcept;

	/* Metoda genereaza random masini si le adauga in lista */
	void srv_generare_lista(size_t numar_masini, vector<Masina> lista_masini);

	const vector<Masina>& cos_manager();
};