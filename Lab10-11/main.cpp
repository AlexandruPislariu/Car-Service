#include "Teste.h"
#include "UI.h"
#include <iostream>
#include "Domain.h"
#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{	
	testAll();

	Repository repo;
	RepositoryFile repoFile{ "fisier_repo.txt" };
	Service srv{ repoFile };

	
	UI console{ srv };
	console.panou_comenzi();
	console.run();
	
	QApplication app(argc, argv);

	GUI consoleGUI{ srv };
	consoleGUI.show();

	return app.exec();
}
