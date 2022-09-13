#include "overview.hpp"

#include "../lib/dataHandler.hpp"

overview::overview(QWidget* parent) : QWidget(parent) {
	m_catPie = new QPieSeries();
	m_chart = new QChart();
	m_chartView = new QChartView(m_chart, this);
	m_chart->addSeries(m_catPie);

	setupCategoryPieChart();
}

void overview::setupCategoryPieChart() {
	// Get a map of all categories with the sum of their price from all bills.
	std::map<int, float> catPrices;
	for(const auto& bill : lib::getBills("")) {
		if(catPrices.contains(bill.category)) {
			catPrices.at(bill.category) += bill.price;
		} else {
			catPrices.insert({bill.category, bill.price});
		}
	}

	// Setup pie chart
	for(const auto& val: catPrices) {
		m_catSlices.push_back(m_catPie->append(std::to_string(val.first).c_str(), val.second));
	}
}

overview::~overview() {
	for (const auto& slice : m_catSlices) {
		delete slice;
	}

	delete m_catPie;
	delete m_chart;
}