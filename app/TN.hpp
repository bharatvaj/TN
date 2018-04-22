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

#include "Excel.hpp"
#include "ActivityInvoker.hpp"
#include "Activity.hpp"
#include "Sheet.hpp"
#include "OCRReader.hpp"
#include "listener/OnEvent.hpp"

class TN : public Activity
{
private:
  typedef Activity super;
  static TN *instance;

  Fl_Input *edit1;
  Fl_Input *edit2;
  Fl_Progress *progressBar;
  Fl_Button *convertBtn;

  class OnFieldUpdateEventListener : public OnEvent<std::string>
  {
  public:
    OnFieldUpdateEventListener()
    {
    }
    void onEvent(std::string s) override
    {
      TN::getInstance()->edit1->value(Resources::getInstance()->getImagePath().c_str());
      TN::getInstance()->edit2->value(Resources::getInstance()->getSheetPath().c_str());
    }
  };

  static void
  buttonCallback(Fl_Widget *o, void *type)
  {
    TN *tn = TN::getInstance();
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
        Resources::getInstance()->setImagePath(fnfc.filename());
      else
        Resources::getInstance()->setSheetPath(fnfc.filename());
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

  void processEndUI()
  {
    ActivityInvoker<Sheet> ai;
    ai.startActivity();
  }

  std::vector<std::string> *processImage(std::string imagePath)
  {
    log_inf(_TN_H, "Image Preprocessing");
    //TODO convert from pdf if pdf is present
    //convert to the required resolution if needed
    return OCRReader::getStringFromImage(imagePath);
  }

  std::vector<std::vector<std::string>> *processExcel(std::string excelPath){
    return nullptr;
  }

  void mixAndMatch(std::vector<std::string> *words, std::vector<std::vector<std::string> > *table){

  }


  void convert()
  {
    processStartUI();
    auto imageStrings = processImage(Resources::getInstance()->getImagePath());
    auto sheetStrings = processExcel(Resources::getInstance()->getSheetPath());
    mixAndMatch(imageStrings, sheetStrings);
    processEndUI();
  }

  TN()
  {
    Resources::getInstance()->setOnUpdateEventListener(new TN::OnFieldUpdateEventListener);
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

  static TN *getInstance()
  {
    if (TN::instance == nullptr)
    {
      log_inf(_TN_H, "Initialzing TN");
      TN::instance = new TN();
    }
    return TN::instance;
  }

  ~TN()
  {
    //TODO cleanup memory before exit
  }
};
TN *TN::instance = nullptr;
#endif