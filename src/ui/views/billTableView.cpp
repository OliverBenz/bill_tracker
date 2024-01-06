#include "billTableView.hpp"

#include <iostream>

billTableView::billTableView() : QTableView(nullptr) {
	m_model = new QStandardItemModel();
	setHeader();
	initShow();
}

void billTableView::setHeader() {
	// Set horizontal header labels
	QStringList headerLabels;
	headerLabels << "Date" << "Shop" << "Price" << "Category" << "Subcategory";

	m_model->setColumnCount(5);
	m_model->setHorizontalHeaderLabels(headerLabels);

	setModel(m_model);
}

void billTableView::initShow() {
	const auto& billData = m_logic.getAllData();
	for (const auto& bill: billData) {
		appendBill(bill);
	}
	setModel(m_model);
}

bool billTableView::insert(const lib::bill& bill) {
	// Add bill to logic
	m_logic.insertBill(bill);

	appendBill(bill);

	return true;
}

void billTableView::appendBill(const lib::bill& bill) {
	// TODO: Assert all information can be resolved
	QList<QStandardItem*> items;
	items.append(new QStandardItem(bill.date.c_str()));
	items.append(new QStandardItem(m_logic.getShopName(bill.shop).c_str()));
	items.append(new QStandardItem(QString::number(static_cast<double>(bill.price))));
	items.append(new QStandardItem(m_logic.getCategoryName(bill.category).c_str()));
	items.append(new QStandardItem(m_logic.getSubCategoryName(bill.category, bill.subCategory).c_str()));
	m_model->appendRow(items);
}
