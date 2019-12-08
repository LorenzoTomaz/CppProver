#include <iostream>
#include <vector>
#include <map>
#include "../include/formula.h"
using std::vector;
using std::map;


Formula::Formula(std::string& formula, bool valid) : formula_(formula), valid_(valid){}

bool Formula::isPValid(std::string& formula){
    int open{0}, close{0}, counter{0};
    for (char& str : formula){
        counter = (str == FormulaOperators::pOpen[0]) ? open++ : open;
        counter = (str == FormulaOperators::pClose[0]) ? close++ : close;
    }
    pOpen_ = open;
    pClose_ = close;
    return (open == close) ? true : false;

}

std::map<std::string, std::string> Formula::getMainOperator(std::string& formula){
    std::map<std::string, std::string> mapOperator;
    std::map<int, std::string> operators;
    int label = 1;
    int position = -1;
    std::string mainOperator;
    std::string index;   
    if (Formula::isPValid(formula)){
        int counter = 1;
        std::vector<std::string> parenteses;
        for (std::string::iterator it = formula.begin(), end = (formula.end() -1); it != end; ++it){
            if (*it == FormulaOperators::pOpen[0]){
                parenteses.push_back(FormulaOperators::pOpen);
            }
            if (*it == (FormulaOperators::conjuntion[0] || (FormulaOperators::disjuntion[0] || (FormulaOperators::mimplication[0] || (FormulaOperators::bimplication[0] || FormulaOperators::negation[0]))))){
                std::string fOperator{*it};
                std::map<int, std::string>::iterator it = operators.begin();
                operators.insert(it, std::pair<int,std::string>(label,fOperator));
                //operators.push_back(fOperator);
                label++;
            }
            if (*it == FormulaOperators::pClose[0]){
                parenteses.push_back(FormulaOperators::pClose);
                auto ptrOperator = operators.find(label);
                operators.erase(ptrOperator);
            }
            if (counter == (formula.size() - 1)){
                std::string strOperator{*it};
                mainOperator = strOperator;
            }
            counter++;
            
        }
        label = operators.begin()->first;
        position = getMainOperatorPosition(formula, label);
        
    }
    
    
    std::map<std::string,std::string>::iterator it = mapOperator.begin();
    mapOperator.insert(it, std::pair<std::string, std::string>("Operator", mainOperator));
    mapOperator.insert(it, std::pair<std::string, std::string>("Index", std::to_string(position)));

    return mapOperator;

}


int Formula::getMainOperatorPosition(std::string& formula, int& label){
    int counter = 1;
    for (std::string::iterator it = formula.begin(), end = (formula.end() -1); it != end; ++it){
        if (*it == (FormulaOperators::conjuntion[0] || (FormulaOperators::disjuntion[0] || (FormulaOperators::mimplication[0] || (FormulaOperators::bimplication[0] || FormulaOperators::negation[0]))))){
                counter++;
        }
        if (counter == label){
                return counter;
        }
    }
    return 0;
}

std::string Formula::removeOuterParenteses(std::string& formula){
    std::string subformula;
    subformula = formula.substr(1, formula.size()-2);
    return subformula;
}

vector<std::string> Formula::splitFormula(std::string& formula){
    std::map<std::string, std::string> mainOperator = Formula::getMainOperator(formula);
    std::vector<std::string> nextFormulas;
    int position = 0;
    auto foperator = mainOperator.find("Operator");
    auto index = mainOperator.find("Index");
    if (foperator->second == FormulaOperators::negation){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula); 
        subformula1 = init.substr(1, init.size());
        nextFormulas.push_back(subformula1);
        nextFormulas.push_back(subformula2);
        return nextFormulas;
    }
    if (foperator->second == FormulaOperators::conjuntion){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula);
        subformula1 = formula.substr(1, position-1);
        subformula2 = formula.substr(position + 1, (formula.size() - (position + 1)));
        nextFormulas.push_back(subformula1);
        nextFormulas.push_back(subformula2);
        return nextFormulas;

    
    }
    if (foperator->second == FormulaOperators::disjuntion){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula);
        subformula1 = formula.substr(1, position-1);
        subformula2 = formula.substr(position + 1, (formula.size() - (position + 1)));
        nextFormulas.push_back(subformula1);
        nextFormulas.push_back(subformula2);
        return nextFormulas;

    
    }
    if (foperator->second == FormulaOperators::mimplication){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula);
        subformula1 = formula.substr(1, position-1);
        subformula2 = formula.substr(position + 1, (formula.size() - (position + 1)));
        nextFormulas.push_back(subformula1);
        nextFormulas.push_back(subformula2);
        return nextFormulas;

    
    }
    if (foperator->second == FormulaOperators::bimplication){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula);
        subformula1 = formula.substr(1, position-1);
        subformula2 = formula.substr(position + 1, (formula.size() - (position + 1)));
        nextFormulas.push_back(subformula1);
        nextFormulas.push_back(subformula2);
        return nextFormulas;

    
    }
    
    return nextFormulas;

}

bool Formula::Validate(std::string& formula){
    //TODO
}