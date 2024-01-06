#include "billTableModel.hpp"

#include "lib/dataHandler.hpp"

billTableModel::billTableModel() {
	getAllData();
}

const std::vector<lib::bill>& billTableModel::getAllData() {
	m_data = lib::getBills("");

	// Get shops
	for(const auto& shop : lib::getShops()) {
		m_shops.insert({shop.id, shop.name});
	}

	// Get categories and subcats
	for(const auto& cat : lib::getCategories()) {
		m_categories.insert({cat.id, cat.name});

		for(const auto& subcat : lib::getSubCategories(cat.id)) {
			m_subcategories.insert({{cat.id, subcat.id}, subcat.name});
		}
	}

	return m_data;
}


void billTableModel::insertBill(const lib::bill& bill) {
	m_data.emplace_back(bill);
}

const std::string& billTableModel::getShopName(const int shopId) {
	return m_shops.at(shopId);
}

const std::string& billTableModel::getCategoryName(const int categoryId) {
	return m_categories.at(categoryId);
}

const std::string& billTableModel::getSubCategoryName(int categoryId, int subCategoryId) {
	return m_subcategories.at({categoryId, subCategoryId});
}
