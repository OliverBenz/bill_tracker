#include "displayWindow.hpp"

displayWindow::displayWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);
	m_cbFindShop = new QComboBox(this);
	m_tabBills = new billTable(this);

	m_lMain->addWidget(m_cbFindShop);
	m_lMain->addWidget(m_tabBills);

	setLayout(m_lMain);
}

displayWindow::~displayWindow() {
	delete m_tabBills;
	delete m_cbFindShop;
	delete m_lMain;
}