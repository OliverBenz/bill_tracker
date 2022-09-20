#include "billTableModel.hpp"

#include "../lib/dataHandler.hpp"

#include <fmt/core.h>
billTableModel::billTableModel() {
	beginInsertColumns(QModelIndex(), 0, 5);
	insertColumns(0, 5);
	endInsertColumns();

	getAllData();
}

void billTableModel::getAllData() {
	m_data = lib::getBills("");

	// Get shops
	m_shops.insert({-1, "---"});
	for(const auto& shop : lib::getShops()) {
		m_shops.insert({shop.id, shop.name});
	}

	// Get categories and subcats
	m_categories.insert({-1, "---"});
	for(const auto& cat : lib::getCategories()) {
		m_categories.insert({cat.id, cat.name});

		m_subcategories.insert({{cat.id, -1}, "---"});
		for(const auto& subcat : lib::getSubCategories(cat.id)) {
			m_subcategories.insert({{cat.id, subcat.id}, subcat.name});
		}
	}
}

int billTableModel::rowCount(const QModelIndex& parent) const {
	if(parent.isValid())
		return 0;

	return static_cast<int>(m_data.size());
}

int billTableModel::columnCount(const QModelIndex& parent) const {
	if(parent.isValid())
		return 0;

	// #{date, shop, price, category, subcategory}
	return 5;
}

QVariant billTableModel::data(const QModelIndex& index, int role) const {
	if(role != Qt::DisplayRole)
		return QVariant::Invalid;

	const std::size_t row = static_cast<std::size_t>(index.row());
	switch(index.column()) {
		case 0:
			return m_data[row].date.c_str();
		case 1:
			return m_shops.at(m_data[row].shop).c_str();
		case 2:
			return fmt::format("{: >5.2f} €", m_data[row].price).c_str();
		case 3:
			return m_categories.at(m_data[row].category).c_str();
		case 4:
			return m_subcategories.at({m_data[row].category, m_data[row].subCategory}).c_str();
		default:
			return QVariant::Invalid;
	}
}
QVariant billTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	const std::array<std::string, 5> headers = {"Date", "Shop", "Price", "Category", "Subcategory"};

	if(orientation == Qt::Horizontal) {
		if(section >= 0 && section <= 4) {
			return headers[static_cast<std::size_t>(section)].c_str();
		}
	}
	
	if(role) {}

	return QVariant::Invalid;
}

bool billTableModel::insert(const lib::bill& newBill) {
	// beginInsertRows();

	m_data.push_back(newBill);

	// endInsertRows();

	return true;
}
