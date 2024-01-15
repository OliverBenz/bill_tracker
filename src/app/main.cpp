#include <QApplication>

#include "lib/dataHandler.hpp"
#include "ui/application.hpp"

int main(int argc, char** argv) {
	lib::initializeProgram();

	QApplication app(argc, argv);

	Application widget;
	widget.show();

	return app.exec();
}
