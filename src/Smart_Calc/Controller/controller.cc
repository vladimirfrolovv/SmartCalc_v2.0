#include "controller.h"

namespace s21 {
Controller::Controller() { model = new Model; }
Controller::~Controller() { delete model; }
std::string Controller::GetResultStr(std::string str, std::string x) {
  std::string res = model->Result(str, x);
  return res;
}
double Controller::GetResultDouble(std::string str, long double x) {
  std::string x_ = std::to_string(x);
  std::string res = model->Result(str, x_);
  auto result = std::stold(res);
  return result;
}
}  // namespace s21
