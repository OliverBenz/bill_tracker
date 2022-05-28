#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

class addBillWidget : public QWidget {
	Q_OBJECT

public:
	addBillWidget(QWidget* parent = nullptr);
	~addBillWidget();

private:
	void setupInputMasks();
	void setupConnections();

	//! Retrieve and display data from global json file
	void fillStandardData();

private slots:
	void clearInputFields();
	void writeBillToFile();
	void updateSubCategories(int newCategory);

private:
	QVBoxLayout* m_lMain;
	QHBoxLayout* m_lInputs;
	QHBoxLayout* m_lButtons;

	QLineEdit* m_leDate;  // NOTE: Could be updated to a calendar widget.
	QComboBox* m_cbShop;
	QComboBox* m_cbCategory;
	QComboBox* m_cbCategorySub;
	QLineEdit* m_lePrice;

	QPushButton* m_bAdd;
	QPushButton* m_bClear;  // TODO: Remove this button?
};

