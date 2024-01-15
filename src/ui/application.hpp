#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "ui/toolBar.hpp"
#include "ui/views/addBillView.hpp"
#include "ui/views/billTableView.hpp"

class Application : public QWidget {
	Q_OBJECT

public:
	Application(QWidget* parent = nullptr);
	~Application();

private:
	QVBoxLayout* m_lMain;

	toolBar* m_menuBar;
	AddBillView* m_addBillWidget;
	billTableView* m_billTable;
};
