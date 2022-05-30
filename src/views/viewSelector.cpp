#include "viewSelector.hpp"

viewSelector::viewSelector(QWidget* parent) : QTabWidget(parent) {
	m_tableView = new QTableView();
	m_billTable = new billTable();
	m_tableView->setModel(m_billTable);
	m_tableView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	m_overview = new overview();

	addTab(m_overview, "Overview");
	addTab(m_tableView, "List View");
}

void viewSelector::updateTab(int id) {
	if(id) {

	}
	// TODO: Check documentation
}


viewSelector::~viewSelector() {
	delete m_overview;

	delete m_billTable;
}