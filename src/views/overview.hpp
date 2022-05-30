#pragma once

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>

class overview : public QWidget {
	Q_OBJECT

public:
	overview(QWidget* parent = nullptr);
	~overview();

private:
	void setupCategoryPieChart();

private:
	QPieSeries* m_catPie;
	QChartView* m_chartView;
	QChart* m_chart;
	std::vector<QPieSlice*> m_catSlices;
};
