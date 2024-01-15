#pragma once

#include <string>

class SettingsModel {
public:
    std::string getBillsPath();
    std::string getDataPath();

    void updateBillPath(std::string pathBill);
    void updateDataPath(std::string pathData);
};
