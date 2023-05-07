#include "s21_smart_calc.h"

char *s21_parse(char *str, char *ex_str, int *status) {
  int i = 0;
  int flag_op = 0;
  int double_op = 1;
  int flag_point = 0;
  int number_of_brack = 0;
  int flag_func = 0;
  list *list_op = NULL;
  if (str != NULL) {
    while (*str != '\0' && *status != 1) {
      if ((flag_func && *str != '(') || *str == '.') {
        *status = 1;
        break;
      } else {
        flag_func = 0;
      }
      if (*str == '-') {
        if (i == 0 || number_of_brack > 0) {
          list_op = s21_push(list_op, '~', 7);
          str++;
        }
      }
      if (*str == '+') {
        if (i == 0 || number_of_brack > 0) {
          list_op = s21_push(list_op, '`', 7);
          str++;
        }
      }
      i = s21_parse_number(ex_str, &str, status, i, &double_op, &flag_point);
      list_op = s21_parse_op(list_op, ex_str, &str, status, &i, &flag_op,
                             &double_op, &number_of_brack);
      list_op = s21_parse_func(list_op, &str, &flag_op, &flag_func, status,
                               &double_op);
      if (*str != '\0') {
        str++;
      }
    }
    while (list_op != NULL) {
      ex_str[i] = list_op->elem;
      list_op = s21_pop(list_op);
      i += 2;
    }

    if (number_of_brack != 0) {
      *status = 1;
    }
    if (*status != 1) {
      ex_str[i] = '\0';
    }

    if (*status) {
      sprintf(ex_str, "%s", "ERROR");
    }
  }
  return ex_str;
}

int s21_parse_number(char *ex_str, char **str, int *status, int i,
                     int *double_op, int *flag_point) {
  if ((isdigit(**str)) || (**str == '.' && flag_point == 0) || **str == 'x') {
    while ((isdigit(**str)) || (**str == '.' && *flag_point <= 1) ||
           **str == 'x' || **str == 'y') {
      if (**str == '.') {
        *flag_point += 1;
        if (*str + 1 != NULL) {
          if (!isdigit(*((*str + 1)))) *status = 1;
        }
      }
      ex_str[i] = **str;
      i += 1;
      *str = *str + 1;
    }
    *double_op -= 1;
    i += 1;
    if (*flag_point >= 2) {
      *status = 1;
    } else {
      *flag_point = 0;
    }
  }

  return i;
}

list *s21_parse_op(list *list_op, char *ex_str, char **str, int *status, int *i,
                   int *flag_op, int *double_op, int *number_of_brack) {
  int prior = -1;
  if (s21_is_operator(**str) && *double_op != 2) {
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
          while (list_op->elem != '(') {
            ex_str[*i] = list_op->elem;
            *i = *i + 2;
            list_op = s21_pop(list_op);
          }
          list_op = s21_pop(list_op);
          ex_str[*i] = list_op->elem;
          *i = *i + 2;
          list_op = s21_pop(list_op);
          *flag_op = 0;
        } else {
          while (list_op->elem != '(') {
            ex_str[*i] = list_op->elem;
            *i = *i + 2;
            list_op = s21_pop(list_op);
          }
          list_op = s21_pop(list_op);
        }
        *number_of_brack -= 1;
      }
    } else {
      prior = s21_priority(**str);
      if (list_op == NULL) {
        list_op = s21_push(list_op, **str, prior);
      } else {
        if (list_op->priority < prior) {
          list_op = s21_push(list_op, **str, prior);
        } else {
          while (list_op != NULL && prior <= list_op->priority &&
                 **str != '(') {
            ex_str[*i] = list_op->elem;
            *i = *i + 2;
            list_op = s21_pop(list_op);
          }
          list_op = s21_push(list_op, **str, prior);
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
  return list_op;
}

int s21_is_operator(char str) {
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

int s21_priority(char str) {
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

list *s21_parse_func(list *list_op, char **str, int *flag_op, int *flag_func,
                     int *status, int *double_op) {
  char *func[10] = {"sin",  "cos", "tan",  "asin", "acos",
                    "atan", "mod", "sqrt", "ln",   "log"};
  int len = 0;
  int prior = -1;
  char tok = ' ';
  for (int j = 0; j < 10; j++) {
    if (strstr(*str, func[j]) == *str) {
      len = strlen(func[j]);
      tok = s21_tok_func(func[j], &prior);
    }
  }
  if (tok != ' ') {
    list_op = s21_push(list_op, tok, prior);
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
    if (!s21_is_operator(**str) && !isdigit(**str) && **str != '.' &&
        **str != 'x' && **str != '\0') {
      *status = 1;
    }
  }

  return list_op;
}

char s21_tok_func(char *str, int *prior) {
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
