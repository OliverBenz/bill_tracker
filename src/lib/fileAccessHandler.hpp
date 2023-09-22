#pragma once

#include "IDataAccessHandler.hpp"

namespace lib {

class fileAccessHandler : public IDataAccessHandler {
public:
	fileAccessHandler() = default;
	~fileAccessHandler() = default;

// Bill data
	bool addBill(const bill& newBill) const override;

	std::vector<bill> getBills(const std::string& date) const override;
	std::vector<shop> getShops() const override;

	std::vector<category> getCategories() const override;
	std::vector<subcategory> getSubCategories(int categoryId) const override;

	bool createBackup() const override;

// Application data
	//! Setup all required infrastructure for the program if necessary.
	void initializeProgram() const override;

	//! Get the application author name from the config file.
	std::string getAppAuthor() const override;

	//! Ge the application name from the config file.
	std::string getAppName() const override;

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

#ifndef NDEBUG
	void writeDebugData() const override;
#endif

private:
	static std::string getFileName(const file fileName);

	static constexpr char m_projectPath[] = "/home/oliver/.billtracker";
	static constexpr char m_filenameConfig[] = "/home/oliver/.billtracker/data/settings.json";
};

}
