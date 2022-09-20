#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "tools/toolBar.hpp"
#include "views/viewSelector.hpp"

class mainWindow : public QWidget {
	Q_OBJECT

public:
	mainWindow(QWidget* parent = nullptr);
	~mainWindow();

private:
	QVBoxLayout* m_lMain;

	toolBar* m_menuBar;
	ViewSelector* m_viewSelector;
};
