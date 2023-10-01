#ifndef VISITOR_HXX
#define VISITOR_HXX 
#include<string>
#include<memory>
#include "Values.hpp"


class BenValues;
class BenInt;
class BenList;
class BenDict;
class BenString;

class PrintPretty
{
public:
    PrintPretty();
private:
    std::string sData;
    std::string sCurrIndent;
public:
    void visit(BenInt* pInteger);
    void visit(BenList* pList);
    void visit(BenDict* pDict);
    void visit(BenString* pString);

    void Print(std::shared_ptr<BenValues> pData);
};
#endif /* VISITOR_HXX */