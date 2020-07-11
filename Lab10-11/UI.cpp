#include "UI.h"
#include "Exceptii.h"
#include <iostream>
#include <string>

using std::string;
using namespace std;

void UI::ui_adauga()
{
	string nr_inmatriculare;
	string producator;
	string model;
	string tip;

	cout << "Introduceti datele masinii: \n";
	cout << "Inroduceti numar inmatriculare:";
	cin >> nr_inmatriculare;

	cout << "Introduceti producator: ";
	cin >> producator;

	cout << "Introduceti model: ";
	cin >> model;

	cout << "Inroduceti tip: ";
	cin >> tip;

	try {
		srv.srv_adauga(nr_inmatriculare, producator, model, tip);
	}
	catch (const RepoException & exceptie)
	{
		cout << exceptie.getMessage();
	}
}

void UI::ui_afisare()
{
	const vector<Masina>& lista = srv.srv_getAll();

	for (auto M : lista)
		cout << M << '\n';
}

void UI::ui_sterge()
{
	string nr_inmatriculare;
	cout << "Introduceti datele masinii: \n";
	cout << "Inroduceti numar inmatriculare:";
	cin >> nr_inmatriculare;

	try {
		srv.srv_sterge(nr_inmatriculare);
	}
	catch (const RepoException & exceptie)
	{
		cout << exceptie.getMessage();
	}
}

void UI::ui_modifica()
{
	string nr_inmatriculare;
	string producator;
	string model;
	string tip;

	cout << "Introduceti datele masinii: \n";
	cout << "Inroduceti numar inmatriculare:";
	cin >> nr_inmatriculare;

	cout << "Introduceti producator: ";
	cin >> producator;

	cout << "Introduceti model: ";
	cin >> model;

	cout << "Inroduceti tip: ";
	cin >> tip;

	try {
		srv.srv_modifica(nr_inmatriculare, producator, model, tip);
	}
	catch (const RepoException & exceptie)
	{
		cout << exceptie.getMessage();
	}
}

void UI::ui_cauta()
{
	string nr_inmatriculare;
	cout << "Introduceti datele masinii: \n";
	cout << "Inroduceti numar inmatriculare:";
	cin >> nr_inmatriculare;
	try
	{
		Masina m = srv.srv_cauta(nr_inmatriculare);
		cout << m << '\n';
	}
	catch (const RepoException & exceptie)
	{
		cout << exceptie.getMessage();
	}
}

void UI::ui_filtrare()
{
	string producator;
	cout << "Introduceti producatorul: ";
	cin >> producator;

	cout << "Masinile producatorului: \n";
	const vector<Masina>& masini_producator = srv.srv_filtrare(producator);
	for (auto M : masini_producator)
		cout << M << '\n';
}

void UI::ui_sortare()
{
	cout << "Masinile sortate: \n";
	const vector<Masina>& masini_sortate = srv.srv_sortare_numar();
	for (auto M : masini_sortate)
		cout << M << '\n';

}

void UI::ui_adauga_manager()
{
	std::string nr_inmatriculare;

	std::cout << "Introduceti datele masinii: \n";
	std::cout << "Inroduceti numar inmatriculare:";
	std::cin >> nr_inmatriculare;

	try
	{
		srv.addToCos(nr_inmatriculare);
	}
	catch (const RepoException & repoEx)
	{
		cout << repoEx.getMessage();
	}
}

void UI::ui_goleste_manager() noexcept
{
	srv.golesteCos();
}

void UI::ui_generate_random()
{
	int numarMasini;
	std::cout << "Introduceti numarul de masini: ";
	std::cin >> numarMasini;

	srv.addRandom(numarMasini);
}

void UI::ui_afisare_cos()
{
	cout << "Numarul de masini din lista managerului: ";
	cout << srv.toateDinCos() << '\n';

	cout << "Lista managerului: \n";
	const vector<Masina>& cos_manager = srv.continutCos();
	for (const auto& it : cos_manager)
		cout << it << '\n';

	cout << '\n';
}

void UI::ui_export()
{
	string nume_fisier;
	cout << "Introduceti numele fisierului: ";
	cin >> nume_fisier;

	nume_fisier = "./" + nume_fisier + ".csv";
	srv.exportaCosCVS(nume_fisier);
}

void UI::ui_undo()
{
	try
	{
		srv.undo();
	}
	catch (const RepoException & exceptie)
	{
		cout << exceptie.getMessage();
	}
}

void UI::panou_comenzi()
{
	cout << "Comenzile disponibile ale aplicatie: \n";
	cout << "1 : Adaugarea unei masini noi \n";
	cout << "2 : Tiparirea masinilor existente \n";
	cout << "3 : Stergerea unei masini \n";
	cout << "4 : Modificarea unei masini \n";
	cout << "5 : Cautarea unei masini \n";
	cout << "6 : Filtrare lista \n";
	cout << "7 : Sortare lista \n";
	cout << "8 : Adauga in lista managerului \n";
	cout << "9 : Goleste lista managerului \n";
	cout << "10 : Genereaza random lista managerului \n";
	cout << "11 : Exporta lista managerului intr-un fisier csv \n";
	cout << "12 : Undo \n";
}

void UI::run()
{
	while (true)
	{
		int cmd = 0;
		cout << "Introduceti comanda dorita! ";
		cin >> cmd;

		switch (cmd)
		{
		case 0:
			cout << "Aplicatia a fost inchisa cu succes!";
			return;

		case 1:
			UI::ui_adauga();
			break;

		case 2:
			UI::ui_afisare();
			break;

		case 3:
			UI::ui_sterge();
			break;

		case 4:
			UI::ui_modifica();
			break;

		case 5:
			UI::ui_cauta();
			break;

		case 6:
			UI::ui_filtrare();
			break;

		case 7:
			UI::ui_sortare();
			break;

		case 8:
			UI::ui_adauga_manager();
			break;

		case 9:
			UI::ui_goleste_manager();
			break;

		case 10:
			UI::ui_generate_random();
			break;

		case 11:
			UI::ui_export();
			break;

		case 12:
			UI::ui_undo();
			break;
		}

		UI::ui_afisare_cos();
	}
}