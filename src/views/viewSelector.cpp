#include "viewSelector.hpp"

viewSelector::viewSelector(QWidget* parent) : QTabWidget(parent) {
	m_selOverview = new QWidget();
	m_selList = new QWidget();

	addTab(m_selOverview, "Overview");
	addTab(m_selList, "List View");
}

void viewSelector::updateTab(int id) {
	if(id) {

	}
	// TODO: Check documentation
}


viewSelector::~viewSelector() {
	delete m_selList;
	delete m_selOverview;
}