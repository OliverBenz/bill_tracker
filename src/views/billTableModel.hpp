#pragma once

#include "../lib/bill.hpp"
#include "../lib/shop.hpp"
#include "../lib/category.hpp"

#include <QAbstractTableModel>

#include <map>
#include <utility>
#include <string>

// TODO: Editable models need to implement setData(), and implement flags() to return a value containing Qt::ItemIsEditable.
// 		 See docs for more info

class billTableModel : public QAbstractTableModel {
	Q_OBJECT

public:
	billTableModel();

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	bool insert(const lib::bill& newBill);

private:
	void getAllData();

private:
	std::vector<lib::bill> m_data;

	// Used to resolve the ids from the bill classes passed to insert().
	std::map<int, std::string> m_shops;
	std::map<int, std::string> m_categories;

	// Category id - pair of (subcat.id, subcat.name)
	std::map<std::pair<int, int>, std::string> m_subcategories;
};
