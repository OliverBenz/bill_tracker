#include "billTableModel.hpp"

#include "lib/dataHandler.hpp"

billTableModel::billTableModel() {
	getAllData();
}

const std::vector<lib::bill>& billTableModel::getAllData() {
	m_data = lib::getBills();

	// Get shops
	for(const auto& shop : lib::getShops()) {
		m_shops.insert({shop.id, shop.name});
	}

    // Get usages
    for (const auto& usage : lib::getUsages()) {
        m_usages.insert({usage.id, usage.name});
		m_usageCategory.insert({usage.id, usage.categoryId});
    }

    // Get categories
	for(const auto& cat : lib::getCategories()) {
		m_categories.insert({cat.id, cat.name});
	}

	return m_data;
}


void billTableModel::insertBill(const lib::bill& bill) {
	m_data.emplace_back(bill);
}

const std::string& billTableModel::getShopName(const unsigned shopId) {
	// TODO: Check available in map
	return m_shops.at(shopId);
}

const std::string& billTableModel::getCategoryName(const unsigned usageId) {
	// TODO: Check available in map
	return m_categories.at(m_usageCategory.at(usageId));
}

const std::string& billTableModel::getUsageName(const unsigned usageId) {
	// TODO: Check available in map
	return m_usages.at(usageId);
}
