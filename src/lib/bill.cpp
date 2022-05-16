#include "bill.hpp"

#include <chrono>
#include <sstream>

namespace bill {

std::string todaysDate()
{
	const auto now = std::chrono::system_clock::now();
	const auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%d.%m.%Y");
	return ss.str();
}

}
