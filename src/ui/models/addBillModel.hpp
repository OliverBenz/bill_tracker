#pragma once

#include "lib/types/category.hpp"
#include "lib/types/usage.hpp"
#include "lib/types/bill.hpp"
#include "lib/types/shop.hpp"

#include "lib/dataHandler.hpp"
#include "lib/dateHandler.hpp"

class AddBillModel {
public:
    AddBillModel();

    std::vector<lib::shop>& getShops();
    std::vector<lib::category>& getCategories();
    std::vector<lib::usage> getUsages(unsigned category = 0);

    void addNewBill(const lib::bill& bill);

    static bool isValidBillInfo(std::string date, unsigned , unsigned , unsigned , std::string );
    static lib::bill constructBill(std::string date, unsigned shop, unsigned category, unsigned subCategory, std::string price);

private:
    std::vector<lib::shop> m_shops;
    std::vector<lib::category> m_categories;
};
