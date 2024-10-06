#include "aboutDialog.hpp"

#include "lib/appConfig.hpp"

#include <format>

aboutDialog::aboutDialog(QWidget* parent) : QDialog(parent) {
	m_lMain = new QVBoxLayout(this);

	m_laAppName = new QLabel(lib::APP_NAME, this);
	m_laAuthor = new QLabel(std::format("By {}", lib::APP_AUTHOR).c_str(), this);

	m_lMain->addWidget(m_laAppName);
	m_lMain->addWidget(m_laAuthor);
}

aboutDialog::~aboutDialog() {
	delete m_laAuthor;
	delete m_laAppName;

	delete m_lMain;
}
