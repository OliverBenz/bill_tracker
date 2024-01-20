#include "dataHandler.hpp"
#include "fileAccessHandler.hpp"
#include "billDbHandler.hpp"

#include <memory>

namespace lib {

//! Helper function to get the proper access handler.
//! \note Will be updated to also be able to return a database access handler.
static std::unique_ptr<IDataAccessHandler> getAccessHandler() {
	return std::make_unique<fileAccessHandler>();
}

void initializeProgram() {
	const auto accessHandler = getAccessHandler();
	accessHandler->initializeProgram();
}

bool addBill(const bill& newBill) {
	const auto accessHandler = std::make_unique<billDbHandler>();
	return accessHandler->addBill(newBill.date, newBill.price, newBill.shopId, newBill.usageId);
}

std::vector<bill> getBills(const std::string& date) {
	const auto accessHandler = std::make_unique<billDbHandler>();
	return accessHandler->getBills(date);
}

std::vector<shop> getShops() {
	const auto accessHandler = std::make_unique<billDbHandler>();
	return accessHandler->getShops();
}

std::vector<usage> getUsages(unsigned categoryId) {
    const auto accessHandler = std::make_unique<billDbHandler>();
    return accessHandler->getUsages(categoryId);
}

std::vector<category> getCategories() {
	const auto accessHandler = std::make_unique<billDbHandler>();
	return accessHandler->getCategories();
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
