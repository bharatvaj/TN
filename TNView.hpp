#ifndef _TN_VIEW
#define _TN_VIEW "TNView"

#include <iostream>
#include <clog/clog.h>
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

  private:
    Fl_Double_Window *window;
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

    static TNView *instance;

    Fl_Input *imageInput = nullptr;
    Fl_Input *excelInput = nullptr;

    const char *name[20] = {
        "Excel",
        "Image"};

    const char *filter_excel[20] = {
        "*.xlsx"
        "*.xls",
    };

    const char *filter_image[20] = {
        ".tiff",
        ".jpg",
        "*png"};

    static void
    convertCallback(Fl_Widget *w, void *o)
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

    static void windowCallback(Fl_Widget *w, void *o)
    {
        TNEvent::getInstance()->fireEvent(Event::Close, TNView::getInstance());
    }

    Fl_Double_Window *createWindow()
    {
        Fl_Double_Window *window = new Fl_Double_Window(0, 0, windowWidth, windowHeight, app_name);
        window->callback(windowCallback);
        return window;
    }

    Fl_Widget *createField(int opt)
    {
        //Fl_Frame *frame = new Fl
        int textBoxWidth = windowWidth - buttonWidth - (2 * leftMargin);
        int textBoxHeight = buttonHeight;
        Fl_Input *text = new Fl_Input(leftMargin, _y, textBoxWidth, textBoxHeight);
        if (opt == BROWSE_EXCEL)
        {
            excelInput = text;
        }
        else if (opt == BROWSE_IMAGE)
        {
            imageInput = text;
        }
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
    const char *getImagePath()
    {
        return imageInput->value();
    }

    const char *getExcelPath()
    {
        return excelInput->value();
    }

    void alert(std::string title, std::string message)
    {
        fl_message_title(title.c_str());
        switch (fl_choice((message).c_str(), "Yes", "No", 0))
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
        fl_message_title(title.c_str());
        fl_choice((message).c_str(), "OK", 0, 0);
    }
    bool checkFieldValidity()
    {
        if (imageInput->value() != NULL && excelInput != NULL)
        {
            return true;
        }
        return false;
    }
    bool runFileChooser(int opt)
    {
        Fl_File_Chooser *chooser = new Fl_File_Chooser("", "", Fl_File_Chooser::SINGLE, "");

        switch (opt)
        {
        case BROWSE_EXCEL:
        {
            chooser->filter(*filter_excel);
            chooser->show();
            while (chooser->shown())
            {
                Fl::wait();
            }
            const char *path = chooser->value();
            if (path == NULL)
            {
                log_err(_TN_VIEW, "Excel not valid");
                return false;
            }
            excelInput->value(path);
            return true;
        }
        case BROWSE_IMAGE:
        {
            chooser->filter(*filter_image);
            chooser->show();
            while (chooser->shown())
            {
                Fl::wait();
            }
            const char *path = chooser->value();
            if (path == NULL)
            {
                log_err(_TN_VIEW, "Image not valid");
                return false;
            }
            imageInput->value(path);
            return true;
        }
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