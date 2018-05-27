#include <csignal>
#include <iostream>
#include <map>
#include <functional>

#include <TNView.hpp>
#include <TNEvent.hpp>
#include <TNConvert.hpp>

#include <clog/clog.h>

#define _MAIN "TN_MAIN"

using namespace tn;

void onStart(TNView *v)
{
    log_inf(_MAIN, "Start");
}

void onClose(TNView *v)
{
    log_inf(_MAIN, "Close");
}

void onExcelOpenFail(TNView *v)
{
    v->error(_MAIN, "Cannot open the specified excel file, please check permission of the file before convertion");
    log_err(_MAIN, "Excel file open fail");
}

void onExcelOpenSuccess(TNView *v)
{
    log_inf(_MAIN, "Excel file open success");
}

void onExcelBrowse(TNView *v)
{
    log_inf(_MAIN, "Browsing excel file");
    v->runFileChooser(tn::BROWSE_EXCEL);
}

void onImageOpenFail(TNView *v)
{
    log_err(_MAIN, "Image file open fail");
}

void onImageOpenSuccess(TNView *v)
{
    log_inf(_MAIN, "Image file open success");
}

void onImageBrowse(TNView *v)
{
    log_inf(_MAIN, "Browsing image file");
    v->runFileChooser(tn::BROWSE_IMAGE);
}

void onConvertFail(TNView *v)
{
    log_err(_MAIN, "Conversion failed");
}

void onConvertSuccess(TNView *v)
{
    log_inf(_MAIN, "Conversion successful");
}

void onConvert(TNView *v)
{
    if (!v->checkFieldValidity())
    {
        v->error(_MAIN, "Input is not valid");
        return;
    }
    v->alert("Converting", "Please wait for some moment while conversion takes place");
    log_inf(_MAIN, "Startig conversion");
}

TNEvent *event = TNEvent::getInstance();
TNView *view = TNView::getInstance();
void exit_handler(int sig)
{
    TNEvent::getInstance()->fireEvent(Event::Close, view);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, exit_handler);
    //register callbacks
    event->addEventHandler(Event::Start, onStart);
    event->addEventHandler(Event::Close, onClose);

    event->addEventHandler(Event::ExcelOpenFail, onExcelOpenFail);
    event->addEventHandler(Event::ExcelOpenSuccess, onExcelOpenSuccess);
    event->addEventHandler(Event::ExcelBrowse, onExcelBrowse);

    event->addEventHandler(Event::ImageOpenFail, onImageOpenFail);
    event->addEventHandler(Event::ImageOpenSuccess, onImageOpenSuccess);
    event->addEventHandler(Event::ImageBrowse, onImageBrowse);

    event->addEventHandler(Event::ConvertFail, onConvertFail);
    event->addEventHandler(Event::ConvertSuccess, onConvertSuccess);
    event->addEventHandler(Event::Convert, onConvert);

    return view->run();
}