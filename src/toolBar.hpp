#pragma once

#include <QWidget>
#include <QMenuBar>
#include <QAction>
#include <QMenu>

#include "settingsWindow.hpp"

class toolBar : public QMenuBar{
	Q_OBJECT

public:
	toolBar(QWidget* parent = nullptr);
	~toolBar();

private:
	void createActions();
	void createMenus();

private slots:
	void importBills();
	void exportBills();
	void settings();
	void about();

private:
	QMenu* m_file;
	QAction* m_import;
	QAction* m_export;
	QAction* m_settings;

	QMenu* m_help;
	QAction* m_about;

	// Windows
	settingsWindow* m_windowSettings;
};

