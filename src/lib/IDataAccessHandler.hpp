#pragma once

#include "types/file.hpp"
#include "types/bill.hpp"
#include "types/shop.hpp"
#include "types/category.hpp"

#include <vector>
#include <string>

namespace lib {

//! Interface allows usage of database or json file.
class IDataAccessHandler {
protected:
	IDataAccessHandler() = default;
	IDataAccessHandler(IDataAccessHandler&& other) = default;
	IDataAccessHandler(const IDataAccessHandler& other) = default;

	IDataAccessHandler& operator=(IDataAccessHandler&& other) = default;
	IDataAccessHandler& operator=(IDataAccessHandler const& other) = default;

public:
	virtual ~IDataAccessHandler() = default;

	virtual bool createBackup() const = 0;

// Application data
	//! Setup all required infrastructure for the program if necessary.
	virtual void initializeProgram() const = 0;

// File specific functions
	//! Get path where file is stored from the settings.json file (with fileName).
	virtual std::string getFilePath(file fileName) const = 0;

	//! Get path where file is stored from the settings.json file (without fileName).
	virtual std::string getFolderPath(file fileName) const = 0;

	//! Set the path of the specified file to the specified path in the settings.json file.
	virtual bool setFolderPath(file fileName, const std::string& path) const = 0;

	/*!
	* @brief  Move the file to a new location and update the path in the settings.json file.
	* @param fileName The file to update.
	* @param newPath New path where to move to.
	* @return False if an error occurred.
	*/
	virtual bool updateFilePath(file fileName, const std::string& newPath) const = 0;
};

}