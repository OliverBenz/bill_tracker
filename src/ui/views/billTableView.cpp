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
	headerLabels << "Date" << "Shop" << "Price" << "Category" << "Usage";

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

bool billTableView::insert(const lib::bill1& bill) {
	// Add bill to logic
	m_logic.insertBill(bill);

	appendBill(bill);

	return true;
}

void billTableView::appendBill(const lib::bill1& bill) {
	// TODO: Assert all information can be resolved
	QList<QStandardItem*> items;
	items.append(new QStandardItem(bill.date.c_str()));
	items.append(new QStandardItem(m_logic.getShopName(bill.shopId).c_str()));
	items.append(new QStandardItem(QString::number(static_cast<double>(bill.price))));
	items.append(new QStandardItem(m_logic.getCategoryName(bill.usageId).c_str()));
	items.append(new QStandardItem(m_logic.getUsageName(bill.usageId).c_str()));
	m_model->appendRow(items);
}
