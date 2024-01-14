#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "ui/toolBar.hpp"
#include "ui/views/addBillView.hpp"
#include "ui/views/billTableView.hpp"

class mainWindow : public QWidget {
	Q_OBJECT

public:
	mainWindow(QWidget* parent = nullptr);
	~mainWindow();

private:
	QVBoxLayout* m_lMain;

	toolBar* m_menuBar;
	AddBillView* m_addBillWidget;
	billTableView* m_billTable;
};
