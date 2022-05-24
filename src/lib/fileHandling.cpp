#include "fileHandling.hpp"
#include "dateHandler.hpp"

#include <set>
#include <sstream>
#include <fstream>

namespace lib {

// NOTE: We parse whole data file every time we want to read or write anything.
// 		 This is awful but this app will never scale so I don't care.
//       IF wish for fix is there: We could make a separate file for every month like:
//       	"2022-05_data.json", "2022-06_data.json", etc

// Config will always be here
// TODO: General path
// TODO: Make path with cmake and setup standard files
constexpr char filenameConfig[] = "/home/oliver/.billtracker/data/settings.json";  // TODO: Have this at special place - Other paths defined in here

bool addBillToFile(const bill& newBill) {
	const std::string pathBillFile = getFilePath(file::bills);

	std::ifstream input(pathBillFile);

	nlohmann::json jsonFile = nlohmann::json::parse(input);

	if(jsonFile.find("bills") != jsonFile.end())
		jsonFile.at("bills").push_back(newBill);

	std::ofstream output(pathBillFile);
	output << std::setw(4) << jsonFile << std::endl;

	return false;
}

std::vector<bill> getBills(const std::string& date) {
	std::ifstream jsonFile(getFilePath(file::bills));
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

std::vector<shop> getShops() {
	std::ifstream jsonFile(getFilePath(file::data));
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	std::vector<shop> shops;
	nlohmann::from_json(json.at("shops"), shops);

	return shops;
}

std::vector<category> getCategories() {
	std::ifstream jsonFile(getFilePath(file::data));
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find("categories") == json.end())
		return {};

	std::vector<category> categories;
	nlohmann::from_json(json.at("categories"), categories);

	return categories;
}

std::vector<subcategory> getSubCategories(int categoryId) {
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

std::string getAppAuthor() {
	std::ifstream jsonFile(filenameConfig);
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

std::string getAppName() {
	std::ifstream jsonFile(filenameConfig);
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

std::string getFilePath(const file fileName) {
	const std::string path = getFolderPath(fileName);

	switch(fileName) {
		case file::bills:
			return path + std::string("/bills.json");
		case file::data:
			return path + std::string("/data.json");
		default:
			return "";
	}
}

std::string getFolderPath(const file fileName) {
	// Config file always at same position
	if(fileName == file::config)
		return std::string(filenameConfig);

	std::string jsonElemName;
	switch(fileName) {
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
	std::ifstream jsonFile(filenameConfig);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find(jsonElemName) == json.end())
		return "";

	return json.at(jsonElemName);

}

}
