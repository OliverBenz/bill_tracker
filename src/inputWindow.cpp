#include "inputWindow.hpp"

#include "lib/bill.hpp"
#include "lib/shop.hpp"
#include "lib/category.hpp"
#include "lib/fileHandling.hpp"

inputWindow::inputWindow(QWidget* parent) : QWidget(parent) {
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

void inputWindow::setupInputMasks() {
	m_leDate->setPlaceholderText("DD.MM.YYYY");
	m_leDate->setInputMask("99.99.9999");

	m_lePrice->setPlaceholderText("00,00€");
	m_lePrice->setInputMask("99,99€");
}

void inputWindow::setupConnections() {
	connect(m_bAdd, SIGNAL(clicked()), this, SLOT(writeBillToFile()));
	connect(m_bClear, SIGNAL(clicked()), this, SLOT(clearInputFields()));
	connect(m_cbCategory, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSubCategories(int)));
}

void inputWindow::fillStandardData() {
	auto shops = lib::getShops();
	for (const auto& shop : shops)
		m_cbShop->insertItem(shop.id, QString(shop.name.c_str()));

	auto categories = lib::getCategories();
	for(const auto& category : categories)
		m_cbCategory->insertItem(category.id, QString(category.name.c_str()));
}

inputWindow::~inputWindow() {
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
void inputWindow::clearInputFields() {
	m_lePrice->clear();
	m_leDate->clear();
	m_cbShop->setCurrentIndex(0);
}

void inputWindow::writeBillToFile() {
	lib::bill b;
	b.date = m_leDate->text().toStdString();
	b.shop = m_cbShop->currentIndex();
	b.price = std::stof(m_lePrice->text().toStdString());

	b.category = m_cbCategory->currentIndex();
	b.subCategory = m_cbCategorySub->currentIndex();

	lib::addBillToFile(b);

	clearInputFields();
}

void inputWindow::updateSubCategories(const int newCategory) {
	const auto subcats = lib::getSubCategories(newCategory);
	m_cbCategorySub->clear();

	for (const auto& cat : subcats)
		m_cbCategorySub->insertItem(cat.id, QString(cat.name.c_str()));
}
