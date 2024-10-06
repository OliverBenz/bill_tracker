#include "appConfig.hpp"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <cassert>
#include <iostream>

namespace lib {

static const auto CONFIG_PATH = std::filesystem::path(getenv("HOME")) / ".config/billtracker";
static const auto CONFIG_FILE = CONFIG_PATH / "config.json";

static constexpr char KEY_PATH_DB[]     = "pathDatabase";
static constexpr char KEY_PATH_BACKUP[] = "pathBackup";

static bool getSimpleKeyFromConfig(const char* keyName, std::filesystem::path& result) {
	std::ifstream jsonFile(CONFIG_FILE);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find(keyName) == json.end()) {
		return false;
    }

    result = std::string(json.at(keyName));
    return true;
}

static bool setSimpleKeyInConfig(const char* keyName, const std::string& newValue) {

    // Read json 
    nlohmann::json configJson;
    {
        std::ifstream configFile(CONFIG_FILE);
        if(!configFile.is_open()) {
            std::cerr << "[CONFIG] Could not open config file for reading." << std::endl;
            return false;
        }
        configFile >> configJson;
        configFile.close();
    }

    // Update information
    if(configJson.find(keyName) == configJson.end()) {
        assert(false);
        return false;
    }
    configJson[keyName] = newValue;

    // Write json
    {
        std::ofstream configFile(CONFIG_FILE);
        if(!configFile.is_open()) {
            std::cerr << "[CONFIG] Could not open config file for writing." << std::endl;
            return false;
        }
        configFile << configJson.dump(4) << "\n";
        configFile.close();
    }

    return true;
}

bool initializeConfig() {
    static const auto DEFAULT_DB_PATH = std::filesystem::path(getenv("HOME")) / ".billtracker";
    static const auto DEFAULT_BACKUP_PATH = std::filesystem::path(getenv("HOME")) / ".billtracker/backup";

    if (std::filesystem::exists(CONFIG_FILE))
        return false;

    // Create default config.json file
	std::filesystem::create_directories(CONFIG_PATH);
    nlohmann::json configBase;
    configBase[KEY_PATH_DB] = DEFAULT_DB_PATH;
    configBase[KEY_PATH_BACKUP]   = DEFAULT_BACKUP_PATH;

    std::ofstream configFile(CONFIG_FILE);
    configFile << configBase.dump(4) << "\n";
    configFile.close();

    // Create default file locations
    std::filesystem::create_directories(DEFAULT_DB_PATH);
    std::filesystem::create_directories(DEFAULT_BACKUP_PATH);

    return true;
}

std::filesystem::path getDatabasePath() {
    std::filesystem::path path;
    if (!getSimpleKeyFromConfig(KEY_PATH_DB, path)) {
        std::cerr << "[CONFIG] Could not find database location in config." << std::endl;
        assert(false);
    }
    if (path.empty()) {
        std::cerr << "[CONFIG] Database path is empty." << std::endl;
        assert(false);
    }

    return path;
}

std::filesystem::path getBackupPath() {
    std::filesystem::path path;
    if (!getSimpleKeyFromConfig(KEY_PATH_BACKUP, path)) {
        std::cerr << "[CONFIG] Could not find backup location in config." << std::endl;
        assert(false);
    }
    if (path.empty()) {
        // Not an error but better to be set.
        std::cout << "[CONFIG] Backup path is empty." << std::endl;
    }

    return path;
}

bool setDatabasePath(const std::filesystem::path& path) {
    if(setSimpleKeyInConfig(KEY_PATH_DB, path)) {
        std::filesystem::create_directories(path);
        return true;
    }
    return false;
}

bool setBackupPath(const std::filesystem::path& path ) {
    if(setSimpleKeyInConfig(KEY_PATH_BACKUP, path)) {
        std::filesystem::create_directories(path);
        return true;
    }
    return false;
}

}