#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace lib {

struct bill {
	std::string date;
	int shop;
	int category;
	int subCategory;

	float price;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(bill, date, shop, price, category, subCategory)

std::string todaysDate();

}
