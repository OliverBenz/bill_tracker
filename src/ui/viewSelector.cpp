#include "viewSelector.hpp"

viewSelector::viewSelector(QWidget* parent) : QTabWidget(parent) {
	m_billTable = new billTableView();
	m_billTable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	m_overview = new overview();

	addTab(m_overview, "Overview");
	addTab(m_billTable, "List View");
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