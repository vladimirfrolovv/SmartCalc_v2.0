#include "model.h"

int main() {
    char ex_str[MAX_STR] = {0};
    int status = 0;
    memset(ex_str, ' ', MAX_STR);
    s21::Model mod;
 mod.parse(    "2.2-2*2/2-2mod3-sin(2)*cos(2)/tan(4)+asin(5)", ex_str, &status);
//    "1*3-(10+55)/2*(30-(50-25))+4^2*2/(4-3*(2-5))"
//    s21::Model::stack_elem st;
//std::stack<s21::Model::stack_elem> s({st});
//s.top();
   for(int i = 0; i < 90; i++){

       std::cout <<ex_str[i];
   }


    return 0;
}