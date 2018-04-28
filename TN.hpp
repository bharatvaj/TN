#ifndef _TN_H
#define _TN_H "TIFFNumbering"
#include <csignal>
#include <iostream>
#include <vector>
#include <functional>
#include <future>
#include <clog/clog.h>
#include <unistd.h>

#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Progress.H>
#include <FL/fl_ask.H>

#include <ui/Activity.hpp>
#include "ui/ActivityInvoker.hpp"

#include <Event.hpp>

#include "OCRReader.hpp"
#include "listener/OnEventListener.hpp"

namespace tn
{
class TN : public Activity
{
private:
  typedef Activity super;

  std::string imagePath;
  std::string sheetPath;
  std::vector<std::vector<std::string>> dataCells;
  OnEventListener<std::string> *onEventListener = nullptr;

  Fl_Input *edit1;
  Fl_Input *edit2;
  Fl_Progress *progressBar;
  Fl_Button *convertBtn;

  class OnFieldUpdateEventListener : public OnEventListener<std::string>
  {
  public:
    OnFieldUpdateEventListener()
    {
    }
    void onEvent(Activity *act, std::string s) override
    {
      TN *tn = (TN *)act;
      tn->edit1->value(tn->getImagePath().c_str());
      tn->edit2->value(tn->getSheetPath().c_str());
    }
  };

  void setOnUpdateEventListener(OnEventListener<std::string> *onEventListener)
  {
    this->onEventListener = onEventListener;
  }
  void setImagePath(std::string imagePath)
  {
    this->imagePath = imagePath;
  }

  std::string getImagePath()
  {
    return imagePath;
  }

  std::string getSheetPath()
  {
    return sheetPath;
  }

  void setSheetPath(std::string sheetPath)
  {
    this->sheetPath = sheetPath;
  }

  void setOnEventListener(enum Event e, OnEventListener<std::string> *listener)
  {
  }

  void onImageSelected(std::string image)
  {

    edit1->value(image.c_str());
  }

  void onSheetSelected(std::string sheet)
  {
  }

  static void
  buttonCallback(Fl_Widget *o, void *type)
  {
    //TN *tn = TN::getInstance();
    TN *tn;
    switch (*(int *)type)
    {
    case 0:
      tn->convert();
      break;
    case 1:
      tn->browse(0);
      break;
    case 2:
      tn->browse(1);
      break;
    }
  }
  void browse(int type)
  {
    Fl_Native_File_Chooser fnfc;
    fnfc.title("Pick a file");
    fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
    fnfc.directory("/"); // default directory to use
                         // Show native chooser

    switch (type)
    {
    case 0:
      fnfc.filter("Image Files \t*.{tiff,png,jpeg}");
      break;
    case 1:
      fnfc.filter("Excel Files \t*.{xlsx, xls}");
      break;
    }
    switch (fnfc.show())
    {
    case -1:
      fl_choice(fnfc.errmsg(), "OK", nullptr, nullptr, nullptr);
      break; // ERROR
    case 1:
      break; // CANCEL
    default:
      if (type == 0)
        ;
      //TNController::getInstance()->setImagePath(fnfc.filename());
      else
        ;
      //TNController::getInstance()->setSheetPath(fnfc.filename());
      break; // FILE CHOSEN
    }
  }

  void processStartUI()
  {
    progressBar->minimum(0); // set progress range to be 0.0 ~ 1.0
    progressBar->maximum(1);
    progressBar->color(0x88888800);           // background color
    progressBar->selection_color(0x4444ff00); // progress bar color
    progressBar->labelcolor(FL_WHITE);        // percent text color
    for (int t = 1; t <= 500; t++)
    {
      progressBar->value(t / 500.0); // update progress bar with 0.0 ~ 1.0 value
      char percent[10];
      sprintf(percent, "%d%%", int((t / 500.0) * 100.0));
      progressBar->label(percent); // update progress bar's label
      Fl::check();                 // give fltk some cpu to update the screen
      usleep(1000);                // 'your stuff' that's compute intensive
    }
    log_inf(_TN_H, "Converting Image");
  }

  //TODO
  void processEndUI()
  {
  }

  std::vector<std::string> *processImage(std::string imagePath)
  {
    log_inf(_TN_H, "Image Preprocessing");
    //TODO convert from pdf if pdf is present
    //convert to the required resolution if needed
    return OCRReader::getStringFromImage(imagePath);
  }

  std::vector<std::vector<std::string>> *processExcel(std::string excelPath)
  {
    return nullptr;
  }

  void mixAndMatch(std::vector<std::string> *words, std::vector<std::vector<std::string>> *table)
  {
  }

  void setProgress(int progress)
  {
    //progressBar
  }

  void convert()
  {
    processStartUI();
    auto imageStrings = processImage(getImagePath());
    auto sheetStrings = processExcel(getSheetPath());
    mixAndMatch(imageStrings, sheetStrings);
    processEndUI();
  }

  int __x = 60;
  int __y = 20;
  Fl_Input *createField(const char *label, int type)
  {
    Fl_Input *input = new Fl_Input(__x, __y, 250, 30, label);
    Fl_Button *btn = new Fl_Button(__x + 250, __y, 60, 30, "Browse");
    btn->callback(&TN::buttonCallback, new int(type));
    getWindow()->add(input);
    getWindow()->add(btn);
    __y += 60;
    return input;
  }

public:
  TN()
  {
  }

  void onCreate()
  {
    super::onCreate();
    edit1 = createField("Image", 1);
    edit2 = createField("XLSX", 2);
    progressBar = new Fl_Progress(0, 380, 400, 20);
    convertBtn = new Fl_Button(320, 140, 60, 30, "Convert");
    convertBtn->callback(&TN::buttonCallback, new int(0));
    getWindow()->add(convertBtn);
    getWindow()->add(progressBar);
    getWindow()->resizable(progressBar);
  }

  void onDestroy()
  {
    super::onDestroy();
  }

  ~TN()
  {
    //TODO cleanup memory before exit
  }
};
}
#endif