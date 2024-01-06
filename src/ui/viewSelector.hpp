#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QTableView>

#include "ui/views/billTableView.hpp"
#include "overview.hpp"

class viewSelector : public QTabWidget {
	Q_OBJECT

public:
	viewSelector(QWidget* parent = nullptr);
	~viewSelector();

private slots:
	void updateTab(int id);

private:
	// Pages
	billTableView* m_billTable;
	overview* m_overview;

};
