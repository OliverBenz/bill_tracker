#include "billDbHandler.hpp"

#include <format>
#include <iostream>
#include <sqlite3.h>
#include <cassert>

namespace lib {

class billDbHandler::SqlitePimpl {
public:
    // TODO: Avoid raw pointer or make copy/move safe
    sqlite3* m_db{nullptr};
};


billDbHandler::billDbHandler()
    : m_sqlite(std::make_unique<billDbHandler::SqlitePimpl>()) {
	open();
}

billDbHandler::~billDbHandler() {
	sqlite3_close(m_sqlite->m_db);
    m_sqlite->m_db = nullptr;
}

bool billDbHandler::tableExists(const std::string& name) {
    static constexpr char QUERY[] = "SELECT name FROM sqlite_master WHERE type='table' AND name='{}'";

    bool exists = false;
    sqlite3_stmt* stmt;
    const auto query = std::format(QUERY, name);
    if (sqlite3_prepare_v2(m_sqlite->m_db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = true;
        }
        sqlite3_finalize(stmt);
    }
    return exists;
}

bool billDbHandler::initializeProgram() {
	static constexpr char QUERY_CREATE_ALL[] = R"(
	CREATE TABLE shops(
        id INTEGER UNIQUE PRIMARY KEY,
        name TEXT UNIQUE
    );

    CREATE TABLE category(
        id INTEGER UNIQUE PRIMARY KEY,
        name TEXT UNIQUE
    );

    CREATE TABLE usage(
        id INTEGER UNIQUE PRIMARY KEY,
        name TEXT,
        categoryId INTEGER,

        FOREIGN KEY (categoryId) REFERENCES category(id),
                       UNIQUE (name, categoryId)
    );

    CREATE TABLE bills(
        id INTEGER UNIQUE PRIMARY KEY,
        date TEXT,
        price REAL,
        shopId INTEGER,
        usageId INTEGER,
        filename TEXT,

        FOREIGN KEY(shopId) REFERENCES shops(id),
                       FOREIGN KEY(usageId) REFERENCES usage(id)
    );
    )";

    // Check tables already exist
    const auto tables = std::array {"shops", "category", "usage", "bills"};
    if (std::all_of(tables.begin(), tables.end(), [this](const std::string& name){return tableExists(name);})) {
        std::cout << "[DB] All tables exist. Aborting initialization." << std::endl;
        return true;
    }

    // Create tables
    char* messageError;
    if (sqlite3_exec(m_sqlite->m_db, QUERY_CREATE_ALL, nullptr, nullptr, &messageError) != SQLITE_OK) {
        std::cerr << "[DB] Error initializing database: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "[DB] Initialized database.\n";
    return true;
}

bool billDbHandler::addCategory(const std::string& name) {
	static constexpr char QUERY_FORMAT[] = "INSERT INTO category (name) VALUES ('{}');";

    if (name.empty()) {
		return false;
	}

    // Write into db
    const std::string query = std::format(QUERY_FORMAT, sanitize(name));
    char* messageError;
    if (sqlite3_exec(m_sqlite->m_db, query.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK) {
        std::cerr << "[DB] Error Insertion: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "[DB] Inserted new Category\n";
    return true;
}

bool billDbHandler::addUsage(const std::string& name, int categoryId) {
    static constexpr char QUERY_FORMAT[] = "INSERT INTO usage (name, categoryId) VALUES ('{}', {});";
    if (name.empty() || categoryId == 0) {
        std::cout << "[DB] Failed to add usage class. Missing or invalid information.\n";
        return false;
    }

    // Write into db
    const std::string query = std::format(QUERY_FORMAT, sanitize(name), categoryId);
    char* messageError;
    if (sqlite3_exec(m_sqlite->m_db, query.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK) {
        std::cerr << "[DB] Error Insertion: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "[DB] Inserted new usage class.\n";
    return true;
}

bool billDbHandler::addShop(const std::string& name) {
    static constexpr char QUERY_FORMAT[] = "INSERT INTO shops (name) VALUES ('{}');";
    if (name.empty()) {
        std::cout << "[DB] Failed to add shop. Name cannot be empty.\n";
        return false;
    }

    // Write into db
    const std::string query = std::format(QUERY_FORMAT, sanitize(name));
    char* messageError;
    if (sqlite3_exec(m_sqlite->m_db, query.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK) {
        std::cerr << "[DB] Error Insertion: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "[DB] Inserted new shop.\n";
    return true;
}

bool billDbHandler::addBill(const std::string& date, float price, unsigned shopId, unsigned usageId, const std::string& filename) {
    static constexpr char QUERY_FORMAT[] = "INSERT INTO bills (date, price, shopId, usageId, filename) VALUES ('{}', {}, {}, {}, '{}');";
    if (date.empty() || usageId == 0 || shopId == 0 || price == 0.f) {
        std::cout << "[DB] Failed to add bill. Missing or invalid information.\n";
        return false;
    }

    // Write into db
    const std::string query = std::format(QUERY_FORMAT, sanitize(date), price, shopId, usageId, sanitize(filename));
    char* messageError;
    if (sqlite3_exec(m_sqlite->m_db, query.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK) {
        std::cerr << "[DB] Error Insertion: " << messageError << '\n';
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "[DB] Inserted new bill.\n";
    return true;
}

std::vector<usage> billDbHandler::getUsages(unsigned categoryId) {
    static constexpr char QUERY_ALL[] = "SELECT id, categoryId, name FROM usage";
	static constexpr char QUERY_SELECT[] = "SELECT id, categoryId, name FROM usage WHERE categoryId IS {}";

	std::string sql = categoryId == 0 ? std::string(QUERY_ALL) : std::format(QUERY_SELECT, categoryId);
    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(m_sqlite->m_db, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "[DB] Error reading usages.\n";
    }

    std::vector<usage> usages;
    while(sqlite3_step(statement) == SQLITE_ROW) {
        usages.emplace_back(
            static_cast<unsigned>(sqlite3_column_int(statement, 0)),
            static_cast<unsigned>(sqlite3_column_int(statement, 1)),
            std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)))
        );
    }

    sqlite3_finalize(statement);
    return usages;
}

std::vector<shop> billDbHandler::getShops() {
	static constexpr char QUERY[] = "SELECT id, name FROM shops";

	sqlite3_stmt* statement;
	if(sqlite3_prepare_v2(m_sqlite->m_db, QUERY, -1, &statement, nullptr) != SQLITE_OK) {
		std::cerr << "[DB] Error reading shops.\n";
	}

	std::vector<shop> shops;
	while(sqlite3_step(statement) == SQLITE_ROW) {
		shops.emplace_back(
				static_cast<unsigned>(sqlite3_column_int(statement, 0)),
				std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)))
		);
	}

	sqlite3_finalize(statement);
	return shops;
}

std::vector<category> billDbHandler::getCategories() {
	static constexpr char QUERY[] = "SELECT id, name FROM category";

	sqlite3_stmt* statement;
	if(sqlite3_prepare_v2(m_sqlite->m_db, QUERY, -1, &statement, nullptr) != SQLITE_OK) {
		std::cerr << "[DB] Error reading categories.\n";
	}

	std::vector<category> categories;
	while(sqlite3_step(statement) == SQLITE_ROW) {
		categories.emplace_back(
				static_cast<unsigned>(sqlite3_column_int(statement, 0)),
				std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)))
		);
	}

	sqlite3_finalize(statement);
	return categories;
}

std::vector<bill> billDbHandler::getBills(const std::string&, unsigned, unsigned) {
	static constexpr char QUERY_FULL[] = "SELECT id, shopId, usageId, price, date, filename FROM bills";

    /*
	std::string sql = std::string(QUERY_FULL);
	if(!date.empty()) {
		// TODO: Continue this shit
		sql += std::format(" WHERE date IS '{}'", date);
	}
 */

    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(m_sqlite->m_db, QUERY_FULL, -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "[DB] Error reading bills.\n";
    }

    std::vector<bill> bills;
    while(sqlite3_step(statement) == SQLITE_ROW) {
        bills.emplace_back(
        static_cast<unsigned>(sqlite3_column_int(statement, 0)),
        static_cast<unsigned>(sqlite3_column_int(statement, 1)),
        static_cast<unsigned>(sqlite3_column_int(statement, 2)),
        static_cast<float>(sqlite3_column_double(statement, 3)),
        reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)),
        reinterpret_cast<const char*>(sqlite3_column_text(statement, 5))
        );
    }

    sqlite3_finalize(statement);
    return bills;
}

std::string billDbHandler::getUsageName(unsigned id) {
    static constexpr char QUERY[] = "SELECT name FROM usage WHERE id IS {}";

    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(m_sqlite->m_db, std::format(QUERY, id).c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "[DB] Error reading usage name.\n";
    }

    if (sqlite3_step(statement) != SQLITE_ROW) {
        throw std::invalid_argument("Usage id does not exist.");
    }

    const auto usageName = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
    assert(sqlite3_step(statement) == SQLITE_DONE); // Make sure only one result.

    return usageName;
}

std::string billDbHandler::getShopName(unsigned id) {
    static constexpr char QUERY[] = "SELECT name FROM shops WHERE id IS {}";

    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(m_sqlite->m_db, std::format(QUERY, id).c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "[DB] Error reading shop name.\n";
    }

    if (sqlite3_step(statement) != SQLITE_ROW) {
        throw std::invalid_argument("Shop id does not exist.");
    }

    const auto shopName = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
    assert(sqlite3_step(statement) == SQLITE_DONE); // Make sure only one result.

    return shopName;
}

std::string billDbHandler::getCategoryName(unsigned id) {
    static constexpr char QUERY[] = "SELECT name FROM category WHERE id IS {}";

    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(m_sqlite->m_db, std::format(QUERY, id).c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "[DB] Error reading category name.\n";
    }

    if (sqlite3_step(statement) != SQLITE_ROW) {
        throw std::invalid_argument("Category id does not exist.");
    }

    const auto categoryName = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
    assert(sqlite3_step(statement) == SQLITE_DONE); // Make sure only one result.

    return categoryName;
}

std::string billDbHandler::sanitize(const std::string& value) {
	// Don't care for now. TODO: Implement
	return value;
}

void billDbHandler::open() {
    // TODO: Allow user to change db path
    static constexpr char dbPath[] ="/home/oliver/.billtracker/data/expense_planner.db";
    static constexpr char FOREIGN_KEYS_ON[] = "PRAGMA foreign_keys = ON;";
	if (m_sqlite->m_db != nullptr) {
		return;
	}

	if (sqlite3_open(dbPath, &m_sqlite->m_db) != SQLITE_OK) {
		std::cerr << "[DB] Error connecting to Bill Database:  " << sqlite3_errmsg(m_sqlite->m_db) << std::endl;
		throw std::invalid_argument(std::format("Could not open database: '{}'", dbPath));
	} else {
		std::cout << "[DB] Connected to Bill Database." << std::endl;
	}

    // Enable foreign key constraint
    char* errorMsg;
    if (sqlite3_exec(m_sqlite->m_db, FOREIGN_KEYS_ON, 0, 0, &errorMsg) != SQLITE_OK) {
        std::cout << "[DB] Failed to enable foreign key constraint: " << errorMsg << '\n';
        sqlite3_free(errorMsg);
    }
}

}
