#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "ui/billTable.hpp"
#include "ui/toolBar.hpp"
#include "addBillWidget.hpp"

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
