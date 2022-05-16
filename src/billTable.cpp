#include "billTable.hpp"

#include "lib/fileHandling.hpp"

billTable::billTable() {
	m_shops	= lib::getShops();
	m_categories = lib::getCategories();
}

int billTable::rowCount(const QModelIndex& parent) const {
	if(parent.isValid())  // TODO: Is this valid?
		return 0;

	return static_cast<int>(m_data.size());
}

int billTable::columnCount(const QModelIndex& parent) const {
	if(parent.isValid())
		return 0;

	// date - shop - price - category - subcategory
	return 5;
}

QVariant billTable::data(const QModelIndex& index, int role) const {
	if(role != Qt::DisplayRole)
		return QVariant::Invalid;

	const std::size_t row = static_cast<std::size_t>(index.row());
	switch(index.column()) {
		case 0:
			return m_data[row].date.c_str();
		case 1:
			return m_data[row].shop;
		case 2:
			return m_data[row].price;
		case 3:
			return m_data[row].category;
		case 4:
			return m_data[row].subCategory;
		default:
			return QVariant::Invalid;
	}
}

bool billTable::insert(const lib::bill& newBill) {
	// beginInsertRows();

	m_data.push_back(newBill);

	// endInsertRows();

	return true;
}
