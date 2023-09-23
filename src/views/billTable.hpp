#pragma once

#include "../lib/bill.hpp"
#include "../lib/shop.hpp"
#include "../lib/category.hpp"

#include <QTableView>
#include <QStandardItemModel>

#include <map>
#include <utility>
#include <string>

// TODO: Editable models need to implement setData(), and implement flags() to return a value containing Qt::ItemIsEditable.
// 		 See docs for more info

class billTable : public QTableView {
	Q_OBJECT

public:
	billTable();

	bool insert(const lib::bill& newBill);

private:
	void setHeader();
	void appendBill(const lib::bill& bill);
	void getAllData();

private:
	QStandardItemModel* m_model;

	std::vector<lib::bill> m_data;
	// Used to resolve the ids from the bill classes passed to insert().
	std::map<int, std::string> m_shops;
	std::map<int, std::string> m_categories;

	// Category id - pair of (subcat.id, subcat.name)
	std::map<std::pair<int, int>, std::string> m_subcategories;
};
