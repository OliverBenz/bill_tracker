#include <QApplication>

#include "lib/dataHandler.hpp"
#include "lib/appConfig.hpp"
#include "ui/application.hpp"

#include "lib/billDbHandler.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if(lib::initializeConfig()) {
        std::cout << "[App] Newly created configuration file.\n";
    }
    if(lib::initializeProgram()) {
        std::cout << "[App] Newly created database file.\n";
    }

    {
        lib::billDbHandler db;
        db.addShop("MPreis");
        db.addShop("Amazon");
        db.addShop("Interspar");
        db.addCategory("Groceries");
        db.addUsage("Necessities", 1);

        // db.addBill("15.01.2024", 23.95f, 3, 1, "");

        // const auto result = db.getUsages();
        // for (const auto& elem: result) {
        //     std::cout << elem.id << "  " << db.getCategoryName(elem.categoryId) << "  " << elem.name << "\n";
        // }
        // for (unsigned i = 1; i != 4; ++i) {
        //     std::cout << db.getShopName(i) << "\n";
        // }

        // std::cout << db.getUsageName(1) << "\n";
    }

	QApplication app(argc, argv);

	Application widget;
	widget.show();

	return app.exec();
}
