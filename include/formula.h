#include <iostream>
#include <vector>
#include <map>
#include "operators.h"
using std::vector;
using std::map;
class Formula{
public:
    Formula(std::string& formula, bool valid);
    bool operator<(Formula& formula);
    bool Validate(std::string& formula) ;
    std::vector<std::string> splitFormula(std::string& formula);
    std::map<std::string, std::string> getMainOperator(std::string& formula);
    int getMainOperatorPosition(std::string& formula, int& label);
    std::string removeOuterParenteses(std::string& formula);
    bool isPValid(std::string& formula);
    bool isValid() const;
    std::string getFormula() const;
    //void setFormula(std::string& formula);
    //void setTree() const;
    //std::map<int, std::string> getTree() const;
    //void setTreeVector(std::map<int, std::string>& tree) ;
    //std::vector<std::string> getTreeVector() const;
    //std::string toString();

private:
    int pOpen_{0};
    int pClose_{0};
    bool valid_;
    std::string formula_;
    std::map<int, std::string> tree_;
    std::vector<std::string> tree_vector_;



};

