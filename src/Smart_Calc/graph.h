#ifndef GRAPH_H
#define GRAPH_H

#include <math.h>

#include <QDialog>

namespace Ui {
class graph;
}

class graph : public QDialog {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();

 private slots:

 private:
  Ui::graph *ui;
  QVector<double> x, y;

 public slots:
  void slot(int xBegin, int xEnd, int yBegin, int yEnd, char *ex_str);
};

#endif  // GRAPH_H
