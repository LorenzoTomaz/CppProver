#include <iostream>
#include <vector>
#include <map>
#include "../include/formula.h"
using std::vector;
using std::map;


Formula::Formula(std::string& formula, bool valid) : formula_(formula), valid_(valid){}

bool Formula::isPValid(std::string& formula){
    //std::cout << "isPValid" << "\n";
    int open{0}, close{0}, counter{0};
    for (char& str : formula){
        counter = (str == FormulaOperators::pOpen[0]) ? open++ : open;
        counter = (str == FormulaOperators::pClose[0]) ? close++ : close;
    }
    ////std::cout << "open" << open << "close" << close << "\n";
    pOpen_ = open;
    pClose_ = close;
    return (open == close) ? true : false;

}

std::map<std::string, std::string> Formula::getMainOperator(std::string& formula){
    //std::cout << "getMainOperator" << "\n";
    std::map<std::string, std::string> mapOperator;
    std::vector<std::string> operators;
    std::vector<int> positions;
    int label = 0;
    int position = -1;
    std::string mainOperator;
    std::string index;   
    if (Formula::isPValid(formula)){
        //std::cout << "IfisPValid" << "\n";
        int counter = 0;
        std::vector<std::string> parenteses;
        for (std::string::iterator it = formula.begin(), end = formula.end(); it != end; ++it){
            ////std::cout << "forLoopGetMainOperator" << "\n";
            if (*it == FormulaOperators::pOpen[0]){
                parenteses.push_back(FormulaOperators::pOpen);
                ////std::cout << "forIFpOpen" << "\n";
            }
            ////std::cout << "forIFAfterpOpen" << *it << "\n";
           //if (*it == (FormulaOperators::conjuntion[0] || (FormulaOperators::disjuntion[0] || (FormulaOperators::mimplication[0] || (FormulaOperators::bimplication[0] || FormulaOperators::negation[0]))))){
             if (*it == (FormulaOperators::bimplication[0]) || *it == (FormulaOperators::disjuntion[0])){  
                ////std::cout << "forIFOperator" << "\n";
                std::string fOperator{*it};
                //std::map<int, std::string>::iterator it = operators.end();
                //operators.insert(it, std::pair<int,std::string>(label,fOperator));
                operators.push_back(fOperator);
                positions.push_back(counter);
                //operators.push_back(fOperator);
                label++;

                
            }
            if (it == end -1){
                ////std::cout << "forIFStop" << "\n";
                break;
            }
            if (*it == FormulaOperators::pClose[0]){
                parenteses.push_back(FormulaOperators::pClose);
                //auto ptrOperator = operators.end();
                //std::cout << "operator size: " << operators.size() << "\n";
                operators.pop_back();
                positions.pop_back();
                ////std::cout << "forIFpClose" << "\n";
            }
            
            counter++;
            ////std::cout << "forIFAfterpOpen" << "\n";
        }
        ////std::cout << "label: " << label << "\n";
        ////std::cout << "Operator: " << operators[0] << "\n";
        mainOperator = operators[0];
        ////std::cout << "formula: " << formula << "\n";
        position = positions[0];
        ////std::cout << "position: " << position << "\n";
        
    }
    ////std::cout << "outforLoopGetMainOperator" << mainOperator << "\n";
    
    std::map<std::string,std::string>::iterator it = mapOperator.begin();
    mapOperator.insert(it, std::pair<std::string, std::string>("Operator", mainOperator));
    mapOperator.insert(it, std::pair<std::string, std::string>("Index", std::to_string(position)));
    ////std::cout << "returnGetMainOperator" << mapOperator.find("Operator")->second << " " << mapOperator.find("Index")->second << "\n";
    return mapOperator;

}


int Formula::getMainOperatorPosition(std::string& formula, int& label){
    ////std::cout << "getMainOperatorPosition" << "\n";
    int oCounter = 0;
    int counter = 0;
    ////std::cout << "formulaTest: "<< formula << "\n";
    for (std::string::iterator it = formula.begin(), end = formula.end(); it != end; ++it){
        //if (*it == (FormulaOperators::conjuntion[0] || (FormulaOperators::disjuntion[0] || (FormulaOperators::mimplication[0] || (FormulaOperators::bimplication[0] || FormulaOperators::negation[0]))))){
        ////std::cout << "it: " << *it << "\n";
        if (*it == (FormulaOperators::bimplication[0]) || *it == (FormulaOperators::disjuntion[0])){ //
                ////std::cout << "biimplication" << "\n";
                oCounter++;
        }
        ////std::cout << "oCounter: " << oCounter << counter << "\n";
        counter++;
        if (oCounter == label){      
                ////std::cout << "counter: " << counter << "\n";
                return counter;
        }
    }
    return 0;
}

std::string Formula::removeOuterParenteses(std::string& formula){
    ////std::cout << "removeOuterParenteses" << "\n";
    ////std::cout << "formulaTest1" << formula << "\n";
    ////std::cout << "index: 0" << formula[0] << "index: -1"  << formula.back() << "\n";
    std::string subformula;
    if (formula[0] == FormulaOperators::pOpen[0] && formula.back() == FormulaOperators::pClose.back()){
        subformula = formula.substr(1, formula.size()-2);
        ////std::cout << "subformula" << subformula << "\n";
    }
    else{
        subformula = formula;
    }
    return subformula;
}

vector<std::string> Formula::splitFormula(std::string& formula){
    ////std::cout << "splitFormula" << "SPLIT" << "\n";
    std::map<std::string, std::string> mainOperator = getMainOperator(formula);
    ////std::cout << "mainOperator: " << mainOperator.find("Operator")->second << "Index :" << mainOperator.find("Index")->second << "\n";
    std::vector<std::string> nextFormulas;
    int position = 0;
    auto foperator = mainOperator.find("Operator");
    auto index = mainOperator.find("Index");
    if (foperator->second == FormulaOperators::negation){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula);
        //implementation with only one negation operator assigned to a formula 
        mainOperator = getMainOperator(formula);
        if (!init.empty()){
            subformula1 = init.substr(0, position - 1);
            ////std::cout << "subformula1" << subformula1 << "\n"; 
            ////std::cout << "size: " << (init.size() - position) << "size1: " << init.size() << "\n";
            subformula2 = init.substr(position,init.size());
            ////std::cout << "subformula2" << subformula2 << "\n";
            nextFormulas.push_back(subformula1);
            nextFormulas.push_back(subformula2);
        }
        return nextFormulas;
    }
    if (foperator->second == FormulaOperators::conjuntion){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        //std::cout << "position: " << position << "\n";
        std::string init = removeOuterParenteses(formula);
        if (!init.empty()){
            subformula1 = init.substr(0, position - 1);
            ////std::cout << "subformula1" << subformula1 << "\n"; 
            ////std::cout << "size: " << (init.size() - position) << "size1: " << init.size() << "\n";
            subformula2 = init.substr(position,init.size());
            ////std::cout << "subformula2" << subformula2 << "\n";
            nextFormulas.push_back(subformula1);
            nextFormulas.push_back(subformula2);
        }
        return nextFormulas;

    
    }
    if (foperator->second == FormulaOperators::disjuntion){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula);
        if (!init.empty()){
            subformula1 = init.substr(0, position - 1);
            ////std::cout << "subformula1" << subformula1 << "\n"; 
            ////std::cout << "size: " << (init.size() - position) << "size1: " << init.size() << "\n";
            subformula2 = init.substr(position,init.size());
            ////std::cout << "subformula2" << subformula2 << "\n";
            nextFormulas.push_back(subformula1);
            nextFormulas.push_back(subformula2);
        }    
        return nextFormulas;

    
    }
    if (foperator->second == FormulaOperators::mimplication){
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula);
        if (!init.empty()){
            subformula1 = init.substr(0, position - 1);
            ////std::cout << "subformula1" << subformula1 << "\n"; 
            ////std::cout << "size: " << (init.size() - position) << "size1: " << init.size() << "\n";
            subformula2 = init.substr(position,init.size());
            ////std::cout << "subformula2" << subformula2 << "\n";
            nextFormulas.push_back(subformula1);
            nextFormulas.push_back(subformula2);
        }
        return nextFormulas;

    
    }
    if (foperator->second == FormulaOperators::bimplication){
        ////std::cout << "splitFormula" << "\n";
        std::string subformula1, subformula2;
        position = stoi(index->second);
        std::string init = removeOuterParenteses(formula);
        ////std::cout << "init: " << init << "\n";
        if (!init.empty()){
            subformula1 = init.substr(0, position - 1);
            ////std::cout << "subformula1" << subformula1 << "\n"; 
            //std::cout << "size: " << (init.size() - position) << "size1: " << init.size() << "\n";
            subformula2 = init.substr(position,init.size());
            ////std::cout << "subformula2" << subformula2 << "\n";
            nextFormulas.push_back(subformula1);
            nextFormulas.push_back(subformula2);
            
        }
        return nextFormulas;
        

    
    }
    
    return nextFormulas;

}

//First version only with double node split
std::vector<std::map<std::vector<int>, std::string>> Formula::constructTree(std::string& formula){
    //std::cout << "constructTree" << "\n";
    std::vector<std::map<std::vector<int>, std::string>> tree;
    std::vector<std::string> nextFormula;
    std::string  nextFormulaLeft, nextFormulaRight, newFormula;
    std::map<std::vector<int>, std::string> nextNode, nextNode1;
    std::map<std::vector<int>, std::string> firstNode;
    std::map<std::vector<int>, std::string> ::iterator it = firstNode.begin();
    firstNode.insert(it, std::pair<std::vector<int>, std::string>(0, formula));
    tree.push_back(firstNode);
    std::string formula1, formula2;
    std::vector<int> nodeInfo1, nodeInfo2;
    int nodeParent = 0;
    int treeHeight = 0;
    nextFormula = splitFormula(formula);
    while(!tree[treeHeight].empty()){
        for(std::map<std::vector<int>, std::string>::iterator iter = tree[treeHeight].begin(), end = tree[treeHeight].end(); iter != end; ++iter){//for(auto vctr: tree[treeHeight]){
                ////std::cout << "tree size: " << tree[treeHeight].size() << " " << iter->second << "\n";
                nodeInfo1.push_back(nodeParent);
                nodeInfo1.push_back(nodeParent + 1);
                nodeInfo2.push_back(nodeParent);
                nodeInfo2.push_back(nodeParent + 2); 
                newFormula = iter->second;
                if (newFormula.size() > 2){
                nextFormula = splitFormula(newFormula);
                //adjust loop
                std::map<std::vector<int>, std::string>::iterator it = nextNode.end();           
                if (!nextFormula[1].empty()){
                    nextNode.insert(it, std::pair<std::vector<int>, std::string>(nodeInfo1, nextFormula[0]));
                    std::map<std::vector<int>, std::string>::iterator it = nextNode.end();
                    nextNode.insert(it, std::pair<std::vector<int>, std::string>(nodeInfo2, nextFormula[1]));
                    
                }
                /*else{
                    nextNode.clear();
                    tree.push_back(nextNode);
                }*/
                
                //to complete
                }
                else{
                    nodeParent++;
                    continue;
                }
                nodeParent++;
        }
        tree.push_back(nextNode);
        nextNode.clear();
        treeHeight++; 
        ////std::cout << "counting..." << "\n";
    }
    tree_ = tree;
    return tree;
}


bool Formula::Validate(std::string& formula){
    std::vector<std::map<std::vector<int>, std::string>> tree = constructTree(formula);
    //Todo Implementation
    for(auto Vector : tree ){
        for(auto Map : Vector){
            std::cout << "Map Value: " << Map.second << "\n";  
        }
    }
    return true;
}