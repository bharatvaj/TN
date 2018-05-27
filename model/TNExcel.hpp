#ifndef _TN_EXCEL
#define _TN_EXCEL
#include <iostream>
using namespace std;
class TNExcel
{
  public:
    string cNum;
    string cName;
    string cType;
    TNExcel(string cNum, string cName, string cType)
    {
        this->cNum = cNum;
        this->cName = cName;
        this->cType = cType;
    }
    string getCNum()
    {
        return cNum;
    }
    string getCName()
    {
        return cName;
    }
    string getCType()
    {
        return cType;
    }
};
#endif