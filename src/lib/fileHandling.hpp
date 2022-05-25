#pragma once

#include <vector>

#include "bill.hpp"
#include "shop.hpp"
#include "category.hpp"

namespace lib {

// List of files we store.
enum class file {
	bills,
	data,
	settings
};

bool addBillToFile(const bill& newBill);

std::vector<bill> getBills(const std::string& date);
std::vector<shop> getShops();

std::vector<category> getCategories();
std::vector<subcategory> getSubCategories(int categoryId);

// Config data
//! Get the application author name from the config file.
std::string getAppAuthor();

//! Ge the application name from the config file.
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

}
