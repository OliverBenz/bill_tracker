#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "billTableModel.hpp"
#include "addBillWidget.hpp"
#include "../tools/toolBar.hpp"

class BillManager : public QWidget {
	Q_OBJECT

public:
	BillManager(QWidget* parent = nullptr);
	~BillManager();

private:
	QVBoxLayout* m_lMain;

	addBillWidget* m_addBillWidget;
	QTableView* m_tableView;
	billTableModel* m_billTable;
};
