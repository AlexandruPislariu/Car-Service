#pragma once
#include <QtWidgets/qtableview.h>
#include "Domain.h"
#include <vector>

class MyTableModel : public QAbstractTableModel
{
	std::vector<Masina> masini;

public:
	MyTableModel(const std::vector<Masina>& v) : masini{ v } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return masini.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			Masina m = masini[index.row()];
			if (index.column() == 0)
				return QString::fromStdString(m.getNrInmatriculare());
			else
				if (index.column() == 1)
					return QString::fromStdString(m.getProducator());
				else
					if (index.column() == 2)
						return QString::fromStdString(m.getModel());
					else
						return QString::fromStdString(m.getTip());
		}

		return QVariant();
	}
	void setElements(const std::vector<Masina>& newList)
	{
		masini = newList;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
	}
};