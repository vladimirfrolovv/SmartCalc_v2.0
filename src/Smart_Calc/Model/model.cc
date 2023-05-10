#include "model.h"

namespace s21 {
    char *Model::parse(char *str, char *ex_str, int *status) {
        int i = 0, flag_op = 0, double_op = 1, flag_point = 0, number_of_brack = 0, flag_func = 0;
        stack_elem st;
        std::stack<stack_elem> stack_op;

        if (str != nullptr) {
            while (*str != '\0' && *status != 1) {
                if ((flag_func && *str != '(') || *str == '.') {
                    *status = 1;
                    break;
                } else {
                    flag_func = 0;
                }
                if (*str == '-') {
                    if (i == 0 || number_of_brack > 0) {
                        st.elem = '~';
                        st.priority = 7;
                        stack_op.push(st);
                        str++;
                        i++;
                    }
                }
                if (*str == '+') {
                    if (i == 0 || number_of_brack > 0) {
                        st.elem = '`';
                        st.priority = 7;
                        stack_op.push(st);
                        str++;
                        i++;
                    }
                }
                parse_number(&ex_str, &str, status, &double_op, &flag_point);
                parse_op(stack_op, &ex_str, &str, status, &flag_op,
                         &double_op, &number_of_brack);
                parse_func(stack_op, &str, &flag_op, &flag_func, status,
                           &double_op);
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
            if (*status)sprintf(ex_str, "%s", "ERROR");
        }
        return ex_str;
    }

    void Model::parse_number(char **ex_str, char **str, int *status,
                             int *double_op, int *flag_point) {
        int flag_e = 0;
        int double_e = 0;
        if ((isdigit(**str)) || (**str == '.' && flag_point == 0) || **str == 'x') {
            while (*status != 1 && ((isdigit(**str)) || (**str == '.' && *flag_point <= 1) ||
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
                            if((isdigit(**str))) {
                                while ((isdigit(**str))) {
                                    **ex_str = **str;
                                    *ex_str = *ex_str + 1;
                                    *str = *str + 1;
                                }
                            } else {
                                *status =1;
                            }
                        } else{
                            *status =1;
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

void Model::parse_op(std::stack<stack_elem> &stack_op, char **ex_str, char **str, int *status,
                     int *flag_op, int *double_op, int *number_of_brack) {
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
            if (stack_op.size() == 0) {
                st.elem = **str;
                st.priority = prior;
                stack_op.push(st);
            } else {
                if (stack_op.top().priority < prior) {
                    st.elem = **str;
                    st.priority = prior;
                    stack_op.push(st);
                } else {
                    while (stack_op.size() != 0 && prior <= stack_op.top().priority &&
                           **str != '(') {
                        **ex_str = stack_op.top().elem;
                        *ex_str = *ex_str + 2;
                        stack_op.pop();
                    }
                    st.elem = **str;
                    st.priority = prior;
                    stack_op.push(st);
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

void Model::parse_func(std::stack<stack_elem> &stack_op, char **str, int *flag_op, int *flag_func,
                       int *status, int *double_op) {
    char *func[10] = {"sin", "cos", "tan", "asin", "acos",
                      "atan", "mod", "sqrt", "ln", "log"};
    int len = 0;
    int prior = -1;
    char tok = ' ';
    stack_elem st;
    for (int j = 0; j < 10; j++) {
        if (strstr(*str, func[j]) == *str) {
            len = strlen(func[j]);
            tok = tok_func(func[j], &prior);
        }
    }
    if (tok != ' ') {
        st.elem = tok;
        st.priority = prior;
        stack_op.push(st);
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

}