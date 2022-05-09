#pragma once

#include <vector>
#include "bill.hpp"

bool addBillToFile(const bill& newBill);
std::vector<bill> getBills(const std::string& date);
std::vector<std::string> getShops();