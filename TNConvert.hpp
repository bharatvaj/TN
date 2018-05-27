#ifndef _CONVERT
#define _CONVERT
#include <iostream>
#include <TNEvent.hpp>
namespace tn
{
class TNConvert
{
  public:
    TNConvert()
    {
    }
    bool open(std::string excelFilePath, std::string imageFilePath)
    {
        TNEvent::getInstance()->fireEvent(Event::ExcelOpenFail, TNView::getInstance());
        return false;
    }
};
}
#endif