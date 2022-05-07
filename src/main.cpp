#include <QApplication>

#include "inputWindow.hpp"

int main(int argc, char** argv){
	QApplication application(argc, argv);

	inputWindow widget;
	widget.show();

	return application.exec();
}
