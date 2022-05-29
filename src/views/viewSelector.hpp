#pragma once

#include <QWidget>
#include <QTabWidget>

#include "billTable.hpp"

class viewSelector : public QTabWidget {
	Q_OBJECT

public:
	viewSelector(QWidget* parent = nullptr);
	~viewSelector();

private slots:
	void updateTab(int id);

private:
	// Tabs
	QWidget* m_selOverview;  // Contains statistics on bills
	QWidget* m_selList;      // Contains a table of bills

	// Pages
	billTable* m_billTable;

};
