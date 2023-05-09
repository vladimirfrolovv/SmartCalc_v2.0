#ifndef SRC_S21_SMART_CALCULATOR_
#define SRC_S21_SMART_CALCULATOR_

#include <ctype.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>


#define MAX_NUM 30
#define MAX_STR 604

namespace s21 {

    class Model {
    public:
        typedef struct stack_elem {
            char elem = ' ';
            int priority =0;
        } stack_elem;

        Model() = default;

        ~Model() = default;

// s21_polish.c
/// @brief Function for parsing input expression polish notation
/// @param str input expresion(str) in polish notation
/// @param ex_str exit expression in polish notation
/// @param status error if status ==0 it's ok if status == 1 it's error
/// @return char *exit str in polish notation
        char *parse( char *str, char *ex_str, int *status);

/// @brief Function for checks current symbol is number in input str
/// @param ex_str exit str
/// @param str current symbol
/// @param status error
/// @param i counter
/// @param double_op flag for double operation
/// @param flag_point flag for "."
/// @return int i counter
    void parse_number(char **ex_str, char **str, int *status,
                         int *double_op, int *flag_point);

/// @brief Function for checks current symbol is operator and push in stack or
/// in exit str depending priority
/// @param list_op stack
/// @param ex_str exit str
/// @param str current symbol
/// @param status error
/// @param i counter
/// @param flag_op flag for checks if 1 pop out of stack ( else 0 pop out of
/// stack ( and function
/// @param double_op flag for cheks double operator
/// @param number_of_brack counter for bracked
/// @return stack

    void parse_op(std::stack<stack_elem> &stack_op, char **ex_str, char **str, int *status,
                       int *flag_op, int *double_op, int *number_of_brack);

/// @brief Function for checks current symbol is function and push in stack and
/// depending priority
/// @param list_opstack stack
/// @param str current symbol
/// @param flag_op flag for checks if 1 pop out of stack ( else 0 pop out of
/// stack ( and function
/// @param flag_func flag for checks current symbol if flag_func 1 && current
/// symb != '(' it's error
/// @param status error
/// @param double_op flag for cheks double operator
/// @return stack

    void parse_func(std::stack<stack_elem> &stack_op, char **str, int *flag_op, int *flag_func,
                     int *status, int *double_op);

/// @brief Function for check current symbol is operator
/// @param str current symbol
/// @return int error
    int is_operator(char str);

/// @brief Function for check priority operator
/// @param str current sybol
/// @return int priority
    int priority(char str);

/// @brief Function for check current expresion is element array with function
/// @param str pointer str element array with functoin
/// @param prior priority function
/// @return  char token(abbreviated function to 1 symbol
    char tok_func(char *str, int *prior);

// s21_calculation.c
/// @brief Function clalculation polish natation
/// @param ex_str expression in polish notation
/// @param status error
/// @param x
/// @return result calculation
//    double s21_callculation(char *ex_str, int *status, double x);
//
//    list_value *s21_func(list_value *list_val, char symb, int *status);
//
//    list_value *s21_add(list_value *list_val, int *status);
//
//    list_value *s21_sub(list_value *list_val, int *status);
//
//    list_value *s21_mul(list_value *list_val, int *status);
//
//    list_value *s21_div(list_value *list_val, int *status);
//
//    list_value *s21_unar_min(list_value *list_val, int *status);
//
//    list_value *s21_unar_plus(list_value *list_val, int *status);
//
//    list_value *s21_mod(list_value *list_val, int *status);
//
//    list_value *s21_sqrt(list_value *list_val, int *status);
//
//    list_value *s21_sin(list_value *list_val, int *status);
//
//    list_value *s21_cos(list_value *list_val, int *status);
//
//    list_value *s21_tan(list_value *list_val, int *status);
//
//    list_value *s21_asin(list_value *list_val, int *status);
//
//    list_value *s21_acos(list_value *list_val, int *status);
//
//    list_value *s21_atan(list_value *list_val, int *status);
//
//    list_value *s21_ln(list_value *list_val, int *status);
//
//    list_value *s21_log(list_value *list_val, int *status);
//
//    list_value *s21_degree(list_value *list_val, int *status);
        //
//
//// s21_stack.c
//
///// @brief Function for push in lincked list new elem
///// @param head poiner on elem stack
///// @param elem field struct for symbol
///// @param priority feild struct priority operations
///// @return stack
//    list *s21_push(list *head, char elem, int priority);
//
///// @brief Function for delete elem out of lincked list
///// @param head pointer current elem
///// @return stack
//    list *s21_pop(list *head);
//
//// /// @brief Function for free all stack
//// /// @param head poiner on current elem
//// void s21_remove(list *head);
//
///// @brief Function for free all stack with value
///// @param head poiner on elem stack
//    void s21_remove_val(list_value *head);
//
///// @brief Function for push in lincked with numbers(need in calculation) list
///// new elem
///// @param head poiner on elem stack
///// @param value meaning number
///// @return stack
//    list_value *s21_push_value(list_value *head, double value);
//
///// @brief Function for delete in lincked with numbers(need in calculation) list
///// new elem
///// @param head poiner on elem stack
///// @return stack
//    list_value *s21_pop_value(list_value *head);

    };
}
#endif  // SRC_SMART_CALCULATOR_
