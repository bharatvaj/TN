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
    exit(EXIT_SUCCESS);
}

void onExcelOpenFail(TNView *v)
{
    v->error("Excel File Invalid", "Cannot open the specified excel file, please check permission of the file before convertion");
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
        v->error("Input Invalid", "Input is not valid");
        return;
    }
    v->alert("Converting", "Conversion is going to start and might take a while. Are you sure you want to continue?");
    log_inf(_MAIN, "Starting conversion");
    TNConvert *convert = new TNConvert();
    if (convert->open(v->getExcelPath(), v->getImagePath()))
    {
        convert->convert();
    }
}

TNEvent *event = TNEvent::getInstance();
TNView *view = TNView::getInstance();
void exit_handler(int sig)
{
    TNEvent::getInstance()->fireEvent(Event::Close, view);
}

int main(int argc, char *argv[])
{
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

    //start program
    signal(SIGINT, exit_handler);
    event->fireEvent(Event::Start, view);
    return view->run();
}