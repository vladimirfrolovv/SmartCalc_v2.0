#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <graph.h>
#include <qcustomplot.h>

#include <QMainWindow>
#include <QTextEdit>
#include <QVector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_pushButton_equals_clicked();

  // void on_result_textChanged();

  void on_pushButton_clean_clicked();

  void on_pushButton_degree_clicked();

  void on_pushButton_mod_clicked();

  void on_pushButton_div_clicked();

  void on_pushButton_sqrt_clicked();

  void on_pushButton_sin_clicked();

  void on_pushButton_cos_clicked();

  void on_pushButton_tan_clicked();

  void on_pushButton_asin_clicked();

  void on_pushButton_acos_clicked();

  void on_pushButton_atan_clicked();

  void on_pushButton_log_clicked();

  void on_pushButton_ln_clicked();

  void on_pushButton_plus_clicked();

  void on_pushButton_minus_clicked();

  void on_pushButton_mul_clicked();

  void on_pushButton_zero_clicked();

  void on_pushButton_point_clicked();

  void on_pushButton_1_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_brack_l_clicked();

  void on_pushButton_brack_r_clicked();

  void on_pushButton_x_clicked();

  void on_pushButton_graph_clicked();

  //    void on_result_textChanged(const QString &arg1);

 private:
  Ui::MainWindow *ui;
  graph *grap;

 signals:
  void signal(int xBegin, int xEnd, int yBegin, int yEnd, char *ex_str);
};
#endif  // MAINWINDOW_H
