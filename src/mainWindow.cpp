#include "mainWindow.hpp"

mainWindow::mainWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);

	m_menuBar = new toolBar();
	m_viewSelector = new ViewSelector();

	m_lMain->setMenuBar(m_menuBar);
	m_lMain->addWidget(m_viewSelector);
}

mainWindow::~mainWindow() {
	delete m_lMain;
}
