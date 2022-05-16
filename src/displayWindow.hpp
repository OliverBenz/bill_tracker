#pragma once

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTableWidget>

#include "billTable.hpp"

class displayWindow : public QWidget {
	Q_OBJECT

public:
	displayWindow(QWidget* parent = nullptr);
	~displayWindow();

private:
	QVBoxLayout* m_lMain;
	QComboBox* m_cbFindShop;
	billTable* m_tabBills;
};
