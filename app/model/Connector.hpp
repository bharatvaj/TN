#ifndef _CON_H
#define _CON_H "Connector"
#include <iostream>
class Connector
{

private:
    std::string cName;

    /**
    * @generated
    */
    std::string cType;

    /**
    * @generated
    */
    std::string cNumber;

public:
    /**
     * @generated
     */
    Connector(std::string cName, std::string cType, std::string cNumber)
    {
        this->cName = cName;
        this->cType = cType;
        this->cNumber = cNumber;
    }

    /**
    * @generated
    */
    std::string getCName()
    {
        return this->cName;
    }

    /**
    * @generated
    */
    void setCName(std::string cName)
    {
        this->cName = cName;
    }

    /**
    * @generated
    */
    std::string getCType()
    {
        return this->cType;
    }

    /**
    * @generated
    */
    void setCType(std::string cType)
    {
        this->cType = cType;
    }

    /**
    * @generated
    */
    std::string getCNumber()
    {
        return this->cNumber;
    }

    /**
    * @generated
    */
    void setCNumber(std::string cNumber)
    {
        this->cNumber = cNumber;
    }
};
#endif
