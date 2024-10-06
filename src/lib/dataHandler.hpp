#pragma once

#include <vector>

#include "types/bill.hpp"
#include "types/category.hpp"
#include "types/file.hpp"
#include "types/shop.hpp"
#include "types/usage.hpp"

namespace lib {

//! Add a new bill to the system.
bool addBill(const bill& newBill);

//! Get a list of bills from a specific date. All bills if date is empty.
std::vector<lib::bill> getBills(const std::string& date = "");

//! Get a list of all shops.
std::vector<shop> getShops();

//! Get a list of all usages.
std::vector<usage> getUsages(unsigned categoryId = 0);

//! Get a list of all categories.
std::vector<category> getCategories();

// ----- Application data -----
//! Setup all required infrastructure for the program if necessary.
void initializeProgram();

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
