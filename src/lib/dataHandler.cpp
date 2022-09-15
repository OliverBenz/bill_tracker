#include "dataHandler.hpp"
#include "fileAccessHandler.hpp"

#include <memory>

namespace lib {

//! Helper function to get the proper access handler.
//! \note Will be updated to also be able to return a database access handler.
static std::unique_ptr<IDataAccessHandler> getAccessHandler() {
	return std::make_unique<fileAccessHandler>();
}

bool addBill(const bill& newBill) {
	const auto accessHandler = getAccessHandler();
	return accessHandler->addBill(newBill);
}

std::vector<bill> getBills(const std::string& date) {
	const auto accessHandler = getAccessHandler();
	return accessHandler->getBills(date);
}

std::vector<shop> getShops() {
	const auto accessHandler = getAccessHandler();
	return accessHandler->getShops();
}

std::vector<category> getCategories() {
	const auto accessHandler = getAccessHandler();
	return accessHandler->getCategories();
}

std::vector<subcategory> getSubCategories(int categoryId) {
	const auto accessHandler = getAccessHandler();
	return accessHandler->getSubCategories(categoryId);
}

std::string getAppAuthor() {
	const auto accessHandler = getAccessHandler();
	return accessHandler->getAppAuthor();
}

std::string getAppName() {
	const auto accessHandler = getAccessHandler();
	return accessHandler->getAppName();
}

std::string getFilePath(const file fileName) {
	const auto accessHandler = getAccessHandler();
	return accessHandler->getFilePath(fileName);
}

std::string getFolderPath(const file fileName) {
	const auto accessHandler = getAccessHandler();
	return accessHandler->getFolderPath(fileName);
}

bool setFolderPath(const file fileName, const std::string& path) {
	const auto accessHandler = getAccessHandler();
	return accessHandler->setFolderPath(fileName, path);
}

bool updateFilePath(file fileName, const std::string& newPath) {
	const auto accessHandler = getAccessHandler();
	return accessHandler->updateFilePath(fileName, newPath);
}

bool createBackup() {
	const auto accessHandler = getAccessHandler();
	return accessHandler->createBackup();
}

}
