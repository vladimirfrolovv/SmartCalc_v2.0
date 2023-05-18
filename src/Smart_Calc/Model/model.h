#ifndef SRC_S21_SMART_CALCULATOR_
#define SRC_S21_SMART_CALCULATOR_

#include <ctype.h>

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>

#define MAX_NUM 30
#define MAX_STR 604

namespace s21 {

class Model {
 public:
  typedef struct stack_elem {
    char elem = ' ';
    int priority = 0;
  } stack_elem;
  Model() = default;

  ~Model() = default;

  /// @brief Function for parsing input expression polish notation
  /// @param str input expresion(str) in polish notation
  /// @param ex_str exit expression in polish notation
  /// @param status error if status ==0 it's ok if status == 1 it's error
  /// @return char *exit str in polish notation
  char *Parse(char *str, char *ex_str, int *status);

  /// @brief Function for checks current symbol is number in input str
  /// @param ex_str exit str
  /// @param str current symbol
  /// @param status error
  /// @param double_op flag for double operation
  /// @param flag_point flag for "."
  void ParseNumber(char **ex_str, char **str, int *status, int *double_op,
                   int *flag_point);

  /// @brief Function for checks current symbol is operator and push in stack or
  /// in exit str depending priority
  /// @param stack_op stack
  /// @param ex_str exit str
  /// @param str current symbol
  /// @param status error
  /// @param flag_op flag for checks if 1 pop out of stack ( else 0 pop out of
  /// stack ( and function
  /// @param double_op flag for cheks double operator
  /// @param number_of_brack counter for bracked
  void ParseOperators(std::stack<stack_elem> &stack_op, char **ex_str,
                      char **str, int *status, int *flag_op, int *double_op,
                      int *number_of_brack);

  /// @brief Function for checks current symbol is function and push in stack
  //  /// and depending priority
  /// @param stack_op stack
  /// @param str current symbol
  /// @param flag_op flag for checks if 1 pop out of stack ( else 0 pop out of
  //  /// stack ( and function
  /// @param flag_func flag for checks current symbol if flag_func 1 && current
  //  /// symb != '(' it's error
  /// @param status error
  /// @param double_op flag for cheks double operator
  void ParseFunction(std::stack<stack_elem> &stack_op, char **str, int *flag_op,
                     int *flag_func, int *status, int *double_op);

  /// @brief Function for check current symbol is operator
  /// @param str current symbol
  /// @return int error
  int IsOperator(char str);

  /// @brief Function for check priority operator
  /// @param str current sybol
  /// @return int priority
  int Priority(char str);

  /// @brief Function for check current expresion is element array with function
  /// @param str pointer str element array with functoin
  /// @param prior priority function
  /// @return  char token(abbreviated function to 1 symbol
  char TokOfFunction(const char *str, int *prior);

  /// @brief Calculation unar operators and function
  /// @param stack_value stack with values
  /// @param status error
  /// @param curr_op current symb of operator
  /// @return status
  int UnarOperAndFunc(std::stack<double> &stack_value, int status,
                      char curr_op);

  /// @brief Function CalcOpAndFunc elections how func calculation need
  /// @param stack_value stack with values
  /// @param symb current sym
  /// @param status error
  void CalcOpAndFunc(std::stack<double> &stack_value, char symb, int *status);

  /// @brief Function Calculation polish notation
  /// @param ex_str expression in polish notation
  /// @param status error
  /// @param x
  /// @return result calculation
  long double Calculation(char *ex_str, int *status, long double x);

  /// @brief Function for Calculate binar oper and function(with two parametrs)
  /// @param stack_value stack
  /// @param status error
  /// @param curr_op current symb
  /// @return status
  int BinarOper(std::stack<double> &stack_value, int status, char curr_op);

  /// @brief Func Menu Calculate polish notation
  /// @param str_ input str infix notation
  /// @param x_ paramert x
  /// @return expresion
  std::string Result(std::string str_, std::string x_);
};
}  // namespace s21
#endif  // SRC_SMART_CALCULATOR_
