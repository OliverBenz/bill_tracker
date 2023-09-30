#include <QApplication>

#include "lib/dataHandler.hpp"
#include "ui/mainWindow.hpp"
// #include "ui/viewSelector.hpp"

int main(int argc, char** argv) {
	lib::initializeProgram();

	QApplication application(argc, argv);

	mainWindow widget;
	//viewSelector widget;
	widget.show();

	return application.exec();
}
