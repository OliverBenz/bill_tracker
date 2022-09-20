#include "addBillWidget.hpp"

#include "../lib/bill.hpp"
#include "../lib/shop.hpp"
#include "../lib/category.hpp"
#include "../lib/dataHandler.hpp"
#include "../lib/dateHandler.hpp"

#include <sstream>
#include <locale>

addBillWidget::addBillWidget(QWidget* parent) : QWidget(parent) {
	// Create widgets
	m_lMain = new QVBoxLayout(this);
	m_lInputs = new QHBoxLayout();
	m_lButtons = new QHBoxLayout();

	m_leDate = new QLineEdit(this);
	m_cbShop = new QComboBox(this);
	m_cbCategory = new QComboBox(this);
	m_cbCategorySub = new QComboBox(this);
	m_lePrice = new QLineEdit(this);

	m_bAdd = new QPushButton("Add", this);
	m_bClear = new QPushButton("Clear", this);

	// Add to layouts
	m_lButtons->addWidget(m_bAdd);
	m_lButtons->addWidget(m_bClear);

	m_lInputs->addWidget(m_leDate);
	m_lInputs->addWidget(m_cbShop);
	m_lInputs->addWidget(m_lePrice);
	m_lInputs->addWidget(m_cbCategory);
	m_lInputs->addWidget(m_cbCategorySub);

	m_lMain->addLayout(m_lInputs);
	m_lMain->addLayout(m_lButtons);

	// Setup fields
	setupInputMasks();
	setupConnections();
	fillStandardData();
}

void addBillWidget::setupInputMasks() {
	m_leDate->setPlaceholderText("DD.MM.YYYY");
	m_leDate->setInputMask("99.99.9999");

	m_lePrice->setPlaceholderText("00,00€");
	m_lePrice->setInputMask("99,99€");
}

void addBillWidget::setupConnections() {
	connect(m_bAdd, SIGNAL(clicked()), this, SLOT(writeBillToFile()));
	connect(m_bClear, SIGNAL(clicked()), this, SLOT(clearInputFields()));
	connect(m_cbCategory, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSubCategories(int)));
}

void addBillWidget::fillStandardData() {
	auto shops = lib::getShops();
	for (const auto& shop : shops)
		m_cbShop->insertItem(shop.id, QString(shop.name.c_str()));

	auto categories = lib::getCategories();
	for(const auto& category : categories)
		m_cbCategory->insertItem(category.id, QString(category.name.c_str()));
}

addBillWidget::~addBillWidget() {
	delete m_bClear;
	delete m_bAdd;

	delete m_lePrice;
	delete m_cbCategorySub;
	delete m_cbCategory;
	delete m_cbShop;
	delete m_leDate;

	delete m_lButtons;
	delete m_lInputs;
	delete m_lMain;
}

// Slots
// -----
void addBillWidget::clearInputFields() {
	m_lePrice->clear();
	m_leDate->clear();
	m_cbShop->setCurrentIndex(0);
}

void addBillWidget::writeBillToFile() {
	if(!lib::dateIsValid(m_leDate->text().toStdString())) {
		return; // TODO: With a message maybe.
	}

	lib::bill b;
	b.date = m_leDate->text().toStdString();
	b.shop = m_cbShop->currentIndex();
	b.category = m_cbCategory->currentIndex();
	b.subCategory = m_cbCategorySub->currentIndex();

	// Convert price to float
	b.price = 0.0f;
	std::string price = m_lePrice->text().toStdString();
	for(auto& c :price) {
		if(c == ',')
			c = '.';
	}
	// Input mask always used ',', we want a conversion using a fixed locale.
	std::stringstream stream(price);
	stream.imbue(std::locale::classic());
	stream >> b.price;

	lib::addBill(b);

	clearInputFields();
}

void addBillWidget::updateSubCategories(const int newCategory) {
	const auto subcats = lib::getSubCategories(newCategory);
	m_cbCategorySub->clear();

	for (const auto& cat : subcats)
		m_cbCategorySub->insertItem(cat.id, QString(cat.name.c_str()));
}
