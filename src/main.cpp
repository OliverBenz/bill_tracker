#include <QApplication>

#include "mainWindow.hpp"
#include "views/viewSelector.hpp"
#include "lib/dataHandler.hpp"

int main(int argc, char** argv) {
	lib::initializeProgram();

	QApplication application(argc, argv);
	mainWindow widget;
	widget.show();

	return application.exec();
}
