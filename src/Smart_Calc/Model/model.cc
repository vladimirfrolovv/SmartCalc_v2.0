#include "model.h"

namespace s21 {
char *Model::parse(char *str, char *ex_str, int *status) {
  int flag_op = 0, double_op = 1, flag_point = 0, number_of_brack = 0,
      flag_func = 0;
  std::stack<stack_elem> stack_op;
  char *tmp = ex_str;
  if (str != nullptr) {
    while (*str != '\0' && *status != 1) {
      if ((flag_func && *str != '(') || *str == '.') {
        *status = 1;
        break;
      } else {
        flag_func = 0;
      }
      if (*str == '-') {
        if (ex_str == tmp || number_of_brack > 0) {
          stack_op.push({'~', 7});
          str++;
        }
      }
      if (*str == '+') {
        if (ex_str == tmp || number_of_brack > 0) {
          stack_op.push({'`', 7});
          str++;
        }
      }
      parse_number(&ex_str, &str, status, &double_op, &flag_point);
      parse_op(stack_op, &ex_str, &str, status, &flag_op, &double_op,
               &number_of_brack);
      parse_func(stack_op, &str, &flag_op, &flag_func, status, &double_op);
      if (*str != '\0') {
        str++;
      }
    }
    while (stack_op.size() != 0) {
      *ex_str = stack_op.top().elem;
      stack_op.pop();
      ex_str = ex_str + 2;
    }
    if (number_of_brack != 0) *status = 1;
    if (*status != 1) *ex_str = '\0';
    if (*status) {
      ex_str = tmp;
      sprintf(ex_str, "%s", "ERROR");
    }
  }
  return ex_str;
}

void Model::parse_number(char **ex_str, char **str, int *status, int *double_op,
                         int *flag_point) {
  int flag_e = 0;
  int double_e = 0;
  if ((isdigit(**str)) || (**str == '.' && flag_point == 0) || **str == 'x') {
    while (*status != 1 &&
           ((isdigit(**str)) || (**str == '.' && *flag_point <= 1) ||
            **str == 'x' || **str == 'e')) {
      if (isdigit(**str)) {
        flag_e = 1;
      }
      if (**str == '.') {
        *flag_point += 1;
        if (*str + 1 != nullptr) {
          if (!isdigit(*((*str + 1)))) *status = 1;
        }
      }
      if (**str == 'e' && double_e == 0) {
        if (flag_e == 0) {
          *status = 1;
        } else {
          double_e++;
          **ex_str = **str;
          *str = *str + 1;
          *ex_str = *ex_str + 1;
          if (**str == '+' || **str == '-') {
            **ex_str = **str;
            *str = *str + 1;
            *ex_str = *ex_str + 1;
            if ((isdigit(**str))) {
              while ((isdigit(**str))) {
                **ex_str = **str;
                *ex_str = *ex_str + 1;
                *str = *str + 1;
              }
            } else {
              *status = 1;
            }
          } else {
            *status = 1;
          }
        }
      }
      if (double_e == 0) {
        **ex_str = **str;
        *ex_str = *ex_str + 1;
        *str = *str + 1;
      }
    }

    *double_op -= 1;
    *ex_str = *ex_str + 1;
    if (*flag_point >= 2) {
      *status = 1;
    } else {
      *flag_point = 0;
    }
  }
}

void Model::parse_op(std::stack<stack_elem> &stack_op, char **ex_str,
                     char **str, int *status, int *flag_op, int *double_op,
                     int *number_of_brack) {
  int prior = -1;
  stack_elem st;
  if (is_operator(**str) && *double_op != 2) {
    if (**str == '(' && *double_op) {
      if (*number_of_brack >= 0) {
        *number_of_brack += 1;
      } else {
        *status = 1;
      }
    }
    if (**str == ')') {
      if (*number_of_brack == 0) {
        *status = 1;
      } else {
        if (*flag_op) {
          while (stack_op.top().elem != '(') {
            **ex_str = stack_op.top().elem;
            *ex_str = *ex_str + 2;
            stack_op.pop();
          }
          stack_op.pop();
          **ex_str = stack_op.top().elem;
          *ex_str = *ex_str + 2;
          stack_op.pop();
          *flag_op = 0;
        } else {
          while (stack_op.top().elem != '(') {
            **ex_str = stack_op.top().elem;
            *ex_str = *ex_str + 2;
            stack_op.pop();
          }
          stack_op.pop();
        }
        *number_of_brack -= 1;
      }
    } else {
      prior = priority(**str);
      if (stack_op.empty()) {
        stack_op.push({**str, prior});
      } else {
        if (stack_op.top().priority < prior) {
          stack_op.push({**str, prior});
        } else {
          while (!stack_op.empty() && prior <= stack_op.top().priority &&
                 **str != '(') {
            **ex_str = stack_op.top().elem;
            *ex_str = *ex_str + 2;
            stack_op.pop();
          }
          stack_op.push({**str, prior});
        }
      }
    }
    if (**str != '(' && **str != ')') {
      *double_op += 1;
    }
  }
  if (*double_op >= 2) {
    *status = 1;
  }
}

int Model::is_operator(char str) {
  int status = 0;
  switch (str) {
    case '+':
      status = 1;
      break;
    case '-':
      status = 1;
      break;
    case '*':
      status = 1;
      break;
    case '/':
      status = 1;
      break;
    case '^':
      status = 1;
      break;
    case '(':
      status = 1;
      break;
    case ')':
      status = 1;
      break;
    default:
      break;
  }
  return status;
}

int Model::priority(char str) {
  int prior = -1;
  switch (str) {
    case '^':
      prior = 6;
      break;
    case '*':
      prior = 2;
      break;
    case '/':
      prior = 2;
      break;
    case '+':
      prior = 1;
      break;
    case '-':
      prior = 1;
      break;
    case '(':
      prior = 0;
      break;
    default:
      break;
  }
  return prior;
}

void Model::parse_func(std::stack<stack_elem> &stack_op, char **str,
                       int *flag_op, int *flag_func, int *status,
                       int *double_op) {
  char *func[10] = {"sin",  "cos", "tan",  "asin", "acos",
                    "atan", "mod", "sqrt", "ln",   "log"};
  int len = 0, prior = -1;
  char tok = ' ';
  for (int j = 0; j < 10; j++) {
    if (strstr(*str, func[j]) == *str) {
      len = strlen(func[j]);
      tok = tok_func(func[j], &prior);
    }
  }
  if (tok != ' ') {
    stack_op.push({tok, prior});
    if (tok != 'm') {
      *flag_func = 1;
    }
    *flag_op = 1;
    if (tok == 'm') {
      *double_op += 1;
    }
    for (int k = 0; k < len - 1; k++) {
      *str = *str + 1;
    }
    *status = 0;
  } else {
    if (!is_operator(**str) && !isdigit(**str) && **str != '.' &&
        **str != 'x' && **str != '\0') {
      *status = 1;
    }
  }
}

char Model::tok_func(char *str, int *prior) {
  char tok = ' ';
  if (!strcmp(str, "sin")) {
    tok = 's';
    *prior = 5;
  } else if (!strcmp(str, "cos")) {
    tok = 'c';
    *prior = 5;
  } else if (!strcmp(str, "tan")) {
    tok = 't';
    *prior = 5;
  } else if (!strcmp(str, "asin")) {
    tok = 'S';
    *prior = 5;
  } else if (!strcmp(str, "acos")) {
    tok = 'C';
    *prior = 5;
  } else if (!strcmp(str, "atan")) {
    tok = 'T';
    *prior = 5;
  } else if (!strcmp(str, "sqrt")) {
    tok = 'Q';
    *prior = 5;
  } else if (!strcmp(str, "ln")) {
    tok = 'L';
    *prior = 5;
  } else if (!strcmp(str, "log")) {
    tok = 'l';
    *prior = 5;
  } else if (!strcmp(str, "mod")) {
    tok = 'm';
    *prior = 3;
  }
  return tok;
}

double Model::callculation(char *ex_str, int *status, double x) {
  double result = 0.0;
  int i = 0;
  double value = 0;
  std::stack<double> stack_value;
  char str_value[MAX_NUM] = {0};
  int j = 0;
  memset(str_value, ' ', MAX_NUM);
  while (*ex_str != '\0') {
    if (isdigit(*ex_str) || *ex_str == '.' || *ex_str == 'x') {
      if (*ex_str != 'x') {
        while (*ex_str != ' ' && j <= 16) {
          str_value[i] = *ex_str;
          i++;
          ex_str++;
          j++;
        }
        j = 0;
        i = 0;
        value = strtod(str_value, nullptr);
        stack_value.push(value);
        memset(str_value, ' ', MAX_NUM);
      } else {
        stack_value.push(x);
        ex_str++;
      }
    } else {
      func(stack_value, *ex_str, status);
      ex_str++;
    }
    ex_str++;
  }
  if (*status != 1 && stack_value.size() != 0) {
    result = stack_value.top();
  }

  return result;
}

void Model::func(std::stack<double> &stack_value, char symb, int *status) {
  switch (symb) {
    case '+':
      *status = operators(stack_value, *status, symb);
      break;
    case '-':
      *status = operators(stack_value, *status, symb);
      break;
    case '*':
      *status = operators(stack_value, *status, symb);
      break;
    case '/':
      *status = operators(stack_value, *status, symb);
      break;
    case '~':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 'm':
      *status = operators(stack_value, *status, symb);
      break;
    case 's':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 'c':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 't':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 'S':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 'C':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 'T':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 'Q':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 'L':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case 'l':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    case '^':
      *status = operators(stack_value, *status, symb);
      break;
    case '`':
      *status = unar_op_and_functions(stack_value, *status, symb);
      break;
    default:
      *status = 1;
      break;
  }
}

int Model::unar_op_and_functions(std::stack<double> &stack_value, int status,
                                 char curr_op) {
  double b = 0;
  double result = 0;
  if (!stack_value.empty()) {
    if (curr_op == '`') {
      result = stack_value.top();
    } else if (curr_op == '~') {
      result = stack_value.top() * (-1);
    } else if (curr_op == 's') {
      result = sin(stack_value.top());
    } else if (curr_op == 'c') {
      result = cos(stack_value.top());
    } else if (curr_op == 't') {
      result = tan(stack_value.top());
    } else if (curr_op == 'S') {
      result = asin(stack_value.top());
    } else if (curr_op == 'C') {
      result = acos(stack_value.top());
    } else if (curr_op == 'T') {
      result = atan(stack_value.top());
    } else if (curr_op == 'Q') {
      result = sqrt(stack_value.top());
    } else if (curr_op == 'L') {
      result = log(stack_value.top());
    } else if (curr_op == 'l') {
      result = log10(stack_value.top());
    }
    stack_value.pop();
    stack_value.push(result);
  } else {
    status = 1;
  }
  return status;
}

int Model::operators(std::stack<double> &stack_value, int status,
                     char curr_op) {
  if (!stack_value.empty()) {
    double result = 0, a = 0, b = 0;
    b = stack_value.top();
    stack_value.pop();
    if (!stack_value.empty()) {
      a = stack_value.top();
      if (curr_op == '+') {
        result = a + b;
      } else if (curr_op == '-') {
        result = a - b;
      } else if (curr_op == '*') {
        result = a * b;
      } else if (curr_op == '/') {
        result = a / b;
      } else if (curr_op == 'm') {
        result = fmod(a, b);
      } else if (curr_op == '^') {
        result = pow(a, b);
      }

      stack_value.pop();
      stack_value.push(result);
    } else {
      status = 1;
    }
  } else {
    status = 1;
  }
  return status;
}

}  // namespace s21