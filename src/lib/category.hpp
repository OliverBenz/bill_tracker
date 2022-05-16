#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace lib {

struct subcategory {
	int id = -1;        // -1 if no subcategory exists
	std::string name;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(subcategory, id, name)

struct category {
	int id;
	std::string name;

	std::vector<subcategory> subCategories;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(category, id, name, subCategories)

}
