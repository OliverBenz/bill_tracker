#pragma once

#include "ui/models/billTableModel.hpp"

#include <QTableView>
#include <QStandardItemModel>

#include <map>
#include <utility>
#include <string>

// TODO: Editable models need to implement setData(), and implement flags() to return a value containing Qt::ItemIsEditable.
// 		 See docs for more info

//! Handles how to display the data model.
class billTableView : public QTableView {
	Q_OBJECT

public:
	billTableView();

public slots:
	//! Insert a new bill to the table.
	bool insert(const lib::bill1& newBill);

private:
	//! Get all bills from file and show in table.
	void initShow();

	//! Setup the header of the table.
	void setHeader();

	//! Add a new line to the table.
	void appendBill(const lib::bill1& bill);

private:
	billTableModel m_logic; //!< Handles data and all non-UI related tasks.

	QStandardItemModel* m_model;
};
