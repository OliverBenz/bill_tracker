#include "fileHandling.hpp"
#include "dateHandler.hpp"

#include <set>
#include <sstream>
#include <fstream>

namespace lib {

// TODO: We parse whole data file every time we want to read or write anything.
// 		 This is awful but this app will never scale so I don't care.
//       IF wish for fix is there: We could make a separate file for every month like:
//       	"2022-05_data.json", "2022-06_data.json", etc

constexpr char filenameGlobal[] = "data/global.json";
constexpr char filenameData[] = "data/data.json";
constexpr char filenameConfig[] = "data/config.json";  // TODO: Have this at special place - Other paths defined in here

bool addBillToFile(const bill& newBill) {
	std::ifstream input(filenameData);

	nlohmann::json jsonFile = nlohmann::json::parse(input);

	if(jsonFile.find("bills") != jsonFile.end())
		jsonFile.at("bills").push_back(newBill);

	std::ofstream output(filenameData);
	output << std::setw(4) << jsonFile << std::endl;

	return false;
}

std::vector<bill> getBills(const std::string& date) {
	std::ifstream jsonFile(filenameData);
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
	std::ifstream jsonFile(filenameGlobal);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	std::vector<shop> shops;
	nlohmann::from_json(json.at("shops"), shops);

	return shops;
}

std::vector<category> getCategories() {
	std::ifstream jsonFile(filenameGlobal);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	std::vector<category> categories;
	nlohmann::from_json(json.at("categories"), categories);

	return categories;
}

std::vector<subcategory> getSubCategories(int categoryId) {
	std::ifstream jsonFile(filenameGlobal);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find("categories") == json.end())
		return {};

	std::vector<subcategory> subcats;
	for(const auto& j : json.at("categories")) {
		const int id = j.at("id").get<int>();
		if(id == categoryId) {
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

}
