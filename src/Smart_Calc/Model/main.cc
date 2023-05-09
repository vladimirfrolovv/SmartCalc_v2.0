#include "model.h"

int main() {
    char ex_str[MAX_STR] = {0};
    int status = 0;
    memset(ex_str, ' ', MAX_STR);
    s21::Model mod;
 mod.parse("1*3-(10+55)/2*(30-(50-25))+4^2*2/(4-3*(2-5))", ex_str, &status);
//   for(int i = 0; i < 50; i++){
//       std::cout <<ex_str[i];
//   }


    return 0;
}