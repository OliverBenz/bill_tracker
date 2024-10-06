#pragma once

#include <filesystem>

namespace lib {

inline static constexpr char APP_NAME[] = "Bill Tracker";
inline static constexpr char APP_AUTHOR[] = "Oliver Benz";

//! Creates the config file if not yet exists.
//! @returns True if the config was newly created.
bool initializeConfig();

//! Get the path to the database file.
std::filesystem::path getDatabasePath();

//! Get the path to the backup folder.
std::filesystem::path getBackupPath();

//! Set the path to the database file.
//! @note Does not move the data to the new location but creates the directory.
bool setDatabasePath(const std::filesystem::path& path);

//! Set the path to the backup folder.
//! @note Does not move the data to the new location but creates the directory.
bool setBackupPath(const std::filesystem::path& path );

}