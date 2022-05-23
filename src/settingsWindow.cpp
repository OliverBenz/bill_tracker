#include "settingsWindow.hpp"

settingsWindow::settingsWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QHBoxLayout(this);
	m_laFolderPath = new QLabel("Folder path:", this);
	m_leFolderPath = new QLineEdit(this);

	m_lMain->addWidget(m_laFolderPath);
	m_lMain->addWidget(m_leFolderPath);
}

settingsWindow::~settingsWindow() {
	delete m_leFolderPath;
	delete m_laFolderPath;
	
	delete m_lMain;
}
