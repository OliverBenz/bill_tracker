#pragma once

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>

//! Display statistics made from available data.
class statisticsView : public QWidget {
	Q_OBJECT

public:
	statisticsView(QWidget* parent = nullptr);
	~statisticsView();

private:
	void setupCategoryPieChart();

private:
	QPieSeries* m_catPie;
	QChartView* m_chartView;
	QChart* m_chart;
	std::vector<QPieSlice*> m_catSlices;
};
