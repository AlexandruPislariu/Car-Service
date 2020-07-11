#pragma once
#include "Service.h"

class UI
{
private:
	Service& srv;

public:
	UI(Service& srv) noexcept :srv{ srv } {}

	/* Functia tipareste panoul de comenzi */
	void panou_comenzi();

	/* Functia de pornire a aplicatiei */
	void run();

	/* Functia comunica cu utilizatorul pentru a adauga o masina */
	void ui_adauga();

	/* Functia tipareste lista masinilor care pot fi inchiriate */
	void ui_afisare();

	/* Functia comunica cu utilizatorul pentru a sterge o masina */
	void ui_sterge();

	/* Functia comunica cu utilizatorul pentru a modifica o masina */
	void ui_modifica();

	/* Functia comunica cu utilizatorul pentru a cauta o masina */
	void ui_cauta();

	/* Functia comunica cu utilizatorul pentru a filtra lista masinilor */
	void ui_filtrare();

	/* Functia comunica cu utilizatorul pentru a sorta crescator in functie de numarul de inmatriculare masinile */
	void ui_sortare();

	/* Metoda comunica cu managerul pentru a adauga o masina in cos */
	void ui_adauga_manager();

	/* Metoda comunica cu managerul pentru a goli cosul */
	void ui_goleste_manager() noexcept;

	/* Metoda comunica cu managerul pentru a adauga random masini in cos */
	void ui_generate_random();

	/* Metoda afiseaza cosul managerului */
	void ui_afisare_cos();

	/* Metoda exporta cosul intr-un fisier csv */
	void ui_export();

	/* Metoda reface ultima operatie */
	void ui_undo();
};