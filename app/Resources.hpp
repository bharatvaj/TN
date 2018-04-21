#ifndef _RES_H
#define _RES_H "Resources"

#include <iostream>
#include <vector>
#include "listener/OnEvent.hpp"

class Resources
{
  private:
    std::string imagePath;
    std::string sheetPath;
    std::vector<std::vector<std::string>> dataCells;
    OnEvent<std::string> *onEventListener = nullptr;
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
        onEventListener->onEvent(imagePath);
    }

    std::string getSheetPath()
    {
        return sheetPath;
    }

    void setSheetPath(std::string sheetPath)
    {
        this->sheetPath = sheetPath;
        onEventListener->onEvent(sheetPath);
    }
    std::vector<std::vector<std::string>> &getDataCells()
    {
        return dataCells;
    }

    void setOnUpdateEventListener(OnEvent<std::string> *onEventListener)
    {
        this->onEventListener = onEventListener;
    }
};
Resources *Resources::instance = nullptr;
#endif