#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "addBillWidget.hpp"
#include "views/billTable.hpp"
#include "tools/toolBar.hpp"

class mainWindow : public QWidget {
	Q_OBJECT

public:
	mainWindow(QWidget* parent = nullptr);
	~mainWindow();

private:
	QVBoxLayout* m_lMain;

	toolBar* m_menuBar;
	addBillWidget* m_addBillWidget;
	billTable* m_billTable;
};
