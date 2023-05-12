#include "../Model/model.h"

namespace s21 {
class Controller {
 public:
  Controller();
  ~Controller();
  std::string GetResultStr(std::string str, std::string x);
  double GetResultDouble(std::string str, long double x);

 private:
  Model *model;
};
}  // namespace s21