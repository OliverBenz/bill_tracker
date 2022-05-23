#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

class settingsWindow : public QWidget {
	Q_OBJECT

public:
	settingsWindow(QWidget* parent = nullptr);
	~settingsWindow();

private:
	QHBoxLayout* m_lMain;

	QLabel* m_laFolderPath;
	QLineEdit* m_leFolderPath;
};
