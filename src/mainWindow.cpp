#include "mainWindow.hpp"

mainWindow::mainWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);

	// TODO: Setup toolbar
	m_menu = new QMenu(this);
	m_menu->addMenu("File");

	m_inputWindow = new inputWindow(this);

	m_lMain->addWidget(m_menu);
	m_lMain->addWidget(m_inputWindow);
}

mainWindow::~mainWindow() {
	delete m_inputWindow;
	delete m_menu;
	delete m_lMain;
}
