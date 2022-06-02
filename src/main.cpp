#include <QApplication>

#include "addBillWidget.hpp"
//#include "displayWindow.hpp"
#include "mainWindow.hpp"
#include "views/viewSelector.hpp"

int main(int argc, char** argv){
	QApplication application(argc, argv);
	mainWindow widget;
	//viewSelector widget;
	widget.show();

	return application.exec();
}
