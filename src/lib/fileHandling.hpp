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
	config
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

//! Get path where file is stored from the config.json file (with fileName).
std::string getFilePath(file fileName);

//! Get path where file is stored from the config.json file (without fileName).
std::string getFolderPath(file fileName);

}
