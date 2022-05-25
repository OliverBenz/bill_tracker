#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class settingsWindow : public QWidget {
	Q_OBJECT

public:
	settingsWindow(QWidget* parent = nullptr);
	~settingsWindow();

private slots:
	//! Get and display data from settings file.
	void fillStandardData();
	void openFileExplorerBills();

	void save();
	void cancel();

private:
	//! Set the new folder path in settings file.
	void updateBillsPath();

private:
	QVBoxLayout* m_lMain;

	QHBoxLayout* m_lPathBill;
	QLabel* m_laPathBill;
	QLineEdit* m_lePathBill;
	QPushButton* m_bPathBill;

	QHBoxLayout* m_lExitButtons;
	QPushButton* m_bSave;
	QPushButton* m_bCancel;
};
