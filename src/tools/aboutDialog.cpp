#include "aboutDialog.hpp"

#include "../lib/fileHandling.hpp"

aboutDialog::aboutDialog(QWidget* parent) : QDialog(parent) {
	m_lMain = new QVBoxLayout(this);

	m_laAppName = new QLabel(lib::getAppName().c_str(), this);
	m_laAuthor = new QLabel(("By " + lib::getAppAuthor()).c_str(), this);

	m_lMain->addWidget(m_laAppName);
	m_lMain->addWidget(m_laAuthor);
}

aboutDialog::~aboutDialog() {
	delete m_laAuthor;
	delete m_laAppName;

	delete m_lMain;
}