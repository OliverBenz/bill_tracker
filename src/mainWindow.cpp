#include "mainWindow.hpp"

mainWindow::mainWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);

	m_menuBar = new toolBar();
	m_addBillWidget = new addBillWidget();
	m_tableView = new QTableView();

	m_billTable = new billTable();
	m_tableView->setModel(m_billTable);

	m_lMain->setMenuBar(m_menuBar);
	m_lMain->addWidget(m_addBillWidget);
	m_lMain->addWidget(m_tableView);
}

mainWindow::~mainWindow() {
	delete m_billTable;
	delete m_tableView;

	delete m_addBillWidget;
	delete m_menuBar;
	delete m_lMain;
}
