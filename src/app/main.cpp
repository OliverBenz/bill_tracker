#include <QApplication>

#include "lib/dataHandler.hpp"
#include "ui/application.hpp"
//#include "ui/viewSelector.hpp"

int main(int argc, char** argv) {
	lib::initializeProgram();

	QApplication app(argc, argv);

	Application widget;
	//viewSelector widget;
	widget.show();

	return app.exec();
}
