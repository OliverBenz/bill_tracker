#pragma once

#include <vector>

#include "file.hpp"
#include "bill.hpp"
#include "shop.hpp"
#include "category.hpp"

namespace lib {

//! Add a new bill to the system.
bool addBill(const bill& newBill);

//! Get a list of bills from a specific date. All bills if date is empty.
std::vector<bill> getBills(const std::string& date);

//! Get a list of all shops.
std::vector<shop> getShops();
//! Get a list of all categories.
std::vector<category> getCategories();
//! Get a list of all subcategories of a specific category.
std::vector<subcategory> getSubCategories(int categoryId);

// ----- Application data -----
//! Setup all required infrastructure for the program if necessary.
void initializeProgram();

//! Get the application author name from the config file.
std::string getAppAuthor();

//! Get the application name from the config file.
std::string getAppName();

//! Get path where file is stored from the settings.json file (with fileName).
std::string getFilePath(file fileName);

//! Get path where file is stored from the settings.json file (without fileName).
std::string getFolderPath(file fileName);

//! Set the path of the specified file to the specified path in the settings.json file.
bool setFolderPath(file fileName, const std::string& path);

/*!
* @brief  Move the file to a new location and update the path in the settings.json file.
* @param fileName The file to update.
* @param newPath New path where to move to.
* @return False if an error occurred.
*/
bool updateFilePath(file fileName, const std::string& newPath);


// Backup
bool createBackup();

}
