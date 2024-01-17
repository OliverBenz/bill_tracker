#pragma once

#include "lib/types/bill.hpp"
#include "lib/bill.hpp"

#include <map>
#include <vector>
#include <string>

//! Defined operations allowed in the bill table and manages data/communication with database.
class billTableModel {
public:
	billTableModel();

	const std::vector<lib::bill1>& getAllData();

	void insertBill(const lib::bill1& bill);
/*
	bool removeBill(const lib::bill& bill);
	bool removeBill(int billId);

	bool editBill(const int billId, const lib::bill& newInfo);
*/
	const std::string& getShopName(unsigned shopId);
	//! Get the category name of the corresponding usage.
	const std::string& getCategoryName(unsigned usageId);
	const std::string& getUsageName(unsigned usageId);

private:
	std::vector<lib::bill1> m_data;
	// Used to resolve the ids from the bill classes passed to insert().
	std::map<unsigned, std::string> m_shops;
	std::map<unsigned, std::string> m_categories;
    std::map<unsigned, std::string> m_usages;
	std::map<unsigned, unsigned> m_usageCategory; //!< 0-> UsageId, 1->CategoryId
};
