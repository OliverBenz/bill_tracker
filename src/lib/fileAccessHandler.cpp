#include "fileAccessHandler.hpp"
#include "dateHandler.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

#include <fmt/format.h>

namespace lib {

// NOTE: We parse whole data file every time we want to read or write anything.
// 		 This is bad but this app will never scale so I don't care.
//       IF wish for fix is there: We could make a separate file for every month like:
//       	"2022-05_data.json", "2022-06_data.json", etc

// TODO: Make path with cmake and setup standard files

bool fileAccessHandler::addBill(const bill& newBill) const {
	const std::string pathBillFile = getFilePath(file::bills);
	std::ifstream input(pathBillFile);

	nlohmann::json jsonFile = nlohmann::json::parse(input);

	if(jsonFile.find("bills") != jsonFile.end())
		jsonFile.at("bills").push_back(newBill);

	std::ofstream output(pathBillFile);
	output << std::setw(4) << jsonFile << std::endl;

	return false;
}

std::vector<bill> fileAccessHandler::getBills(const std::string& date) const {
	const std::string billsFilePath = getFilePath(file::bills);
	if (!std::filesystem::exists(billsFilePath)) {
		initializeProgram();
	}

	std::ifstream jsonFile(billsFilePath);
	nlohmann::json json =  nlohmann::json::parse(jsonFile);

	std::vector<bill> result;
	if (!date.empty()) {
		for(const nlohmann::json& jsonBill : json.at("bills")) {
			if(jsonBill.at("date") == date) {
				bill temp;
				nlohmann::from_json(jsonBill, temp);

				result.push_back(temp);
			}
		}
	} else {
		json.at("bills").get_to(result);
	}

	return result;
}

std::vector<shop> fileAccessHandler::getShops() const {
	std::ifstream jsonFile(getFilePath(file::data));
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	std::vector<shop> shops;
	nlohmann::from_json(json.at("shops"), shops);

	return shops;
}

std::vector<category> fileAccessHandler::getCategories() const {
	std::ifstream jsonFile(getFilePath(file::data));
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find("categories") == json.end())
		return {};

	std::vector<category> categories;
	nlohmann::from_json(json.at("categories"), categories);

	return categories;
}

std::vector<subcategory> fileAccessHandler::getSubCategories(int categoryId) const {
	std::ifstream jsonFile(getFilePath(file::data));
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find("categories") == json.end())
		return {};

	std::vector<subcategory> subcats;
	for(const auto& j : json.at("categories")) {
		const int id = j.at("id").get<int>();
		if(id == categoryId && j.find("subCategories") != j.end()) {
			nlohmann::from_json(j.at("subCategories"), subcats);
			break;
		}
	}

	return subcats;
}

void fileAccessHandler::initializeProgram() const {
	if(std::filesystem::exists(m_filenameConfig)) {
		return;
	}

	// Copy settings.json file.
	const std::string settingsPath = getFolderPath(file::settings);
	std::filesystem::create_directories(settingsPath);
	std::filesystem::copy_file(RESOURCE_PATH_SETTINGS, settingsPath + "/settings.json");

	// NOTE: Quick solution for convenience. When no settings file, give user chance to select directory.
	const auto initEmptyJsonFile = [&](const file fileType, const std::string content) {
		std::ofstream file(getFilePath(fileType));
		file << "{ " << content << "}\n";
		file.close();
	};
	initEmptyJsonFile(file::bills, "\n\t\"bills\": []\n");
	initEmptyJsonFile(file::data, "\n\t\"shops\": [],\n\t\"categories\": []\n");
}

std::string fileAccessHandler::getAppAuthor() const {
	std::ifstream jsonFile(m_filenameConfig);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	constexpr char app[] = "application";
	constexpr char author[] = "author";

	if(json.find(app) == json.end())
		return "";

	nlohmann::json jsonApp = json.at(app);
	if(jsonApp.find(author) == jsonApp.end())
		return "";

	return jsonApp.at(author);
}

std::string fileAccessHandler::getAppName() const {
	std::ifstream jsonFile(m_filenameConfig);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	constexpr char app[] = "application";
	constexpr char name[] = "name";

	if(json.find(app) == json.end())
		return "";

	nlohmann::json jsonApp = json.at(app);
	if(jsonApp.find(name) == jsonApp.end())
		return "";

	return jsonApp.at(name);
}

std::string fileAccessHandler::getFilePath(const file fileName) const {
	if(fileName == file::settings)
		return {m_filenameConfig};

	return getFolderPath(fileName) + "/" + getFileName(fileName);
}

std::string fileAccessHandler::getFolderPath(const file fileName) const {
	// Config file always at same position
	if (fileName == file::settings){
		std::string path = std::string(m_filenameConfig);
		path.resize(path.rfind('/'));
		return path;
	}

	std::string jsonElemName;
	switch (fileName) {
		case file::bills:
			jsonElemName = "pathBills";
			break;
		case file::data:
			jsonElemName = "pathData";
			break;
		default:
			return "";
	}

	// Read filepath from config file
	std::ifstream jsonFile(m_filenameConfig);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if (json.find(jsonElemName) == json.end())
		return "";

	return json.at(jsonElemName);
}

bool fileAccessHandler::setFolderPath(const file fileName, const std::string& path) const {
	if(fileName == file::settings)
		return false;

	const std::string settingsFile = getFilePath(file::settings);
	std::ifstream input(settingsFile);
	nlohmann::json jsonFile = nlohmann::json::parse(input);

	std::string fieldName;
	switch(fileName){
		case file::bills:
			fieldName = "pathBills";
			break;
		case file::data:
			fieldName = "pathData";
			break;
		case file::settings:
		default:
			return false;
	}

	if(jsonFile.find(fieldName) != jsonFile.end()) {
		jsonFile.at(fieldName) = path;
	} else {
		jsonFile.push_back({fieldName, path});
	}

	std::ofstream output(settingsFile);
	output << std::setw(4) << jsonFile << std::endl;

	return false;
}

bool fileAccessHandler::updateFilePath(file fileName, const std::string& newPath) const {
	const std::string oldPath = getFolderPath(fileName);
	if(newPath == oldPath)
		return true;

	if(!std::filesystem::exists(newPath)) {
		std::cerr << "Error: New path does not exist.\n";
		return false;
	}

	try {
		std::filesystem::rename(getFilePath(fileName), newPath + "/" + getFileName(fileName));
	} catch (std::filesystem::filesystem_error& e) {
		// A simple rename can fail if the new path in on a different filesystem.
		try {
			std::filesystem::copy(getFilePath(fileName), newPath + "/" + getFileName(fileName));
			std::filesystem::remove(getFilePath(fileName));
		} catch (std::filesystem::filesystem_error& e1) {
			std::cerr << "Error: Could not move file to new path\n" << e1.what();
			return false;
		}
	}

	if(setFolderPath(fileName, newPath))
		return true;


	// TODO: File already moved but path not updated!
	return false;
}

bool fileAccessHandler::createBackup() const {
	const std::string fileSettings = getFilePath(file::settings);
	std::ifstream input(fileSettings);
	nlohmann::json json = nlohmann::json::parse(input);

	if(json.find("pathBills") == json.end() || json.find("pathData") == json.end())
		return false;

	const std::string fileBills = json.at("pathBills");
	const std::string fileData = json.at("pathData");

	const std::string backupDir = std::string(m_projectPath) + "/backup";
	if(!std::filesystem::exists(backupDir)){
		std::filesystem::create_directory(backupDir);
	}

	// Create backup directory name
	std::string dirName = fmt::format("{}/[{}]backup", backupDir, todaysDate());
	if(std::filesystem::exists(dirName)) {
		std::size_t backupTracker = 1;
		while(std::filesystem::exists(fmt::format("{}({})", dirName, backupTracker))) {
			++backupTracker;
		}
		dirName += "(" + std::to_string(backupTracker) + ")";
	}

	std::filesystem::create_directory(dirName);

	try {
		std::filesystem::copy(getFilePath(file::data), dirName + "/" + getFileName(file::data));
		std::filesystem::copy(getFilePath(file::bills), dirName + "/" + getFileName(file::bills));
		std::filesystem::copy(getFilePath(file::settings), dirName + "/" + getFileName(file::settings));
	} catch (std::filesystem::filesystem_error& e) {
		std::filesystem::remove_all(dirName);  // Cleanup
		std::cerr << "Error: Could not create backup.\n" << e.what();
		return false;
	}

	return true;
}

std::string fileAccessHandler::getFileName(const file fileName) {
	switch(fileName) {
		case file::bills:
			return "bills.json";
		case file::data:
			return "data.json";
		case file::settings:
			return "settings.json";
	}
	return "";
}

#ifndef NDEBUG
void fileAccessHandler::writeDebugData() const {
	subcategory subCatA{0, "Sub Test A"};
	subcategory subCatB{1, "Sub Test B"};
	category catA {0, "Test A", {subCatA, subCatB}};
	shop sh{0, "Shop A"};

	bill b{"25.12.1999", 0, 0, 0, 0.99f};
	//addShop(shop);  // TODO: Implement these two
	//addCategory{catA};
	addBill(b);
}
#endif

}
