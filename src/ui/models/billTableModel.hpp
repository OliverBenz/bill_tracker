#pragma once

#include "lib/bill.hpp"

#include <map>
#include <vector>
#include <string>

//! Defined operations allowed in the bill table and manages data/communication with database.
class billTableModel {
public:
	billTableModel();

	const std::vector<lib::bill>& getAllData();

	void insertBill(const lib::bill& bill);
/*
	bool removeBill(const lib::bill& bill);
	bool removeBill(int billId);

	bool editBill(const int billId, const lib::bill& newInfo);
*/
	const std::string& getShopName(int shopId);
	const std::string& getCategoryName(int categoryId);
	const std::string& getSubCategoryName(int categoryId, int subCategoryId);

private:
	std::vector<lib::bill> m_data;
	// Used to resolve the ids from the bill classes passed to insert().
	std::map<int, std::string> m_shops;
	std::map<int, std::string> m_categories;

	// Category id - pair of (subcat.id, subcat.name)
	std::map<std::pair<int, int>, std::string> m_subcategories;
};

