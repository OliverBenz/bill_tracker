#include "settingsWindow.hpp"

#include "lib/fileHandling.hpp"

#include <QFileDialog>
#include <filesystem>

settingsWindow::settingsWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);

	// Bill line
	m_lPathBill = new QHBoxLayout(this);
	m_laPathBill = new QLabel("Bill folder path:", this);
	m_lePathBill = new QLineEdit(this);
	m_bPathBill = new QPushButton("Find", this);

	m_lPathBill->addWidget(m_laPathBill);
	m_lPathBill->addWidget(m_lePathBill);
	m_lPathBill->addWidget(m_bPathBill);

	// Exit buttons
	m_lExitButtons = new QHBoxLayout(this);
	m_bSave = new QPushButton("Save", this);
	m_bCancel = new QPushButton("Cancel", this);

	m_lExitButtons->addWidget(m_bSave);
	m_lExitButtons->addWidget(m_bCancel);

	// Add to main layout
	m_lMain->addLayout(m_lPathBill);
	m_lMain->addLayout(m_lExitButtons);

	// Set connections
	connect(m_bPathBill, SIGNAL(clicked()), this, SLOT(openFileExplorerBills()));
	connect(m_bCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(m_bSave, SIGNAL(clicked()), this, SLOT(save()));

	fillStandardData();
}

void settingsWindow::fillStandardData() {
	m_lePathBill->setText(lib::getFolderPath(lib::file::bills).c_str());
}

void settingsWindow::openFileExplorerBills() {
	QFileDialog fileDialog;
	fileDialog.setFileMode(QFileDialog::Directory);
	fileDialog.exec();

	if(fileDialog.selectedFiles().size() == 1) {
		m_lePathBill->setText(fileDialog.selectedFiles()[0]);
	}
}

void settingsWindow::save() {
	updateBillsPath();
}

void settingsWindow::cancel() {
	fillStandardData();
}

void settingsWindow::updateBillsPath() {
	std::string path = m_lePathBill->text().toStdString();
	if(path.back() == '/')
		path.pop_back();

	if(path != lib::getFolderPath(lib::file::bills))
		lib::updateFilePath(lib::file::bills, path);
}

settingsWindow::~settingsWindow() {
	delete m_bCancel;
	delete m_bSave;
	delete m_lExitButtons;

	delete m_bPathBill;
	delete m_lePathBill;
	delete m_laPathBill;
	delete m_lPathBill;

	delete m_lMain;
}
