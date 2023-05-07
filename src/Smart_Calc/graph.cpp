#include "graph.h"

#include "ui_graph.h"
extern "C" {

#include "s21_smart_calc.h"
}
graph::graph(QWidget* parent) : QDialog(parent), ui(new Ui::graph) {
  ui->setupUi(this);
  setGeometry(QRect(1200, 500, 800, 620));
}

graph::~graph() { delete ui; }

void graph::slot(int xBegin, int xEnd, int yBegin, int yEnd, char* ex_str) {
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);

  ui->widget->replot();
  double x_point = 0;
  double result = 0;
  double h = 0.1;
  int status = 0;
  x.clear();
  y.clear();
  ui->widget->clearGraphs();
  ui->widget->addGraph(0);
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);

  for (x_point = xBegin; x_point < xEnd && status != 1; x_point += h) {
    result = s21_callculation(ex_str, &status, x_point);
    x.push_back(x_point);
    y.push_back(result);
  }

  ui->widget->graph(0)->setPen(QPen(Qt::blue));

  ui->widget->graph(0)->addData(x, y);

  ui->widget->replot();
}
