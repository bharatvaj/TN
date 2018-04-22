#ifndef _SHEET_H
#define _SHEET_H "Sheet"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "MyTable.hpp"

#include "Activity.hpp"
#include "Resources.hpp"

class Sheet : public Activity
{
  private:
    Sheet()
    {
    }
    static Sheet *instance;
    typedef Activity super;
    MyTable *table;
    Fl_Button *btn;

  public:
    static Sheet *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Sheet();
        }
        return instance;
    }

    void exportToDocument(std::string outputPath)
    {
        log_inf(_SHEET_H, "Exporting to file");
    }
    static void buttonCallback(Fl_Widget *o, void *type)
    {
        Sheet *sheet = Sheet::getInstance();
        ;
        Fl_Native_File_Chooser fnfc;
        fnfc.title("Pick a file");
        fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
        fnfc.directory("/");
        fnfc.filter("Image Files \t*.{tiff,png,jpeg}");

        switch (fnfc.show())
        {
        case -1:
            fl_choice(fnfc.errmsg(), "OK", nullptr, nullptr, nullptr);
            break; // ERROR
        case 1:
            break; // CANCEL
        default:
            std::string s(fnfc.filename());
            sheet->exportToDocument(s);
            break; // FILE CHOSEN
        }
    }

    void onStart() override
    {
        log_inf(_SHEET_H, "onStart()");
        getWindow(400, 650)->set_modal();
        table = new MyTable(0, 0, 400, 590, "Table");
        table->cols(4);
        table->rows(20);
        btn = new Fl_Button(400, 600, 60, 30, "Export");
        btn->callback(buttonCallback);
        super::onStart();
    }

    void
    onCreate() override
    {
        log_inf(_SHEET_H, "onCreate()");
        super::onCreate();
        getWindow()->add(table);
        getWindow()->resizable(table);
        getWindow()->add(btn);
        while(getWindow()->shown()) Fl::wait();
    }
};
Sheet *Sheet::instance = nullptr;
#endif