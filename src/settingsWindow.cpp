#include "settingsWindow.hpp"

#include "lib/fileHandling.hpp"

settingsWindow::settingsWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QHBoxLayout(this);
	m_laPathBill = new QLabel("Bill folder path:", this);
	m_lePathBill = new QLineEdit(lib::getFolderPath(lib::file::bills).c_str(), this);
	m_bPathBill = new QPushButton("Update", this);

	m_lMain->addWidget(m_laPathBill);
	m_lMain->addWidget(m_lePathBill);
	m_lMain->addWidget(m_bPathBill);

	connect(m_bPathBill, SIGNAL(clicked()), this, SLOT(updateFolderPath()));
}

void settingsWindow::updateFolderPath() {
	// TODO:
	//   - Check if new path exists
	//   - Move old file to new path
	//   - Update path in config.json
}

settingsWindow::~settingsWindow() {
	delete m_bPathBill;
	delete m_lePathBill;
	delete m_laPathBill;
	
	delete m_lMain;
}
