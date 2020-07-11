#include "Teste.h"
#include "Repository.h"
#include "Valid.h"
#include "Exceptii.h"
#include "Service.h"
#include <assert.h>
#include <fstream>
#include <algorithm>

void testAdaugare()
{
	Repository repo;
	Service serv{ repo };
	serv.srv_adauga("SV07HIZ", "Dacia", "Logan", "Sedan");
	assert(repo.getAll().size() == 1);
	try
	{
		serv.srv_adauga("SV07HIZ", "Dacia", "Logan", "Sedan");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void testStergere()
{
	Repository repo;
	Service serv{ repo };
	serv.srv_adauga("SV07HIZ", "Dacia", "Logan", "Sedan");
	serv.srv_sterge("SV07HIZ");
	assert(repo.getAll().empty());

	try
	{
		serv.srv_sterge("SV07HIZ");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void testModifica()
{
	Repository repo;
	Service serv{ repo };
	serv.srv_adauga("SV07HIZ", "Dacia", "Logan", "Sedan");
	serv.srv_modifica("SV07HIZ", "a", "a", "a");
	const vector<Masina>& masini = repo.getAll();
	assert(find_if(masini.begin(), masini.end(), [=](const Masina& m) {return m.getProducator() == "a"; }) != masini.end());
	assert(find_if(masini.begin(), masini.end(), [=](const Masina& m) {return m.getModel() == "a"; }) != masini.end());
	assert(find_if(masini.begin(), masini.end(), [=](const Masina& m) {return m.getTip() == "a"; }) != masini.end());

	try
	{
		serv.srv_modifica("SV97HIZ", "a", "a", "a");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

}

void testCauta()
{
	Repository repo;
	Service serv{ repo };
	Masina m{ "SV07HIZ", "Dacia", "Logan", "Sedan" };
	repo.adaugaMasina(m);
	assert(serv.srv_cauta("SV07HIZ").getNrInmatriculare() == m.getNrInmatriculare());

	try
	{
		m = serv.srv_cauta("SV97HIZ");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

}

void testGetAll()
{
	Repository repo;
	Service serv{ repo };
	Masina m{ "SV07HIZ", "Dacia", "Logan", "Sedan" };
	repo.adaugaMasina(m);
	const vector<Masina>& masini = serv.srv_getAll();
	assert(masini.size() == 1);

}
void testFiltrare()
{
	Repository repo;
	Service serv{ repo };
	Masina m1{ "SV08HIZ","Dacia","Logan","Sedan" };
	Masina m2{ "SV07HPZ","Dacia","Sandero","Sedan" };
	Masina m3{ "SV09HIZ","Dacia","Duster","SUV" };
	Masina m4{ "SV27HIZ","BMW","X6","SUV" };
	repo.adaugaMasina(m1);
	repo.adaugaMasina(m2);
	repo.adaugaMasina(m3);
	repo.adaugaMasina(m4);

	vector<Masina> masini_producator = serv.srv_filtrare("Dacia");
	assert(masini_producator.size() == 3);
	assert(find_if(masini_producator.begin(), masini_producator.end(), [=](const Masina& m) {return m.getNrInmatriculare() == m1.getNrInmatriculare(); }) != masini_producator.end());
	assert(find_if(masini_producator.begin(), masini_producator.end(), [=](const Masina& m) {return m.getNrInmatriculare() == m2.getNrInmatriculare(); }) != masini_producator.end());
	assert(find_if(masini_producator.begin(), masini_producator.end(), [=](const Masina& m) {return m.getNrInmatriculare() == m3.getNrInmatriculare(); }) != masini_producator.end());

	vector<Masina> masini_producator1 = serv.srv_filtrare("BMW");
	assert(masini_producator1.size() == 1);
	assert(find_if(masini_producator1.begin(), masini_producator1.end(), [=](const Masina& m) {return m.getNrInmatriculare() == m4.getNrInmatriculare(); }) != masini_producator1.end());


	vector<Masina> masini_producator2 = serv.srv_filtrare("Mercedes");
	assert(masini_producator2.empty());
}

void testSortare()
{
	Repository repo;
	Service serv{ repo };
	Masina m0{ "SV07HIZ","a","a","a" };
	Masina m1{ "SV08HIZ","Dacia","Logan","Sedan" };
	Masina m2{ "SV07HPZ","Dacia","Sandero","Sedan" };
	Masina m3{ "SV09HIZ","Dacia","Duster","SUV" };
	Masina m4{ "SV27HIZ","BMW","X6","SUV" };

	repo.adaugaMasina(m0);
	repo.adaugaMasina(m1);
	repo.adaugaMasina(m2);
	repo.adaugaMasina(m3);
	repo.adaugaMasina(m4);

	vector<Masina> masini_sortate = serv.srv_sortare_numar();
	assert(masini_sortate.size() == 5);
	assert(find_if(masini_sortate.begin(), masini_sortate.end(), [=](const Masina& m) {return m.getNrInmatriculare() == m0.getNrInmatriculare(); }) != masini_sortate.end());
	assert(find_if(masini_sortate.begin(), masini_sortate.end(), [=](const Masina& m) {return m.getNrInmatriculare() == m1.getNrInmatriculare(); }) != masini_sortate.end());
	assert(find_if(masini_sortate.begin(), masini_sortate.end(), [=](const Masina& m) {return m.getNrInmatriculare() == m2.getNrInmatriculare(); }) != masini_sortate.end());
	assert(find_if(masini_sortate.begin(), masini_sortate.end(), [=](const Masina& m) {return m.getNrInmatriculare() == m3.getNrInmatriculare(); }) != masini_sortate.end());
}

void testeValid()
{
	Masina m1{ "","Dacia","Logan","Sedan" };
	Masina m2{ "sadsa","","Logan","Sedan" };
	Masina m3{ "asda","Dacia","","Sedan" };
	Masina m4{ "asdsa","Dacia","Logan","" };
	Masina m5{ "asdsa","Dacia","Logan","sda" };

	try
	{
		validare_masina(m1);
		assert(false);
	}
	catch (ValidException&)
	{
		assert(true);
	}
	try
	{
		validare_masina(m2);
		assert(false);
	}
	catch (ValidException&)
	{
		assert(true);
	}
	try
	{
		validare_masina(m3);
		assert(false);
	}
	catch (ValidException&)
	{
		assert(true);
	}
	try
	{
		validare_masina(m4);
		assert(false);
	}
	catch (ValidException&)
	{
		assert(true);
	}

	assert(validare_masina(m5));
}

void testGolire()
{
	Repository repo;
	Service serv{ repo };

	Masina m1{ "SV07HIZ","Dacia","Logan","Sedan" };
	Masina m2{ "SV07HPZ","Dacia","Sandero","Sedan" };
	Masina m3{ "SV09HIZ","Dacia","Duster","SUV" };
	Masina m4{ "SV27HIZ","BMW","X6","SUV" };

	repo.adaugaMasina(m1);
	repo.adaugaMasina(m2);
	repo.adaugaMasina(m3);
	repo.adaugaMasina(m4);

	serv.addToCos("SV07HIZ");
	assert(serv.toateDinCos() == 1);

	serv.golesteCos();
	assert(serv.toateDinCos() == 0);
}

void testAdaugareManager()
{
	Repository repo;
	Service serv{ repo };

	Masina m1{ "SV07HIZ","Dacia","Logan","Sedan" };
	Masina m2{ "SV07HPZ","Dacia","Sandero","Sedan" };
	Masina m3{ "SV09HIZ","Dacia","Duster","SUV" };
	Masina m4{ "SV27HIZ","BMW","X6","SUV" };

	repo.adaugaMasina(m1);
	repo.adaugaMasina(m2);
	repo.adaugaMasina(m3);
	repo.adaugaMasina(m4);

	try
	{
		serv.addToCos("");
		assert(false);
	}
	catch (const ValidException&)
	{
		assert(true);
	}

	try
	{
		serv.addToCos("asdas");
		assert(false);
	}
	catch (const RepoException&)
	{
		assert(true);
	}

	serv.addToCos("SV07HIZ");
	assert(serv.toateDinCos() == 1);

	serv.addToCos("SV07HPZ");
	serv.addToCos("SV27HIZ");

	assert(serv.toateDinCos() == 3);
	assert(serv.continutCos().size() == 3);
}

void testGenerate()
{
	Repository repo;
	Service serv{ repo };

	Masina m1{ "SV07HIZ","Dacia","Logan","Sedan" };
	Masina m2{ "SV07HPZ","Dacia","Sandero","Sedan" };
	Masina m3{ "SV09HIZ","Dacia","Duster","SUV" };
	Masina m4{ "SV27HIZ","BMW","X6","SUV" };

	repo.adaugaMasina(m1);
	repo.adaugaMasina(m2);
	repo.adaugaMasina(m3);
	repo.adaugaMasina(m4);
	serv.addRandom(3);

	assert(serv.toateDinCos() == 3);

	serv.addToCos("SV09HIZ");

	assert(serv.toateDinCos() == 4);

}


void testExport()
{
	Repository repo;
	Service serv{ repo };

	Masina m1{ "SV07HIZ","Dacia","Logan","Sedan" };
	Masina m2{ "BC20ABP","BMW","X6","SUV" };

	repo.adaugaMasina(m1);
	repo.adaugaMasina(m2);

	serv.exportaCosCVS("test.csv");

	std::ifstream fisier("test.csv");

	const std::vector<Masina>& lista = repo.getAll();
	unsigned int line = 0;

	while (!fisier.eof())
	{
		std::string continut_linie;
		getline(fisier, continut_linie, '\n');
		Masina m = repo.read_no_comma(continut_linie);

		if (line < lista.size())
		{
			assert(m.getNrInmatriculare() == lista[line].getNrInmatriculare());
			assert(m.getProducator() == lista[line].getProducator());
			assert(m.getModel() == lista[line].getModel());
		}

		line++;
	}
	fisier.close();
}

void testeRepo()
{
	Repository repo;
	Masina m{ "SV07HIZ","Dacia","Logan","Sedan" };
	Masina m2{ "SV09HIZ","Dacia","Logan","Sedan" };
	Masina m3{ "SV07HIZ","Mercedes","CLS","Sedan" };

	/* Testez adaugarea unei masini */
	repo.adaugaMasina(m);
	assert(repo.getAll().size() == 1);
	try
	{
		repo.adaugaMasina(m);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	/* Testez cautarea unei masini */
	assert(repo.cautaMasina(m).getNrInmatriculare() == m.getNrInmatriculare());
	assert(repo.cautaMasina(m2).getNrInmatriculare() == "");

	/* Testez modificarea unei masini */
	repo.modificaMasina(m3);
	Masina m_cauta = repo.cautaMasina(m3);

	assert(m_cauta.getNrInmatriculare() == m3.getNrInmatriculare());

	try
	{
		repo.modificaMasina(m2);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	/* Testez stergerea unei masini  */
	try
	{
		repo.stergeMasina(m2);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	repo.adaugaMasina(m2);
	repo.stergeMasina(m3);
	assert(repo.getAll().size() == 1);

	repo.stergeMasina(m2);
}

void testeRepoFile()
{
	RepositoryFile repo{ "fisier_test.txt" };

	assert(repo.getAll().size() == 3);

	Masina m{ "SV12ABS","Dacia","Duster","SUV" };
	repo.adaugaMasina(m);
	assert(repo.getAll().size() == 4);

	Masina m1{ "SV12ABS","a","a","a" };
	repo.modificaMasina(m1);
	assert(repo.cautaMasina(m).getProducator() == "a");

	repo.stergeMasina(m);
	assert(repo.getAll().size() == 3);
}

void testUndo()
{
	Repository repo;
	Service serv{ repo };
	Masina m1{ "SV07HIZ","Dacia","Logan","Sedan" };
	Masina m2{ "SV09HIZ","Dacia","Logan","Sedan" };
	Masina m3{ "SV07HIZ","Mercedes","CLS","Sedan" };

	serv.srv_adauga("SV07HIZ", "Dacia", "Logan", "Sedan");
	assert(repo.getAll().size() == 1);
	serv.undo();
	assert(repo.getAll().size() == 0);

	serv.srv_adauga("SV07HIZ", "Dacia", "Logan", "Sedan");
	serv.srv_adauga("SV09HIZ", "Dacia", "Logan", "Sedan");
	assert(repo.getAll().size() == 2);
	serv.srv_sterge("SV07HIZ");
	assert(repo.getAll().size() == 1);
	serv.undo();
	assert(repo.getAll().size() == 2);

	serv.srv_modifica("SV07HIZ", "Mercedes", "CLS", "Sedan");
	assert(repo.cautaMasina(m3).getProducator() == "Mercedes");
	serv.undo();
	assert(repo.cautaMasina(m3).getProducator() == "Dacia");

	serv.undo();
	assert(repo.getAll().size() == 1);
	serv.undo();
	assert(repo.getAll().empty());

	try
	{
		serv.undo();
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

}
void testAll()
{
	testeRepo();
	testeRepoFile();
	testUndo();

	testAdaugare();
	testStergere();
	testModifica();
	testCauta();
	testGetAll();
	testFiltrare();
	testSortare();
	testeValid();


	testAdaugareManager();
	testGenerate();
	testGolire();
	testExport();


}