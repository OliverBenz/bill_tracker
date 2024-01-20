#pragma once

#include "types/usage.hpp"
#include "types/category.hpp"
#include "types/bill.hpp"
#include "types/shop.hpp"

#include <memory>
#include <string>
#include <vector>

namespace lib {

// TODO: All these std::cout should be replaced with logger (see my github)
class billDbHandler {
public:
	billDbHandler();
    ~billDbHandler();

// Add row to table
    bool addUsage(const std::string& name, int categoryId);
    bool addShop(const std::string& name);
    bool addCategory(const std::string& name);
    bool addBill(const std::string& date, float price, unsigned shopId, unsigned usageId, const std::string& filename = "");

// Get whole table
    std::vector<usage> getUsages(unsigned categoryId = 0);
    std::vector<shop> getShops();
	std::vector<category> getCategories();  //!< TODO: Rename struct
    std::vector<bill> getBills(const std::string& date = "", unsigned categoryId = 0, unsigned shopId = 0);


// Get one row from table


// Get column from table.
    //! \note throws invalid_argument if id does not exist.
    std::string getUsageName(unsigned id);

    //! \note throws invalid_argument if id does not exist.
    std::string getShopName(unsigned id);

    //! \note throws invalid_argument if id does not exist.
    std::string getCategoryName(unsigned id);

private:
    //! Protect against sql-injection and make sure data properly formatted.
    std::string sanitize(const std::string& value);

    //! \note throws invalid_argument if the database file cannot be found.
	void open();

    class SqlitePimpl;
	std::unique_ptr<SqlitePimpl> m_sqlite;  //!< Pimpl to hide the SQLite implementation.
};

}