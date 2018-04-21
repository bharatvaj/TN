#ifndef _RES_H
#define _RES_H "Resources"

#include <iostream>
#include <vector>
#include <xlsxio_write.h>
class Resources
{
  private:
    std::string imagePath;
    std::string sheetPath;

    std::vector<std::vector<std::string>> dataCells;

    static Resources *instance;
    Resources()
    {
    }

  public:
    static Resources *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Resources();
        }
        return instance;
    }

    std::string getImagePath()
    {
        return imagePath;
    }

    void setImagePath(std::string imagePath)
    {
        this->imagePath = imagePath;
    }

    std::string getSheetPath()
    {
        return sheetPath;
    }

    void setSheetPath(std::string sheetPath)
    {
        this->sheetPath = sheetPath;
    }
    std::vector<std::vector<std::string>> &getDataCells()
    {
        return dataCells;
    }
};
Resources *Resources::instance = nullptr;
#endif