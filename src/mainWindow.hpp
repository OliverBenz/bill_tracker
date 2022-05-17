#pragma once

#include <QWidget>
#include <QMenu>
#include <QVBoxLayout>

#include "inputWindow.hpp"

class mainWindow : public QWidget {
	Q_OBJECT

public:
	mainWindow(QWidget* parent = nullptr);
	~mainWindow();

private:
	QVBoxLayout* m_lMain;
	QMenu* m_menu;

	inputWindow* m_inputWindow;
};
