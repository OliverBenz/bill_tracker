#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

class inputWindow : public QWidget {
	Q_OBJECT

public:
	inputWindow(QWidget* parent = nullptr);
	~inputWindow();

private slots:
	void clear();
	void add();

private:
	QVBoxLayout* m_lMain;
	QHBoxLayout* m_lInputs;
	QHBoxLayout* m_lButtons;

	QLineEdit* m_leDate;  // TODO: Update to calendar type widget
	QComboBox* m_cbShop;
	QLineEdit* m_lePrice;

	QPushButton* m_bAdd;
	QPushButton* m_bClear;
};
