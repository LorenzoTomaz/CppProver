#ifndef MAIN_EXCEPTION_H
#define MAIN_EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>
#include "../include/formula.h"
#include "../include/operators.h"
using namespace std;

class mainException: public std::exception
{
public:
  mainException(){
    
  }
  ~mainException(){

  }
  virtual const char* what() const throw(){
    return "Arguments Error, desirable format should be: ./prover <formula>";
    }

} MException;


#endif
