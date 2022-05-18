#include "dateHandler.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>

namespace lib {

std::string todaysDate()
{
	const auto now = std::chrono::system_clock::now();
	const auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%d.%m.%Y");
	return ss.str();
}

bool dateIsValid(const std::string& date) {
	// TODO: Implement
	for(const auto& c : date) {
		// Placeholder because "date" cannot be unused.
		if(c == 'a')
			return false;
	}
	return true;
}

}
