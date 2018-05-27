#ifndef _TN_CONVERT
#define _TN_CONVERT
#include <iostream>
#include <fstream>
#include <TNEvent.hpp>
#include <Excel.hpp>
#include <model/TNExcel.hpp>
#include <model/TNImage.hpp>
using namespace std;
using namespace excel;
namespace tn
{
class TNConvert
{
  private:
    TNView *view = nullptr;
    TNEvent *event = nullptr;
    fstream *excelStream = nullptr;
    fstream *imageStream = nullptr;

    vector<TNExcel> tnExcels;
    vector<TNImage> tnImages;

  public:
    TNConvert()
    {
        view = TNView::getInstance();
        event = TNEvent::getInstance();
    }
    bool open(const char *excelFilePath, const char *imageFilePath)
    {
        fstream *excelStream = new fstream();
        excelStream->open(excelFilePath);
        if (!excelStream)
        {
            event->fireEvent(Event::ExcelOpenFail, view);
            return false;
        }
        event->fireEvent(Event::ExcelOpenSuccess, view);

        fstream *imageStream = new fstream();
        imageStream->open(imageFilePath);
        if (!imageStream)
        {
            event->fireEvent(Event::ImageOpenFail, view);
            return false;
        }
        event->fireEvent(Event::ImageOpenSuccess, view);
        return true;
    }

    void startConversion(){
        event->fireEvent(Event::ConvertSuccess, TNView::getInstance());
    }

    void convert()
    {
        Excel *excel = new Excel();
        //tnExcels.push_back(excel.get(0));

        //Image *ocr_read = OpenCV::Tesseract();
        //tnImages.push_back(ocr_read->get(0));

        startConversion();
    }
};
}
#endif