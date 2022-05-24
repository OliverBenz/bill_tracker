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
	void updateFolderPath();

private:
	QHBoxLayout* m_lMain;

	QLabel* m_laPathBill;
	QLineEdit* m_lePathBill;
	QPushButton* m_bPathBill;
};
