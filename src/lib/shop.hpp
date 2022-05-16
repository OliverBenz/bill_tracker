#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace bill {

struct shop {
	int id;
	std::string name;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(shop, id, name)

}