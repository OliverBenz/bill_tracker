#include "settingsModel.hpp"

#include "lib/dataHandler.hpp"

std::string SettingsModel::getBillsPath() {
    return lib::getFolderPath(lib::file::bills);
}
std::string SettingsModel::getDataPath() {
    return lib::getFolderPath(lib::file::data);
}

void SettingsModel::updateBillPath(std::string pathBill) {
    if(pathBill.back() == '/') {
        pathBill.pop_back();
    }

    if(pathBill != lib::getFolderPath(lib::file::bills)) {
        lib::updateFilePath(lib::file::bills, pathBill);
    }
}

void SettingsModel::updateDataPath(std::string pathData) {
    if(pathData.back() == '/') {
        pathData.pop_back();
    }

    if(pathData != lib::getFolderPath(lib::file::data)) {
        lib::updateFilePath(lib::file::data, pathData);
    }
}