#include "toolBar.hpp"

#include "aboutDialog.hpp"
#include "lib/dataHandler.hpp"

toolBar::toolBar(QWidget* parent) : QMenuBar(parent) {
	createActions();
	createMenus();
}

void toolBar::createActions() {
	m_import = new QAction("Import Bills");
	m_import->setStatusTip("Import bills from json file.");
	connect(m_import, SIGNAL(triggered()), this, SLOT(importBills()));

	m_export = new QAction("Export Bills");
	m_export->setStatusTip("Export bills to json file.");
	connect(m_export, SIGNAL(triggered()), this, SLOT(exportBills()));

	m_backup = new QAction("Create Backup");
	m_backup->setStatusTip("Create new backup file for shops and bills.");
	connect(m_backup, SIGNAL(triggered()), this, SLOT(createBackup()));

	m_settings = new QAction("Settings");
	m_settings->setStatusTip("Configure settings");
	connect(m_settings, SIGNAL(triggered()), this, SLOT(settings()));

	m_about = new QAction("About");
	m_about->setStatusTip("About this application.");
	connect(m_about, SIGNAL(triggered()), this, SLOT(about()));
}

void toolBar::createMenus() {
	m_file = addMenu("File");
	m_file->addAction(m_import);
	m_file->addAction(m_export);
	m_file->addAction(m_backup);
	m_file->addAction(m_settings);

	m_help = addMenu("Help");
	m_help->addAction(m_about);
}

void toolBar::importBills() {

}

void toolBar::exportBills() {

}

void toolBar::createBackup() {
	if(!lib::createBackup()) {
		// TODO: Error popup
	}
}

void toolBar::settings() {
	m_windowSettings = new SettingsView();
	m_windowSettings->show();
}

void toolBar::about() {
	aboutDialog about;
	about.exec();
}

toolBar::~toolBar() {
	delete m_windowSettings;

	delete m_about;
	delete m_help;

	delete m_settings;
	delete m_export;
	delete m_import;
	delete m_file;
}
