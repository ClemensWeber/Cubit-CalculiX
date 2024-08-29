#include "PlotChart.hpp"

#include "CubitMessage.hpp"

PlotChart::PlotChart(QWidget* parent,QString windowtitle, QString title, QString x_axis, QString y_axis, std::vector<double> x_data,  std::vector<double> y_data):
  QWidget(parent),
  isInitialized(false)
{
  if(isInitialized)
    return;

  this->setWindowTitle(windowtitle);
  this->setGeometry(0,0,700,570);
  gridLayout = new QGridLayout(this);
  boxLayout_window = new QHBoxLayout();
  boxLayout_widget = new QVBoxLayout();
  gridLayout->addLayout(boxLayout_window,1,1, Qt::AlignRight);

  QtCharts::QLineSeries *series = new QtCharts::QLineSeries(this);

  for (size_t i = 0; i < x_data.size(); i++)
  {
    series->append(x_data[i], y_data[i]);
  }

  QtCharts::QChart *chart = new QtCharts::QChart();
  chart->legend()->hide();
  chart->addSeries(series);
  chart->createDefaultAxes();
  chart->setTitle(title);

  QtCharts::QChartView *chartView = new QtCharts::QChartView(chart,this);
  chartView->setRenderHint(QPainter::Antialiasing);
  
  this->setAttribute(Qt::WA_DeleteOnClose);
  boxLayout_window->addWidget(chartView);

  std::string log;
  log = "plotting \n";
  PRINT_INFO("%s", log.c_str());

  isInitialized = true;
}

PlotChart::~PlotChart()
{
  std::string log;
  log = "closing plot for job \n";
  PRINT_INFO("%s", log.c_str());
}