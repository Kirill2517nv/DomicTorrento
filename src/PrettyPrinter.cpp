#include "PrettyPrinter.hpp"
#include <iostream>


PrintPretty::PrintPretty()
{
}

void PrintPretty::visit(BenInt* pInteger)
{
	sData += std::to_string(pInteger->GetValue());
}

void PrintPretty::visit(BenList* pList)
{
    sData += "[\n";
    sCurrIndent += "    ";
    bool bComma = false;
    for (auto bItem : *pList)
    {
        if (bComma)
        {
            sData += ", ";
        }
        sData += sCurrIndent;
        bItem->accept(this);
        bComma = true;
    }
    sCurrIndent = sCurrIndent.substr(0, sCurrIndent.length() - 4);
    sData = sData + "\n" + sCurrIndent + "]";
    //sData += "\n]";
}

void PrintPretty::visit(BenDict* pDict)
{
    sData += "{\n";
    sCurrIndent += "    ";
    bool bComma = false;
    for (auto bItem : *pDict)
    {
        if (bComma)
        {
            sData += ", ";
            sData += "\n";
        }
        sData += sCurrIndent;
        bItem.first->accept(this);
        sData += " : ";
        bItem.second->accept(this);
        bComma = true;
    }
    sCurrIndent = sCurrIndent.substr(0, sCurrIndent.length() - 4);
    sData = sData + "\n" + sCurrIndent + "}";
}

void PrintPretty::visit(BenString* pString)
{
	sData += '"' + pString->GetValue() + '"';
}

void PrintPretty::Print(std::shared_ptr<BenValues> pData)
{
	pData->accept(this);
	std::cout << sData << std::endl;
}
