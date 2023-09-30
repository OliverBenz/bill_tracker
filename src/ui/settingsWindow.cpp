#include "settingsWindow.hpp"

#include "lib/dataHandler.hpp"

#include <QFileDialog>
#include <filesystem>
#include <iostream>

settingsWindow::settingsWindow(QWidget* parent) : QWidget(parent) {
	m_lMain = new QVBoxLayout(this);

	// Bill line
	m_lPathBill = new QHBoxLayout();
	m_laPathBill = new QLabel("Bill folder path:");
	m_lePathBill = new QLineEdit();
	m_bPathBill = new QPushButton("Find");

	m_lPathBill->addWidget(m_laPathBill);
	m_lPathBill->addWidget(m_lePathBill);
	m_lPathBill->addWidget(m_bPathBill);

	// Data line
	m_lPathData = new QHBoxLayout();
	m_laPathData = new QLabel("Data folder path:");
	m_lePathData = new QLineEdit();
	m_bPathData = new QPushButton("Find");

	m_lPathData->addWidget(m_laPathData);
	m_lPathData->addWidget(m_lePathData);
	m_lPathData->addWidget(m_bPathData);

	// Exit buttons
	m_lExitButtons = new QHBoxLayout();
	m_bSave = new QPushButton("Save");
	m_bCancel = new QPushButton("Cancel");

	m_lExitButtons->addWidget(m_bSave);
	m_lExitButtons->addWidget(m_bCancel);

	// Add to main layout
	m_lMain->addLayout(m_lPathBill);
	m_lMain->addLayout(m_lPathData);
	m_lMain->addLayout(m_lExitButtons);

	// Set connections
	connect(m_bPathBill, SIGNAL(clicked()), this, SLOT(openFileExplorerBills()));
	connect(m_bPathData, SIGNAL(clicked()), this, SLOT(openFileExplorerData()));
	connect(m_bCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(m_bSave, SIGNAL(clicked()), this, SLOT(save()));

	fillStandardData();
}

void settingsWindow::fillStandardData() {
	m_lePathBill->setText(lib::getFolderPath(lib::file::bills).c_str());
	m_lePathData->setText(lib::getFolderPath(lib::file::data).c_str());
}

void settingsWindow::openFileExplorerBills() {
	QFileDialog fileDialog;
	fileDialog.setFileMode(QFileDialog::Directory);
	fileDialog.exec();

	if(fileDialog.selectedFiles().size() == 1) {
		m_lePathBill->setText(fileDialog.selectedFiles()[0]);
	}
}

void settingsWindow::openFileExplorerData() {
	QFileDialog fileDialog;
	fileDialog.setFileMode(QFileDialog::Directory);
	fileDialog.exec();

	if(fileDialog.selectedFiles().size() == 1) {
		m_lePathData->setText(fileDialog.selectedFiles()[0]);
	}
}

void settingsWindow::save() {
	updatePaths();
}

void settingsWindow::cancel() {
	fillStandardData();
}

void settingsWindow::updatePaths() {
	// Bills path
	std::string pathBill = m_lePathBill->text().toStdString();
	if(pathBill.back() == '/')
		pathBill.pop_back();

	if(pathBill != lib::getFolderPath(lib::file::bills))
		lib::updateFilePath(lib::file::bills, pathBill);

	// Data path
	std::string pathData = m_lePathData->text().toStdString();
	if(pathData.back() == '/')
		pathData.pop_back();

	if(pathData != lib::getFolderPath(lib::file::data))
		lib::updateFilePath(lib::file::data, pathData);
}

settingsWindow::~settingsWindow() {
	delete m_bCancel;
	delete m_bSave;
	delete m_lExitButtons;

	delete m_bPathData;
	delete m_lePathData;
	delete m_laPathData;
	delete m_lPathData;

	delete m_bPathBill;
	delete m_lePathBill;
	delete m_laPathBill;
	delete m_lPathBill;

	delete m_lMain;
}
