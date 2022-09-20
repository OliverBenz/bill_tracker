#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QTableView>

#include "statisticsView.hpp"
#include "billManager.hpp"

class ViewSelector : public QTabWidget {
	Q_OBJECT

public:
	ViewSelector(QWidget* parent = nullptr);
	~ViewSelector();

private slots:
	void updateTab(int id);

private:
	// Pages
	QTableView* m_tableView;
	statisticsView* m_overview;
	BillManager* m_billManager;
};
