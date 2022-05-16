#pragma once

#include "lib/bill.hpp"
#include "lib/shop.hpp"
#include "lib/category.hpp"

#include <QAbstractTableModel>

// TODO: Editable models need to implement setData(), and implement flags() to return a value containing Qt::ItemIsEditable.
// 		 See docs for more info

class billTable : public QAbstractTableModel {
	Q_OBJECT

public:
	billTable();

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	bool insert(const lib::bill& newBill);

protected:
	std::vector<lib::bill> m_data;

private:
	// Used to resolve the ids from the bill classes passed to insert().
	std::vector<lib::shop> m_shops;
	std::vector<lib::category> m_categories;
};
