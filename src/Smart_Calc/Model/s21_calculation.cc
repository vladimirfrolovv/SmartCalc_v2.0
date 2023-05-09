//#include "model.h"

double s21_callculation(char *ex_str, int *status, double x) {
  double result = 0.0;
  int i = 0;
  double value = 0;
  std *list_val = NULL;
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
        value = strtod(str_value, NULL);
        list_val = s21_push_value(list_val, value);
        memset(str_value, ' ', MAX_NUM);
      } else {
        list_val = s21_push_value(list_val, x);
        ex_str++;
      }
    } else {
      list_val = s21_func(list_val, *ex_str, status);
      ex_str++;
    }
    ex_str++;
  }
  if (*status != 1 && list_val != NULL) {
    result = list_val->value;
  }
  if (list_val != NULL) {
    s21_remove_val(list_val);
  }

  return result;
}

list_value *s21_func(list_value *list_val, char symb, int *status) {
  switch (symb) {
    case '+':
      list_val = s21_add(list_val, status);
      break;
    case '-':
      list_val = s21_sub(list_val, status);
      break;
    case '*':
      list_val = s21_mul(list_val, status);
      break;
    case '/':
      list_val = s21_div(list_val, status);
      break;
    case '~':
      list_val = s21_unar_min(list_val, status);
      break;
    case 'm':
      list_val = s21_mod(list_val, status);
      break;
    case 's':
      list_val = s21_sin(list_val, status);
      break;
    case 'c':
      list_val = s21_cos(list_val, status);
      break;
    case 't':
      list_val = s21_tan(list_val, status);
      break;
    case 'S':
      list_val = s21_asin(list_val, status);
      break;
    case 'C':
      list_val = s21_acos(list_val, status);
      break;
    case 'T':
      list_val = s21_atan(list_val, status);
      break;
    case 'Q':
      list_val = s21_sqrt(list_val, status);
      break;
    case 'L':
      list_val = s21_ln(list_val, status);
      break;
    case 'l':
      list_val = s21_log(list_val, status);
      break;
    case '^':
      list_val = s21_degree(list_val, status);
      break;
    case '`':
      list_val = s21_unar_plus(list_val, status);
      break;
    default:
      *status = 1;
      break;
  }

  return list_val;
}

list_value *s21_add(list_value *list_val, int *status) {
  double a = 0;
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    if (list_val != NULL) {
      a = list_val->value;
      list_val = s21_pop_value(list_val);
      result = a + b;
      list_val = s21_push_value(list_val, result);
    } else {
      *status = 1;
    }
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_sub(list_value *list_val, int *status) {
  double a = 0;
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    if (list_val != NULL) {
      a = list_val->value;
      list_val = s21_pop_value(list_val);
      result = a - b;
      list_val = s21_push_value(list_val, result);
    } else {
      *status = 1;
    }
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_mul(list_value *list_val, int *status) {
  double a = 0;
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    if (list_val != NULL) {
      a = list_val->value;
      list_val = s21_pop_value(list_val);
      result = a * b;
      list_val = s21_push_value(list_val, result);
    } else {
      *status = 1;
    }
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_div(list_value *list_val, int *status) {
  double a = 0;
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    if (list_val != NULL) {
      a = list_val->value;
      list_val = s21_pop_value(list_val);
      result = a / b;
      list_val = s21_push_value(list_val, result);
    } else {
      *status = 1;
    }
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_unar_min(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = b * (-1);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_mod(list_value *list_val, int *status) {
  double a = 0;
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    if (list_val != NULL) {
      a = list_val->value;
      list_val = s21_pop_value(list_val);
      result = fmod(a, b);
      list_val = s21_push_value(list_val, result);
    } else {
      *status = 1;
    }
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_sin(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = sin(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_cos(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = cos(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_tan(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = tan(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_asin(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = asin(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_acos(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = acos(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_atan(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = atan(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_ln(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = log(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_log(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = log10(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_sqrt(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = sqrt(b);
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_degree(list_value *list_val, int *status) {
  double a = 0;
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    if (list_val != NULL) {
      a = list_val->value;
      list_val = s21_pop_value(list_val);
      result = pow(a, b);
      list_val = s21_push_value(list_val, result);
    } else {
      *status = 1;
    }
  } else {
    *status = 1;
  }
  return list_val;
}

list_value *s21_unar_plus(list_value *list_val, int *status) {
  double b = 0;
  double result = 0;
  if (list_val != NULL) {
    b = list_val->value;
    list_val = s21_pop_value(list_val);
    result = b;
    list_val = s21_push_value(list_val, result);
  } else {
    *status = 1;
  }
  return list_val;
}