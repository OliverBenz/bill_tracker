#include "mainWindow.hpp"

mainWindow::mainWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);

	m_menuBar = new toolBar(this);
	m_inputWindow = new inputWindow(this);

	m_lMain->setMenuBar(m_menuBar);
	m_lMain->addWidget(m_inputWindow);
}

mainWindow::~mainWindow() {
	delete m_inputWindow;
	delete m_menuBar;
	delete m_lMain;
}
