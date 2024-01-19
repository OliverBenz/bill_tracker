#include <QApplication>

#include "lib/dataHandler.hpp"
#include "ui/application.hpp"

#include "lib/billDbHandler.hpp"
#include <iostream>
int main(int argc, char** argv) {
	lib::initializeProgram();

    /*
    {
        lib::billDbHandler db;
        db.addShop("Astroshop");
        db.addShop("Amazon");
        db.addShop("Interspar");
        db.addCategory("Groceries");
        db.addUsage("Necessities", 1);
        db.addCategory("Work");
        db.addUsage("Omicron", 2);
        db.addUsage("IQOQI", 2);

        db.addBill("15.01.2024", 23.95f, 3, 1, "");

        const auto result = db.getUsages();
        for (const auto& elem: result) {
            std::cout << elem.id << "  " << db.getCategoryName(elem.categoryId) << "  " << elem.name << "\n";
        }
        for (unsigned i = 1; i != 4; ++i) {
            std::cout << db.getShopName(i) << "\n";
        }

        std::cout << db.getUsageName(1) << "\n";

    }
     */

	QApplication app(argc, argv);

	Application widget;
	widget.show();

	return app.exec();
}
