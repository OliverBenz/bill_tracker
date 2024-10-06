#pragma once

#include "IDataAccessHandler.hpp"

#include <string>

namespace lib {

// TODO: Deprecated. Delete this. 
class fileAccessHandler : public IDataAccessHandler {
public:
	fileAccessHandler() = default;
	~fileAccessHandler() = default;

	bool createBackup() const override;

// Application data
	//! Setup all required infrastructure for the program if necessary.
	void initializeProgram() const override;

// File specific functions
	//! Get path where file is stored from the settings.json file (with fileName).
	std::string getFilePath(file fileName) const override;

	//! Get path where file is stored from the settings.json file (without fileName).
	std::string getFolderPath(file fileName) const override;

	//! Set the path of the specified file to the specified path in the settings.json file.
	bool setFolderPath(file fileName, const std::string& path) const override;

	/*!
	* @brief  Move the file to a new location and update the path in the settings.json file.
	* @param fileName The file to update.
	* @param newPath New path where to move to.
	* @return False if an error occurred.
	*/
	bool updateFilePath(file fileName, const std::string& newPath) const override;

private:
	static std::string getFileName(file fileName);

	static constexpr char m_projectPath[] = "/home/oliver/.billtracker";
	static constexpr char m_filenameConfig[] = "/home/oliver/.billtracker/data/settings.json";
};

}
