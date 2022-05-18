#pragma once

#include <string>

namespace lib {

/*!
 * @brief Get todays date.
 * @return Todays date in format "DD.MM.YYYY".
 */
std::string todaysDate();

/*!
 * @brief Check wether a entered date is valid or not.
 * @param date Date in string format.
 * @return True if the date is valid and is formatted propoerly.
 * @note   Valid format is "DD.MM.YYYY".
 */
bool dateIsValid(const std::string& date);

}
