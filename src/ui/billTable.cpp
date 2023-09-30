#include "billTable.hpp"

#include "lib/dataHandler.hpp"

billTable::billTable() {

	m_model = new QStandardItemModel();
	m_model->setColumnCount(5);

	setHeader();
	getAllData();
}

void billTable::setHeader() {
	// Set horizontal header labels
	QStringList headerLabels;
	headerLabels << "Date" << "Shop" << "Price" << "Category" << "Subcategory";
	m_model->setHorizontalHeaderLabels(headerLabels);

	setModel(m_model);
}

void billTable::getAllData() {
	m_data = lib::getBills("");

	// Get shops
	for(const auto& shop : lib::getShops()) {
		m_shops.insert({shop.id, shop.name});
	}

	// Get categories and subcats
	for(const auto& cat : lib::getCategories()) {
		m_categories.insert({cat.id, cat.name});

		for(const auto& subcat : lib::getSubCategories(cat.id)) {
			m_subcategories.insert({{cat.id, subcat.id}, subcat.name});
		}
	}

	// NOTE: Preallocate row would be better
	// m_model->setRowCount(static_cast<int>(m_data.size()));
	for (const auto& bill: m_data) {
		appendBill(bill);
	}
}

bool billTable::insert(const lib::bill& bill) {
	m_data.push_back(bill);
	appendBill(bill);

	return true;
}

void billTable::appendBill(const lib::bill& bill) {
	// TODO: Assert all information can be resolved
	QList<QStandardItem*> items;
	items.append(new QStandardItem(bill.date.c_str()));
	items.append(new QStandardItem(m_shops.at(bill.shop).c_str()));
	items.append(new QStandardItem(QString::number(static_cast<double>(bill.price))));
	items.append(new QStandardItem(m_categories.at(bill.category).c_str()));
	items.append(new QStandardItem(m_subcategories.at({bill.category,bill.subCategory}).c_str()));
	m_model->appendRow(items);
}
