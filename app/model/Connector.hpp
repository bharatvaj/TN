#ifndef _CON_H
#define _CON_H "Connector"
#include <iostream>
class Connector
{

  private:
    std::string cName;
    std::string cType;
    std::string cNumber;
    int referenceCount;

  public:
    Connector(std::string cName, std::string cType, std::string cNumber, int referenceCount = 0)
    {
        this->cName = cName;
        this->cType = cType;
        this->cNumber = cNumber;
    }

    std::string getCName()
    {
        return this->cName;
    }

    void setCName(std::string cName)
    {
        this->cName = cName;
    }

    std::string getCType()
    {
        return this->cType;
    }

    void setCType(std::string cType)
    {
        this->cType = cType;
    }

    std::string getCNumber()
    {
        return this->cNumber;
    }

    void setCNumber(std::string cNumber)
    {
        this->cNumber = cNumber;
    }

    int getReferenceCount()
    {
        return referenceCount;
    }

    void setReferenceCount(int referenceCount)
    {
        this->referenceCount = referenceCount;
    }
};
#endif
