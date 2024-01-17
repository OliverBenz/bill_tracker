#include "application.hpp"

Application::Application(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);

	m_menuBar = new toolBar();
	m_addBillWidget = new AddBillView();

	m_billTable = new billTableView();

	m_lMain->setMenuBar(m_menuBar);
	m_lMain->addWidget(m_addBillWidget);
	m_lMain->addWidget(m_billTable);

	connect(m_addBillWidget, SIGNAL(onNewBill(const lib::bill1&)),
            m_billTable, SLOT(insert(const lib::bill1&)));
}

Application::~Application() {
	delete m_billTable;

	delete m_addBillWidget;
	delete m_menuBar;
	delete m_lMain;
}
