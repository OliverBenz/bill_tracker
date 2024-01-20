#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

#include "ui/models/addBillModel.hpp"
#include "lib/types/bill.hpp"

class AddBillView : public QWidget {
    Q_OBJECT

public:
    AddBillView(QWidget* parent = nullptr);
    ~AddBillView();

signals:
    void onNewBill(const lib::bill&);

private slots:
    void clearInputFields();
    void writeBillToFile();
    void updateUsages(int newCategory);

private:
    void setupInputMasks();
    void setupConnections();

    //! Retrieve and display data from global json file
    void fillStandardData();

    AddBillModel m_logic;  //!< Handles data and all non-UI related tasks.

    // UI Elements
    QVBoxLayout* m_lMain;
    QHBoxLayout* m_lInputs;
    QHBoxLayout* m_lButtons;

    QLineEdit* m_leDate;  // NOTE: Could be updated to a calendar widget.
    QComboBox* m_cbShop;
    QComboBox* m_cbCategory;
    QComboBox* m_cbCategorySub;
    QLineEdit* m_lePrice;

    QPushButton* m_bAdd;
    QPushButton* m_bClear;  // TODO: Remove this button?
};
