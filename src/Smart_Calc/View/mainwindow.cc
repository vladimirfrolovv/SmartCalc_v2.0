#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setStyleSheet("background-color: white;");
  grap = new graph;
  setGeometry(QRect(400, 500, 800, 620));

  connect(this, &MainWindow::signal, grap, &graph::slot);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_equals_clicked() {
  std::string x_str = ui->input_x->text().toUtf8().constData();
  std::string v_str = ui->result->text().toUtf8().constData();
  s21::Controller controller;
  ui->result->setText(
      ui->result->text() + "=" +
      QString::fromStdString(controller.GetResultStr(v_str, x_str)));
}

void MainWindow::on_pushButton_graph_clicked() {
  int xBegin = atoi(ui->domain_min->text().toUtf8().constData());
  int xEnd = atoi(ui->domain_max->text().toUtf8().constData());
  int yBegin = atoi(ui->range_min->text().toUtf8().constData());
  int yEnd = atoi(ui->range_max->text().toUtf8().constData());
  std::string v_str = ui->result->text().toUtf8().constData();
  s21::Controller controller;
  std::string res = controller.GetResultStr(v_str, "0");
  if (res != "ERROR") {
    emit signal(xBegin, xEnd, yBegin, yEnd, v_str);
    grap->show();

  } else {
    ui->result->setText(QString::fromStdString(res));
  }
}

void MainWindow::on_pushButton_clean_clicked() { ui->result->setText(""); }

void MainWindow::on_pushButton_degree_clicked() { ui->result->insert("^"); }

void MainWindow::on_pushButton_mod_clicked() { ui->result->insert("mod"); }

void MainWindow::on_pushButton_div_clicked() { ui->result->insert("/"); }

void MainWindow::on_pushButton_sqrt_clicked() { ui->result->insert("sqrt("); }

void MainWindow::on_pushButton_sin_clicked() { ui->result->insert("sin("); }

void MainWindow::on_pushButton_cos_clicked() { ui->result->insert("cos("); }

void MainWindow::on_pushButton_tan_clicked() { ui->result->insert("tan("); }

void MainWindow::on_pushButton_asin_clicked() { ui->result->insert("asin("); }

void MainWindow::on_pushButton_acos_clicked() { ui->result->insert("acos("); }

void MainWindow::on_pushButton_atan_clicked() { ui->result->insert("atan("); }

void MainWindow::on_pushButton_log_clicked() { ui->result->insert("log("); }

void MainWindow::on_pushButton_ln_clicked() { ui->result->insert("ln("); }

void MainWindow::on_pushButton_plus_clicked() { ui->result->insert("+"); }

void MainWindow::on_pushButton_minus_clicked() { ui->result->insert("-"); }

void MainWindow::on_pushButton_mul_clicked() { ui->result->insert("*"); }

void MainWindow::on_pushButton_zero_clicked() { ui->result->insert("0"); }

void MainWindow::on_pushButton_point_clicked() { ui->result->insert("."); }

void MainWindow::on_pushButton_1_clicked() { ui->result->insert("1"); }

void MainWindow::on_pushButton_2_clicked() { ui->result->insert("2"); }

void MainWindow::on_pushButton_3_clicked() { ui->result->insert("3"); }

void MainWindow::on_pushButton_4_clicked() { ui->result->insert("4"); }

void MainWindow::on_pushButton_5_clicked() { ui->result->insert("5"); }

void MainWindow::on_pushButton_6_clicked() { ui->result->insert("6"); }

void MainWindow::on_pushButton_7_clicked() { ui->result->insert("7"); }

void MainWindow::on_pushButton_8_clicked() { ui->result->insert("8"); }

void MainWindow::on_pushButton_9_clicked() { ui->result->insert("9"); }

void MainWindow::on_pushButton_brack_l_clicked() { ui->result->insert("("); }

void MainWindow::on_pushButton_brack_r_clicked() { ui->result->insert(")"); }

void MainWindow::on_pushButton_x_clicked() { ui->result->insert("x"); }
