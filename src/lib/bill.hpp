#pragma once

#ifndef NDEBUG
#include <iostream>
#endif

#include <string>
#include <nlohmann/json.hpp>

struct bill {
	std::string date;
	std::string shop;

	float price;
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(bill, date, shop, price)
// TODO: Add debug output with json.

std::string todaysDate();