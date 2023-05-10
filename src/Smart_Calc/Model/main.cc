#include "model.h"

int main() {
    char ex_str[MAX_STR] = {0};

//    char *ex_str = "22e-1";
    int status = 0;
    memset(ex_str, ' ', MAX_STR);
    s21::Model mod;
 mod.parse("3-(10+55)/2*(30-(50-25))+4^2*2/(4-3*(2-5)", ex_str, &status);
 double val = mod.callculation(ex_str,&status,0.0);

//double val = strtod(ex_str, nullptr);
//val*=2;
//    "1*3-(10+55)/2*(30-(50-25))+4^2*2/(4-3*(2-
//    5))"
//    s21::Model::stack_elem st;
//std::stack<s21::Model::stack_elem> s({st});
//s.top();
//   for(int i = 0; i < 90; i++){
//
//       std::cout <<ex_str[i];
//   }

       std::cout << val;
    return 0;
}