#pragma once
#include "Domain.h"
#include "Repository.h"

class ActiuneUndo //clasa abstracta
{
public:
	virtual void doUndo() = 0; //metoda abstracta
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo
{
private:
	Masina masinaAdaugata;
	Repository& repo;

public:
	UndoAdauga(Repository& rep, const Masina& m) noexcept : repo{ rep }, masinaAdaugata{ m }{}

	void doUndo() override
	{
		repo.stergeMasina(masinaAdaugata);
	}

};

class UndoSterge : public ActiuneUndo
{
private:
	Masina masinaStearsa;
	Repository& repo;
public:
	UndoSterge(Repository& rep, const Masina& m) noexcept : repo{ rep }, masinaStearsa{ m }{}

	void doUndo() override
	{
		repo.adaugaMasina(masinaStearsa);
	}
};

class UndoModifica : public ActiuneUndo
{
private:
	Masina masinaModificata;
	Repository& repo;

public:
	UndoModifica(Repository& rep, const Masina& m) noexcept : repo{ rep }, masinaModificata{ m }{}

	void doUndo() override
	{
		repo.modificaMasina(masinaModificata);
	}
};