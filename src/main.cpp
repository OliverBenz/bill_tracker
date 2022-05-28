#include <QApplication>

#include "addBillWidget.hpp"
//#include "displayWindow.hpp"
#include "mainWindow.hpp"

int main(int argc, char** argv){
	QApplication application(argc, argv);
	mainWindow widget;
	widget.show();

	return application.exec();
}
