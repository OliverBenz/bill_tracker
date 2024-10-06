#include "appConfig.hpp"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <cassert>
#include <iostream>

namespace lib {

static const auto CONFIG_PATH = std::filesystem::path(getenv("HOME")) / ".config/billtracker";
static const auto CONFIG_FILE = CONFIG_PATH / "config.json";

static bool getSimpleKeyFromConfig(const char* name, std::string& result) {
	std::ifstream jsonFile(CONFIG_FILE);
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find(name) == json.end()) {
		return false;
    }

    result = json.at(name);
    return true;
}

bool initializeConfig() {
    static const auto DEFAULT_DB_PATH = std::filesystem::path(getenv("HOME")) / ".billtracker";
    static const auto DEFAULT_BACKUP_PATH = std::filesystem::path(getenv("HOME")) / ".billtracker/backup";

    if (std::filesystem::exists(CONFIG_FILE)) {
        return false;
    }

	std::filesystem::create_directories(CONFIG_PATH);
    nlohmann::json configBase;
    configBase["pathDatabase"] = DEFAULT_DB_PATH;
    configBase["pathBackup"]   = DEFAULT_BACKUP_PATH;

    std::ofstream configFile(CONFIG_FILE);
    configFile << configBase.dump(4);
    configFile.close();

    return true;
}

std::string getDatabasePath() {
    static constexpr char KEY_NAME[] = "pathDatabase";

    std::string path;
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

std::string getBackupPath() {
    static constexpr char KEY_NAME[] = "pathBackup";

    std::string path;
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