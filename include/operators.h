#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
#include <string>
namespace FormulaOperators {

const std::string negation{"~"};
const std::string conjuntion{"&"};
const std::string disjuntion{"|"};
const std::string mimplication{">"};
const std::string bimplication{"*"};
const std::string pOpen{"("};
const std::string pClose{"("};

};

#endif


/*
--- Tableux rules for propositional logic ---
Negation:
1.~~A
    A    
Conjunction:
1. A & B
     A
     B
2. ~(A & B)
       /\
     ~A ~B
Disjuntion:
1. (A | B)
      /\
     A  B
2. ~(A | B)
      ~A
      ~B
Material Implication:
1. A > B
    /\
  ~A  B
2. ~(A > B)
       A
      ~B
Biimplication:
1.  A * B
    /   \
A ^ B ~A ^ ~B         
2. ~(A * B)
     /   \
A ^ ~B ~A ^ B
*/