#include "databaseAccessHandler.hpp"

#include <fmt/format.h>
#include <iostream>
#include <sqlite3.h>

namespace lib {

class billDbHandler::SqlitePimpl {
public:
    sqlite3* m_db{nullptr};
};

billDbHandler::billDbHandler()
    : m_sqlite(std::make_unique<billDbHandler::SqlitePimpl>()) {
	open();
}

billDbHandler::~billDbHandler() {
	sqlite3_close(m_sqlite->m_db);
}

bool billDbHandler::addCategory(const std::string& name) {
	static constexpr char QUERY_FORMAT[] = "INSERT INTO category (name) VALUES ('{}');";

    if (name.empty()) {
		return false;
	}

    // Write into db
    const std::string query = fmt::format(QUERY_FORMAT, sanitize(name));
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
    const std::string query = fmt::format(QUERY_FORMAT, sanitize(name), categoryId);
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
    const std::string query = fmt::format(QUERY_FORMAT, sanitize(name));
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
    const std::string query = fmt::format(QUERY_FORMAT, sanitize(date), price, shopId, usageId, sanitize(filename));
    char* messageError;
    if (sqlite3_exec(m_sqlite->m_db, query.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK) {
        std::cerr << "[DB] Error Insertion: " << messageError << '\n';
        sqlite3_free(messageError);
        return false;
    }

    std::cout << "[DB] Inserted new bill.\n";
    return true;
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
		throw std::invalid_argument(fmt::format("Could not open database: '{}'", dbPath));
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



void readDataTest() {
    // TODO: Package this in proper classes
    sqlite3* DB;
//    char* messageError;
    int exit = sqlite3_open("/home/oliver/.billtracker/data/expense_planner.db", &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return;
    }
    else {
        std::cout << "Opened Database Successfully!" << std::endl;
    }


    // TODO: Read from db. Using a callback function

    sqlite3_close(DB);
}

}
