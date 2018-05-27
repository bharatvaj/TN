#ifndef _TN_VIEW
#define _TN_VIEW

#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_File_Chooser.H>

namespace tn
{
class TNView;
}

#include <TNEvent.hpp>

namespace tn
{
const char *app_name = "TN";
const int BROWSE_EXCEL = 0;
const int BROWSE_IMAGE = 1;
class TNView
{
    Fl_Double_Window *window;

  private:
    TNView()
    {
    }
    int _x = 0;
    int _y = 20;
    int leftMargin = 20;
    int topMargin = 20;
    int windowWidth = 500;
    int windowHeight = 256;

    int buttonWidth = 60;
    int buttonHeight = 40;

    bool excelSelected = false;
    bool imageSelected = false;

    static TNView *instance;

    const char *name[20] = {
        "Excel",
        "Image"};

    const char *filter[20] = {
        "*.xlsx"
        "*.png",
    };

    static void convertCallback(Fl_Widget *w, void *o)
    {
        TNView *view = (TNView *)o;
        TNEvent::getInstance()->events[Event::Convert](view);
    }

    static void browseCallback(Fl_Widget *w, void *o)
    {
        int *opt = (int *)o;
        switch (*opt)
        {
        case BROWSE_EXCEL:
            TNEvent::getInstance()->events[Event::ExcelBrowse](TNView::getInstance());
            break;
        case BROWSE_IMAGE:
            TNEvent::getInstance()->events[Event::ImageBrowse](TNView::getInstance());
            break;
        }
    }

    Fl_Double_Window *createWindow()
    {
        Fl_Double_Window *window = new Fl_Double_Window(0, 0, windowWidth, windowHeight, app_name);
        return window;
    }

    Fl_Widget *createField(int opt)
    {
        //Fl_Frame *frame = new Fl
        int textBoxWidth = windowWidth - buttonWidth - (2 * leftMargin);
        int textBoxHeight = buttonHeight;
        Fl_Input *text = new Fl_Input(leftMargin, _y, textBoxWidth, textBoxHeight);
        Fl_Button *btn = new Fl_Button(leftMargin + textBoxWidth, _y, buttonWidth, buttonHeight, name[opt]);
        btn->callback(browseCallback, new int(opt));
        _y += buttonHeight + 20;
        return btn;
    }

    Fl_Button *createConvertButton()
    {
        Fl_Button *btn = new Fl_Button(leftMargin, _y, buttonWidth, buttonHeight, "Convert");
        btn->callback(convertCallback, this);
        return btn;
    }

  public:
    void alert(std::string title, std::string message)
    {
        switch (fl_choice((title + message).c_str(), "Yes", "No", 0))
        {
        case 0:
            //YES
            break;
        case 1:
            //NO
            break;
        }
    }

    void error(std::string title, std::string message)
    {
        fl_choice((title + message).c_str(), "OK", 0, 0);
    }
    bool checkFieldValidity()
    {
        return excelSelected && imageSelected;
    }
    bool runFileChooser(int opt)
    {
        Fl_File_Chooser *chooser = new Fl_File_Chooser("", "", Fl_File_Chooser::SINGLE, "");
        chooser->filter(opt ? filter[0] : filter[1]);
        chooser->show();
        while (chooser->shown())
        {
            Fl::wait();
        }
        switch (opt)
        {
        case BROWSE_EXCEL:
            excelSelected = false;
            return false;
        case BROWSE_IMAGE:
            imageSelected = false;
            return false;
        }
        return false;
    }

    static TNView *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new TNView();
        }
        return instance;
    }

    Fl_Window *getWindow()
    {
        return window;
    }
    int run()
    {
        window = createWindow();
        window->add(createField(BROWSE_EXCEL));
        window->add(createField(BROWSE_IMAGE));
        window->add(createConvertButton());
        window->show();
        return Fl::run();
    }
};
TNView *TNView::instance = nullptr;
}
#endif