#pragma once

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

class aboutDialog : public QDialog {
	Q_OBJECT

public:
	aboutDialog(QWidget* parent = nullptr);
	~aboutDialog();

private:
	QVBoxLayout* m_lMain;

	QLabel* m_laAppName;
	QLabel* m_laAuthor;
};
