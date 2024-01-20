#include "addBillModel.hpp"

#include <algorithm>
#include <sstream>
#include <locale>

AddBillModel::AddBillModel(){
    m_shops = lib::getShops();
    m_categories = lib::getCategories();
};

std::vector<lib::shop>& AddBillModel::getShops() {
    return m_shops;
}

std::vector<lib::category>& AddBillModel::getCategories() {
    return m_categories;
}


std::vector<lib::usage> AddBillModel::getUsages(unsigned category) {
    return lib::getUsages(category);
}

void AddBillModel::addNewBill(const lib::bill& bill){
    lib::addBill(bill);
}

bool AddBillModel::isValidBillInfo(std::string date, unsigned , unsigned , unsigned , std::string ) {
    if(!lib::dateIsValid(date)) {
        return false;
    }
    return true;
    // TODO: Check other inputs
}

lib::bill AddBillModel::constructBill(std::string date, unsigned shop, unsigned, unsigned subCategory, std::string price) {

    // Construct bill struct
    lib::bill bill;
    bill.date = date;
    bill.shopId = shop;
    bill.usageId = subCategory;

    // Convert price to float
    std::replace(price.begin(), price.end(), ',', '.');  // Use decimal dot for price
    bill.price = 0.0f;

    for(auto& c :price) {
        if(c == ',')
            c = '.';
    }
    // Input mask always used ',', we want a conversion using a fixed locale.
    std::stringstream stream(price);
    stream.imbue(std::locale::classic());
    stream >> bill.price;

    return bill;
}
