#include "GUI.h"
#include "Exceptii.h"
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qgridlayout.h>
#include <qmessagebox.h>
#include <qimage.h>

void GUI::loadData(const vector<Masina>& all)
{	
	/*
	anteriorSelectedItem = nullptr;
	lista_masini->clear();
	for (auto masina : all)
		lista_masini->addItem(QString::fromStdString(masina.getNrInmatriculare()));	
	*/
	model->setElements(all);
}

void GUI::loadBtn(const vector<Masina>& all)
{	
	QLayoutItem* child;
	while ((child = lyBtnDyn->takeAt(0)) != 0)
		delete child;

	for (auto masina : all)
	{	
		auto btn = new QPushButton{ QString::fromStdString(masina.getNrInmatriculare()) };
		lyBtnDyn->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [this, btn, masina]() {
			delete btn;
			srv.srv_sterge(masina.getNrInmatriculare());
			loadData(srv.srv_getAll());
			});
	}
}

void GUI::initGUI()
{
	QHBoxLayout* layoutMain = new QHBoxLayout{};
	setLayout(layoutMain);
	
	btnDynamic->setLayout(lyBtnDyn);
	layoutMain->addWidget(btnDynamic);

	QVBoxLayout* layoutList = new QVBoxLayout{};
/* Tiparesc masinile existente in lista */
	tableElems->setModel(model);
	layoutList->addWidget(tableElems);

	QHBoxLayout* buttonsList= new QHBoxLayout{};
/* Butoane care actioneaza pe toata lista */
	buttonsList->addWidget(buttonLoad);
	buttonsList->addWidget(buttonSort);
	buttonsList->addWidget(buttonFilter);
	layoutList->addLayout(buttonsList);

	layoutMain->addLayout(layoutList);

/* Tiparesc detaliile unei masini */
	auto crudOPLayout = new QVBoxLayout;
	auto formLayout = new QFormLayout;
	formLayout->addRow("Inmatriculare", txtNumar);
	formLayout->addRow("Producator", txtProducator);
	formLayout->addRow("Model", txtModel);
	formLayout->addRow("Tip", txtTip);
	crudOPLayout->addLayout(formLayout);

/* Butoanele pentru CRUD operations */
	auto layoutButtons = new QGridLayout;
	layoutButtons->addWidget(buttonAdauga,0,0);
	layoutButtons->addWidget(buttonSterge,0,1);
	layoutButtons->addWidget(buttonModifica,0,2);
	layoutButtons->addWidget(buttonUndo,1,1);
	layoutButtons->addWidget(buttonAdaugaCos, 2, 0);
	layoutButtons->addWidget(buttonCosCrud, 2, 1);
	layoutButtons->addWidget(buttonCosReadOnly, 2, 2);
	crudOPLayout->addLayout(layoutButtons);

	layoutMain->addLayout(crudOPLayout);
}

void GUI::initConnect()
{
/* Cand se selecteaza butonul Adauga */
	QObject::connect(buttonAdauga, &QPushButton::clicked, [&]() {
		GUIAdauga* windowAdauga = new GUIAdauga(srv, *this);
		windowAdauga->show();
		});

/* Cand se selecteaza butonul Sterge*/
	QObject::connect(buttonSterge, &QPushButton::clicked, [&]() {
		QString numar_inmatriculare = txtNumar->text();

		try
		{
			srv.srv_sterge(numar_inmatriculare.toStdString());
			QMessageBox::information(nullptr, "Info", "Am sters masina!!");
		}
		catch (ValidException & validEx)
		{
			QMessageBox::warning(nullptr, "Error", QString::fromStdString(validEx.getMessage()));
		}
		catch (RepoException & repoEx)
		{
			QMessageBox::critical(nullptr, "Error", QString::fromStdString(repoEx.getMessage()));
		}
		//reincarc lista
		loadData(srv.srv_getAll());
		});

/* Cand se selecteaza butonul Modifica */
	QObject::connect(buttonModifica, &QPushButton::clicked, [&]() {
		QString numar_inmatriculare = txtNumar->text();
		QString producator = txtProducator->text();
		QString model = txtModel->text();
		QString tip = txtTip->text();

		try
		{
			srv.srv_modifica(numar_inmatriculare.toStdString(), producator.toStdString(), model.toStdString(), tip.toStdString());
			QMessageBox::information(nullptr, "Info", "Am modificat masina!!");
		}
		catch (ValidException & validEx)
		{
			QMessageBox::warning(nullptr, "Error", QString::fromStdString(validEx.getMessage()));
		}
		catch (RepoException & repoEx)
		{
			QMessageBox::critical(nullptr, "Error", QString::fromStdString(repoEx.getMessage()));
		}
		//reincarc lista
		loadData(srv.srv_getAll());
		});

/* Cand se selecteaza un item din lista incarc detaliile 
	QObject::connect(lista_masini, &QListWidget::itemSelectionChanged, [&]() {
		if (lista_masini->selectedItems().isEmpty())
		{
			txtNumar->setText("");
			txtProducator->setText("");
			txtModel->setText("");
			txtTip->setText("");

			return;
		}

		if (anteriorSelectedItem != nullptr)
		{
			anteriorSelectedItem->setBackground(QBrush{});
			anteriorSelectedItem->setCheckState(Qt::Unchecked);
		}

		QListWidgetItem* selectedItem = lista_masini->selectedItems().at(0);
		selectedItem->setBackground(QBrush{ Qt::blue,Qt::SolidPattern });
		selectedItem->setCheckState(Qt::Checked);
		QString line = selectedItem->text();
		Masina m = srv.srv_cauta(line.toStdString());

		txtNumar->setText(QString::fromStdString(m.getNrInmatriculare()));
		txtProducator->setText(QString::fromStdString(m.getProducator()));
		txtModel->setText(QString::fromStdString(m.getModel()));
		txtTip->setText(QString::fromStdString(m.getTip()));

		anteriorSelectedItem = selectedItem;
		});
	*/

/* Selectia in tabel */
	QObject::connect(tableElems->selectionModel(), &QItemSelectionModel::selectionChanged, [this]()
		{
			if (tableElems->selectionModel()->selectedIndexes().isEmpty())
			{
				txtNumar->setText("");
				txtProducator->setText("");
				txtModel->setText("");
				txtTip->setText("");

				return;
			}

			int selectedRow = tableElems->selectionModel()->selectedIndexes().at(0).row();
			auto celNumar = tableElems->model()->index(selectedRow, 0);
			auto valueNumar = tableElems->model()->data(celNumar, Qt::DisplayRole).toString();
			txtNumar->setText(valueNumar);

			auto celProducator = tableElems->model()->index(selectedRow, 1);
			auto valueProducator = tableElems->model()->data(celProducator, Qt::DisplayRole).toString();
			txtProducator->setText(valueProducator);

			auto celModel = tableElems->model()->index(selectedRow, 2);
			auto valueModel = tableElems->model()->data(celModel, Qt::DisplayRole).toString();
			txtModel->setText(valueModel);

			auto celTip = tableElems->model()->index(selectedRow, 3);
			auto valueTip = tableElems->model()->data(celTip, Qt::DisplayRole).toString();
			txtTip->setText(valueTip);

		});

/* Cand se apasa butonul Load */
	QObject::connect(buttonLoad, &QPushButton::clicked, [&]() {
		loadData(srv.srv_getAll());
		});

/* Cand se apasa butonul Sort */
	QObject::connect(buttonSort, &QPushButton::clicked, [&]() {
		GUISort* windowSort = new GUISort(srv, *this);
		windowSort->show();
		});

/* Cand se apasa butonul Filer */
	QObject::connect(buttonFilter, &QPushButton::clicked, [&]() {
		GUIFilter* windowFilter = new GUIFilter(srv, *this);
		windowFilter->show();
		});

	QObject::connect(buttonUndo, &QPushButton::clicked, [&]() {
		try
		{
			srv.undo();
			loadData(srv.srv_getAll());
			//loadBtn(srv.srv_getAll());
		}
		catch (RepoException & repoEx)
		{
			QMessageBox::critical(nullptr, "Error", QString::fromStdString(repoEx.getMessage()));
		}
		});

	QObject::connect(buttonAdaugaCos, &QPushButton::clicked, [=]() {
		QString numar_inmatriculare = txtNumar->text();
		try
		{
			srv.addToCos(numar_inmatriculare.toStdString());
		}
		catch (ValidException& validEx)
		{
			QMessageBox::critical(nullptr, "Error", QString::fromStdString(validEx.getMessage()));
		}
		catch (RepoException & repoEx)
		{
			QMessageBox::critical(nullptr, "Error", QString::fromStdString(repoEx.getMessage()));
		}
		});
	QObject::connect(buttonCosCrud, &QPushButton::clicked, [=]() {
		GUICos* windowCos = new GUICos(srv, *this);
		windowCos->show();
		});

	QObject::connect(buttonCosReadOnly, &QPushButton::clicked, [=]()
		{
			GUICosReadOnly* windowCos = new GUICosReadOnly(srv, *this);
			windowCos->show();
		});

}

void GUIAdauga::initGUIAdauga()
{
	QVBoxLayout* crudOPLayout = new QVBoxLayout;
	setLayout(crudOPLayout);
	auto formLayout = new QFormLayout;
	formLayout->addRow("Inmatriculare", txtNumar);
	formLayout->addRow("Producator", txtProducator);
	formLayout->addRow("Model", txtModel);
	formLayout->addRow("Tip", txtTip);
	crudOPLayout->addLayout(formLayout);

	auto layoutButtons = new QGridLayout;
	layoutButtons->addWidget(buttonAdauga, 0, 0);
	layoutButtons->addWidget(buttonCancel, 0, 1);
	crudOPLayout->addLayout(layoutButtons);
}

void GUIAdauga::initConnectAdauga()
{
	QObject::connect(buttonAdauga, &QPushButton::clicked, [&]() {
			
		QString numar_inmatriculare = txtNumar->text();
		QString producator = txtProducator->text();
		QString model = txtModel->text();
		QString tip = txtTip->text();
		try
		{
			srv.srv_adauga(numar_inmatriculare.toStdString(), producator.toStdString(), model.toStdString(), tip.toStdString());
			QMessageBox::information(nullptr, "Info", "Am adaugat masina!!");
		}
		catch (ValidException & validEx)
		{
			QMessageBox::warning(nullptr, "Error", QString::fromStdString(validEx.getMessage()));
		}
		catch (RepoException & repoEx)
		{
			QMessageBox::critical(nullptr, "Error", QString::fromStdString(repoEx.getMessage()));
		}

		main.loadData(srv.srv_getAll());
		//main.loadBtn(srv.srv_getAll());
		close();
	});
	QObject::connect(buttonCancel, &QPushButton::clicked, [=]() {close(); });
	
}

void GUISort::initGUISort()
{
	QVBoxLayout* sortLayout = new QVBoxLayout{};
	setLayout(sortLayout);

	sortLayout->addWidget(dupaNumar);
	sortLayout->addWidget(dupaProducator);

	QGridLayout* buttons = new QGridLayout{};
	buttons->addWidget(buttonSort, 0, 0);
	buttons->addWidget(buttonCancel, 0, 1);
	sortLayout->addLayout(buttons);
}

void GUISort::initConnectSort()
{
	QObject::connect(buttonSort, &QPushButton::clicked, [=]() {
		if (dupaNumar->isChecked())
		{
			main.loadData(srv.srv_sortare_numar());
		//	main.loadBtn(srv.srv_sortare_numar());
		}
		else
		{
			main.loadData(srv.srv_sortare_producator());
		//	main.loadBtn(srv.srv_sortare_producator());
		}

		QMessageBox::information(nullptr, "Info", "Am sortat datele!");
		close();
		});
	QObject::connect(buttonCancel, &QPushButton::clicked, [=]() {close(); });
}

void GUIFilter::initGUIFilter()
{
	QVBoxLayout* filterLayout = new QVBoxLayout;
	setLayout(filterLayout);

	QFormLayout* lineLayout = new QFormLayout;
	lineLayout->addRow("Producator", txtProducator);
	filterLayout->addLayout(lineLayout);

	QGridLayout* buttonsLayout = new QGridLayout;
	buttonsLayout->addWidget(buttonFilter, 0, 0);
	buttonsLayout->addWidget(buttonCancel, 0, 1);
	filterLayout->addLayout(buttonsLayout);
}

void GUIFilter::initConnectFilter()
{
	QObject::connect(buttonFilter, &QPushButton::clicked, [=]() {
		main.loadData(srv.srv_filtrare(txtProducator->text().toStdString()));
		close();
		});
	QObject::connect(buttonCancel, &QPushButton::clicked, [=]() {
		close();
		});
}

void GUICos::update()
{
	loadDataCos(srv.continutCos());
}

void GUICos::loadDataCos(const vector<Masina>& all)
{
	lista_cos->clear();
	for (auto masina : all)
		lista_cos->addItem(QString::fromStdString(masina.getNrInmatriculare()));
}

void GUICos::initGUICos()
{
	QHBoxLayout* cosLayout = new QHBoxLayout{};
	setLayout(cosLayout);

	QVBoxLayout* layoutList = new QVBoxLayout{};
	layoutList->addWidget(lista_cos);

	QGridLayout* buttonCos = new QGridLayout{};
	buttonCos->addWidget(buttonDelete, 0, 0);
	buttonCos->addWidget(buttonRandom, 0, 1);
	buttonCos->addWidget(buttonExport, 0, 2);

	layoutList->addLayout(buttonCos);
	cosLayout->addLayout(layoutList);

	QFormLayout* layoutDate = new QFormLayout{};
	layoutDate->addRow("Numar", txtNumar);
	layoutDate->addRow("Producator", txtProducator);
	layoutDate->addRow("Model", txtModel);
	layoutDate->addRow("Tip", txtTip);
	cosLayout->addLayout(layoutDate);

}

void GUICos::initConnectCos()
{	
	QObject::connect(buttonDelete, &QPushButton::clicked, [=]() {
		srv.golesteCos();
		loadDataCos(srv.continutCos());
		});
	QObject::connect(buttonExport, &QPushButton::clicked, [=]() {
		GUIExport* windowExport = new GUIExport(srv);
		windowExport->show();
		});
	QObject::connect(buttonRandom, &QPushButton::clicked, [=]() {
		GUIRandom* windowRandom = new GUIRandom(srv, *this);
		windowRandom->show();
		});

	QObject::connect(lista_cos, &QListWidget::itemSelectionChanged, [=]() {

		if (lista_cos->selectedItems().isEmpty())
		{
			txtNumar->setText("");
			txtProducator->setText("");
			txtModel->setText("");
			txtTip->setText("");
		}
		else
		{
			QListWidgetItem* selectedItem = lista_cos->selectedItems().at(0);
			string numar_inmatricurale = selectedItem->text().toStdString();
			Masina m = srv.srv_cauta(numar_inmatricurale);

			txtNumar->setText(QString::fromStdString(m.getNrInmatriculare()));
			txtProducator->setText(QString::fromStdString(m.getProducator()));
			txtModel->setText(QString::fromStdString(m.getModel()));
			txtTip->setText(QString::fromStdString(m.getTip()));
		}
		});
}

void GUICosReadOnly::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };

	int x = 10;
	QImage* img = new QImage;
	img->load("nike.jpg");

	for (const auto& element : srv.continutCos())
	{	
		//p.setPen(Qt::blue);
		// p.setFont(QFont("Arial", 30));
		//p.drawRect(x, 0, 10, x);
		//p.drawText(QRect(10,x,200,200), Qt::AlignTop | Qt::AlignHCenter, QString::fromStdString(element.getNrInmatriculare()));
		//p.fillRect(0, 100, 100, 100, Qt::BrushStyle::Dense1Pattern);
		p.drawImage(10, x, *img);
		x += 100;
	}
}

void GUIExport::initGUIExport()
{
	QVBoxLayout* exportLayout = new QVBoxLayout{};
	setLayout(exportLayout);

	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow("Nume fisier", numeFisier);
	exportLayout->addLayout(formLayout);

	QGridLayout* buttons = new QGridLayout;
	buttons->addWidget(buttonExport, 0, 0);
	buttons->addWidget(buttonCancel, 0, 1);
	exportLayout->addLayout(buttons);
}

void GUIExport::initConnectExport()
{
	QObject::connect(buttonExport, &QPushButton::clicked, [=]() {
		srv.exportaCosCVS(numeFisier->text().toStdString());
		QMessageBox::information(nullptr, "Info", "Am exportat datele!");
		close();
		});

	QObject::connect(buttonCancel, &QPushButton::clicked, [=]() {
		close();
		});
}

void GUIRandom::initGUIRandom()
{
	QVBoxLayout* randLayout = new QVBoxLayout;
	setLayout(randLayout);

	QFormLayout* formLay = new QFormLayout;
	formLay->addRow("Numar date", numarDate);
	randLayout->addLayout(formLay);

	QGridLayout* buttons = new QGridLayout;
	buttons->addWidget(buttonRandom, 0, 0);
	buttons->addWidget(buttonCancel, 0, 1);
	randLayout->addLayout(buttons);
}

void GUIRandom::initConnectRandom()
{
	QObject::connect(buttonRandom, &QPushButton::clicked, [=]() {
		srv.addRandom(numarDate->text().toUInt());

		main.loadDataCos(srv.continutCos());

		close();
		});

	QObject::connect(buttonCancel, &QPushButton::clicked, [=]() {
		close();
		});
}