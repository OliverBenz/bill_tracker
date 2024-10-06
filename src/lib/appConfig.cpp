#include "appConfig.hpp"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <cassert>
#include <iostream>

namespace lib {

static const auto CONFIG_PATH = std::filesystem::path(getenv("HOME")) / "billtracker";

bool getSimpleKeyFromConfig(const char* name, std::string& result) {
	std::ifstream jsonFile(CONFIG_PATH / "config.json");
	nlohmann::json json = nlohmann::json::parse(jsonFile);

	if(json.find(name) == json.end()) {
		return false;
    }

    result = json.at(name);
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