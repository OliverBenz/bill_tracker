#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "addBillWidget.hpp"
#include "billTable.hpp"
#include "toolBar.hpp"

class mainWindow : public QWidget {
	Q_OBJECT

public:
	mainWindow(QWidget* parent = nullptr);
	~mainWindow();

private:
	QVBoxLayout* m_lMain;

	toolBar* m_menuBar;
	addBillWidget* m_addBillWidget;
	QTableView* m_tableView;
	billTable* m_billTable;
};
