#include <iostream>
#include <exception>
#include "../include/formula.h"
#include "../include/operators.h"
#include "../include/mainException.h"
using std::cout;

int main(int argc, char *argv[]){
        
    try{
        if(argc > 2){
                throw MException;
        }

        std::string strFormula = argv[1];
        Formula* formula = new Formula(strFormula, false);
        std::cout << "creating Formula object" << "..." << "\n";
        formula->Validate(strFormula);
        delete formula;
        std::cout << "Formula object deleted" << "..." << "\n";}
    catch (mainException& e){
        std::cout << e.what() << "\n";
    }
    return 0;
}