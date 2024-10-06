#include "appConfig.hpp"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <cassert>
#include <iostream>

namespace lib {

static const auto CONFIG_PATH = std::filesystem::path(getenv("HOME")) / ".config/billtracker";
static const auto CONFIG_FILE = CONFIG_PATH / "config.json";

static bool getSimpleKeyFromConfig(const char* name, std::filesystem::path& result) {
	std::ifstream jsonFile(CONFIG_FILE);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find(name) == json.end()) {
		return false;
    }

    result = std::string(json.at(name));
    return true;
}

bool initializeConfig() {
    static const auto DEFAULT_DB_PATH = std::filesystem::path(getenv("HOME")) / ".billtracker";
    static const auto DEFAULT_BACKUP_PATH = std::filesystem::path(getenv("HOME")) / ".billtracker/backup";

    if (std::filesystem::exists(CONFIG_FILE))
        return false;

    // Create default config.json file
    if (!std::filesystem::exists(CONFIG_PATH))
	    std::filesystem::create_directories(CONFIG_PATH);
    nlohmann::json configBase;
    configBase["pathDatabase"] = DEFAULT_DB_PATH;
    configBase["pathBackup"]   = DEFAULT_BACKUP_PATH;

    std::ofstream configFile(CONFIG_FILE);
    configFile << configBase.dump(4);
    configFile.close();

    // Create default file locations
    if (!std::filesystem::exists(DEFAULT_DB_PATH))
        std::filesystem::create_directories(DEFAULT_DB_PATH);
    if (!std::filesystem::exists(DEFAULT_BACKUP_PATH))
        std::filesystem::create_directories(DEFAULT_BACKUP_PATH);

    return true;
}

std::filesystem::path getDatabasePath() {
    static constexpr char KEY_NAME[] = "pathDatabase";

    std::filesystem::path path;
    if (!getSimpleKeyFromConfig(KEY_NAME, path)) {
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
    static constexpr char KEY_NAME[] = "pathBackup";

    std::filesystem::path path;
    if (!getSimpleKeyFromConfig(KEY_NAME, path)) {
        std::cerr << "[CONFIG] Could not find backup location in config." << std::endl;
        assert(false);
    }
    if (path.empty()) {
        // Not an error but better to be set.
        std::cout << "[CONFIG] Backup path is empty." << std::endl;
    }

    return path;
}


}