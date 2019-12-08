#include <iostream>
#include "../include/formula.h"
#include "../include/operators.h"
using std::cout;

int main(){
    std::string strFormula = "A*A";
    Formula* formula = new Formula(strFormula, false);
    std::cout << "creating Formula object" << "..." << "\n";
    delete formula;
    std::cout << "Formula object deleted" << "..." << "\n";
}