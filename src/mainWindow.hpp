#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "inputWindow.hpp"
#include "toolBar.hpp"

class mainWindow : public QWidget {
	Q_OBJECT

public:
	mainWindow(QWidget* parent = nullptr);
	~mainWindow();

private:
	QVBoxLayout* m_lMain;

	toolBar* m_menuBar;
	inputWindow* m_inputWindow;
};
