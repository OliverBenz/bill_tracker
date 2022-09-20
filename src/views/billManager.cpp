#include "billManager.hpp"

BillManager::BillManager(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);

	m_addBillWidget = new addBillWidget();
	m_tableView = new QTableView();

	m_billTable = new billTableModel();
	m_tableView->setModel(m_billTable);

	m_lMain->addWidget(m_addBillWidget);
	m_lMain->addWidget(m_tableView);
}

BillManager::~BillManager() {
	delete m_billTable;
	delete m_tableView;

	delete m_addBillWidget;
	delete m_lMain;
}
