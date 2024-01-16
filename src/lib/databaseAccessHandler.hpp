#pragma once

#include <memory>
#include <string>
#include "bill.hpp"

namespace lib {

// TODO: All these std::cout should be replaced with logger (see my github)
class billDbHandler {
public:
	billDbHandler();
    ~billDbHandler();

    // TODO: Is better to pass usageId in app or name?
    /*void writeBill(id, date, shop, usageId, filename);*/
    bool addCategory(const std::string& name);
    bool addUsage(const std::string& name, int categoryId);
    bool addShop(const std::string& name);
    bool addBill(const std::string& date, float price, unsigned shopId, unsigned usageId, const std::string& filename = "");

    //! Get last n bills by date or all (-1)
    void getBills(int count = -1);

private:
    //! Protect against sql-injection and make sure data properly formatted.
    std::string sanitize(const std::string& value);
	void open();

    class SqlitePimpl;
	std::unique_ptr<SqlitePimpl> m_sqlite;  //!< Pimpl to hide the SQLite implementation.
};

void readDataTest();

}