#pragma once
#include "Service.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qtableview.h>
#include "MyTableModel.h"
#include "Observer.h"
#include <qpainter.h>

class GUI : public QWidget
{	
	friend class GUIAdauga;
private:
	Service& srv;

	QListWidget* lista_masini = new QListWidget;
	
	QTableView* tableElems = new QTableView;
	MyTableModel* model = new MyTableModel(srv.srv_getAll());

	QWidget* btnDynamic = new QWidget{};
	QHBoxLayout* lyBtnDyn = new QHBoxLayout{};
	QPushButton* buttonAdauga = new QPushButton{ "&Adauga" };
	QPushButton* buttonSterge = new QPushButton{ "&Sterge" };
	QPushButton* buttonModifica = new QPushButton{ "&Modifica" };
	QPushButton* buttonSort = new QPushButton{ "&Sort" };
	QPushButton* buttonFilter = new QPushButton{ "&Filter" };
	QPushButton* buttonLoad = new QPushButton{ "&Load" };
	QPushButton* buttonUndo = new QPushButton{ "&<-" };
	QPushButton* buttonAdaugaCos = new QPushButton{ "&Adauga in cos" };
	QPushButton* buttonCosCrud = new QPushButton{ "&CosCRUD" };
	QPushButton* buttonCosReadOnly = new QPushButton{ "&CosReadOnly" };
	QLineEdit* txtNumar = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	QLineEdit* txtModel = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QListWidgetItem* anteriorSelectedItem = new QListWidgetItem;

/* Functia aseaza componentele pe fereastra*/
	void initGUI();

/* Functia preia datele aplicatiei */
	//void loadData(const vector<Masina>& all);

/* Functia conecteaza butoanele aplicatiei */
	void initConnect();

public:
	void loadData(const vector<Masina>& all);
	void loadBtn(const vector<Masina>& all);

	GUI(Service& serv) : srv{serv}
	{	
		loadData(srv.srv_getAll());
		//loadBtn(srv.srv_getAll());
		initGUI();
		initConnect();
	}
};

class GUIAdauga : public QWidget
{	
	friend class GUI;
private:
	Service& srv;
	GUI& main;

	QPushButton* buttonAdauga = new QPushButton{ "&Adauga" };
	QPushButton* buttonCancel = new QPushButton{ "&Cancel" };
	QLineEdit* txtNumar = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	QLineEdit* txtModel = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	void initGUIAdauga();
	void initConnectAdauga();

public:
	GUIAdauga(Service& serv, GUI& main) : srv{serv}, main{main}
	{
		initGUIAdauga();
		initConnectAdauga();
	}
};

class GUISort : public QWidget
{	
	friend class GUI;
private:
	Service& srv;
	GUI& main;

	QRadioButton* dupaNumar = new QRadioButton{ "&Dupa numar" };
	QRadioButton* dupaProducator = new QRadioButton{ "&Dupa producator" };
	QPushButton* buttonSort = new QPushButton{ "&Sort" };
	QPushButton* buttonCancel = new QPushButton{ "&Cancel" };
	void initGUISort();
	void initConnectSort();

public:
	GUISort(Service& serv, GUI& main) : srv{ serv }, main{ main }
	{
		initGUISort();
		initConnectSort();
	}
};

class GUIFilter : public QWidget
{
private:
	Service& srv;
	GUI& main;

	QLineEdit* txtProducator = new QLineEdit;
	QPushButton* buttonFilter = new QPushButton{ "&Filter" };
	QPushButton* buttonCancel = new QPushButton{ "&Cancel" };

	void initGUIFilter();
	void initConnectFilter();

public:
	GUIFilter(Service& srv, GUI& main) : srv{ srv }, main{ main }
	{
		initGUIFilter();
		initConnectFilter();
	}
};

class GUICos : public QWidget, public Observer
{
private:
	Service& srv;
	GUI& main;

	QListWidget* lista_cos = new QListWidget;
	QPushButton* buttonDelete = new QPushButton{ "&Delete all" };
	QPushButton* buttonRandom = new QPushButton{ "&Random" };
	QPushButton* buttonExport = new QPushButton{ "&Export" };
	QLineEdit* txtNumar = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	QLineEdit* txtModel = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;

	//void loadDataCos(const vector<Masina>& all);
	void initGUICos();
	void initConnectCos();
	void update() override;

public:
	void loadDataCos(const vector<Masina>& all);
	GUICos(Service& serv, GUI& main) : srv{ serv }, main{ main }
	{	
		srv.addObserver(this);
		loadDataCos(srv.continutCos());
		initGUICos();
		initConnectCos();
	}
};

class GUICosReadOnly : public QWidget, public Observer
{
private:
	Service& srv;
	GUI& main;

	void update() override
	{
		repaint();
	}

public:
	GUICosReadOnly(Service& serv, GUI& main) : srv{ serv }, main{ main }
	{
		srv.addObserver(this);
	}
	
	void paintEvent(QPaintEvent* ev) override;
};

class GUIExport : public QWidget
{
private:
	Service& srv;

	QLineEdit* numeFisier = new QLineEdit{};
	QPushButton* buttonExport = new QPushButton{ "&Export" };
	QPushButton* buttonCancel = new QPushButton{ "&Cancel" };

	void initGUIExport();
	void initConnectExport();

public:
	GUIExport(Service& srv) :srv{ srv }
	{
		initGUIExport();
		initConnectExport();
	}
};

class GUIRandom : public QWidget
{
private:
	Service& srv;
	GUICos& main;

	QLineEdit* numarDate = new QLineEdit{};
	QPushButton* buttonRandom = new QPushButton{ "&Random" };
	QPushButton* buttonCancel = new QPushButton{ "&Cancel" };

	void initGUIRandom();
	void initConnectRandom();

public:
	GUIRandom(Service& srv, GUICos& main) : srv{ srv }, main{main}
	{
		initGUIRandom();
		initConnectRandom();
	}
};