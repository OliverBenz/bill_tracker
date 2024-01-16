#pragma once

#include <string>

namespace lib {

struct bill1 {
	unsigned id;
	unsigned shopId;
	unsigned usageId;

	float price;
	std::string date;
	std::string filename;
};

}