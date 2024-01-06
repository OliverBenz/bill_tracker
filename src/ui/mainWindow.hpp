#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "ui/toolBar.hpp"
#include "addBillWidget.hpp"
#include "ui/views/billTableView.hpp"

class mainWindow : public QWidget {
	Q_OBJECT

public:
	mainWindow(QWidget* parent = nullptr);
	~mainWindow();

private:
	QVBoxLayout* m_lMain;

	toolBar* m_menuBar;
	addBillWidget* m_addBillWidget;
	billTableView* m_billTable;
};
