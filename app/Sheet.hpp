#ifndef _SHEET_H
#define _SHEET_H "Sheet"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <FL/Fl_Table.H>

#include "Activity.hpp"

class Sheet : public Activity
{
  private:
    typedef Activity super;
    Fl_Table *table;

  public:
    Sheet()
    {
        getWindow(400, 600)->set_modal();
        table = new Fl_Table(0, 0, 600, 300, "Table");
    }
    void onCreate() override
    {
        getWindow()->add(table);
    }
};
#endif