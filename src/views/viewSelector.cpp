#include "viewSelector.hpp"
#include "billTableModel.hpp"

ViewSelector::ViewSelector(QWidget* parent) : QTabWidget(parent) {
	m_billManager = new BillManager();

	m_overview = new statisticsView();

	m_tableView = new QTableView();
	m_tableView->setModel(new billTableModel());
	m_tableView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);


	addTab(m_billManager, "Home");
	addTab(m_overview, "Overview");
	addTab(m_tableView, "List View");
}

void ViewSelector::updateTab(int id) {
	if(id) {

	}
	// TODO: Check documentation
}


ViewSelector::~ViewSelector() {
	delete m_overview;
	delete m_tableView;
	delete m_billManager;
}