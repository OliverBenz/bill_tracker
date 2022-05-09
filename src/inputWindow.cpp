#include "inputWindow.hpp"

#include "lib/bill.hpp"
#include "lib/fileHandling.hpp"

inputWindow::inputWindow(QWidget* parent) : QWidget(parent) {
	// Create widgets
	m_lMain = new QVBoxLayout(this);
	m_lInputs = new QHBoxLayout(this);
	m_lButtons = new QHBoxLayout(this);

	m_leDate = new QLineEdit(this);
	m_cbShop = new QComboBox(this);
	m_lePrice = new QLineEdit(this);

	m_bAdd = new QPushButton("Add", this);
	m_bClear = new QPushButton("Clear", this);

	// Add to layouts
	m_lButtons->addWidget(m_bAdd);
	m_lButtons->addWidget(m_bClear);

	m_lInputs->addWidget(m_leDate);
	m_lInputs->addWidget(m_cbShop);
	m_lInputs->addWidget(m_lePrice);

	m_lMain->addLayout(m_lInputs);
	m_lMain->addLayout(m_lButtons);

	// Setup fields
	m_leDate->setPlaceholderText("DD.MM.YYYY");
	m_leDate->setInputMask("99.99.9999");

	m_lePrice->setPlaceholderText("00,00€");
	m_lePrice->setInputMask("99,99€");

	m_cbShop->insertItem(0, "Merkur");
	m_cbShop->insertItem(1, "Spar");

	// Setup connections
	connect(m_bAdd, SIGNAL(clicked()), this, SLOT(add()));
	connect(m_bClear, SIGNAL(clicked()), this, SLOT(clear()));
}

void inputWindow::clear() {
	m_lePrice->clear();
	m_leDate->clear();
	m_cbShop->setCurrentIndex(0);
}

void inputWindow::add() {
	bill b;
	b.date = m_leDate->text().toStdString();
	b.shop = m_cbShop->currentText().toStdString();
	b.price = std::stof(m_lePrice->text().toStdString());

	addBillToFile(b);
}

inputWindow::~inputWindow() {
	delete m_lMain;
	delete m_lInputs;
	delete m_lButtons;

	delete m_leDate;
	delete m_cbShop;
	delete m_lePrice;

	delete m_bAdd;
	delete m_bClear;
}