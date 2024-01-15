#pragma once

#include "lib/bill.hpp"
#include "lib/shop.hpp"
#include "lib/category.hpp"
#include "lib/dataHandler.hpp"
#include "lib/dateHandler.hpp"

class AddBillModel {
public:
    AddBillModel();

    std::vector<lib::shop>& getShops();
    std::vector<lib::category>& getCategories();
    std::vector<lib::subcategory> getSubCategories(const int category);

    void addNewBill(const lib::bill& bill);

    static bool isValidBillInfo(std::string date, int , int , int , std::string );
    static lib::bill constructBill(std::string date, int shop, int category, int subCategory, std::string price);

private:
    std::vector<lib::shop> m_shops;
    std::vector<lib::category> m_categories;
};
