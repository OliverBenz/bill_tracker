#include "fileHandling.hpp"

#include <set>
#include <sstream>
#include <fstream>

/*
	{
		"bills": [

		],
 		"shops": [

 		]
	}
*/

bool addBillToFile(const bill& newBill) {
	const std::string fileName = "data/data.json";
	std::ifstream input(fileName);

	nlohmann::json jsonFile = nlohmann::json::parse(input);

	if(jsonFile.find("bills") != jsonFile.end())
		jsonFile.at("bills").push_back(newBill);

	std::ofstream output(fileName);
	output << std::setw(4) << jsonFile << std::endl;

	return false;
}

std::vector<bill> getBills(const std::string& date) {
	std::ifstream jsonFile("data/data.json");
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

std::vector<std::string> getShops() {
	std::ifstream jsonFile{"data/data.json"};
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	std::set<std::string> shops;
	for(const nlohmann::json& jBill : json.at("bills")) {
		std::string temp;
		nlohmann::from_json(jBill.at("shop"), temp);
		shops.insert(temp);
	}

	std::vector<std::string> result(shops.begin(), shops.end());

	return result;
}