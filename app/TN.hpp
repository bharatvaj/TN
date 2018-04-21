#ifndef _TN_H
#define _TN_H "TIFFNumbering"
#include <csignal>
#include <iostream>
#include <functional>
#include <future>
#include <clog/clog.h>
#include <apdf.h>

#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Progress.H>

#include "ActivityInvoker.hpp"
#include "Activity.hpp"
#include "Sheet.hpp"
#include "listener/OnEvent.hpp"

class TN : public Activity
{
private:
  typedef Activity super;
  static TN *instance;

  Fl_Input *edit1;
  Fl_Input *edit2;

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

  void preprocessImage()
  {
    log_inf(_TN_H, "Image Preprocessing");
    //convert from pdf if pdf is present
    //convert to the required resolution if needed
  }

  void convert()
  {
    log_inf(_TN_H, "Converting Image");
    preprocessImage();
    ActivityInvoker<Sheet> ai;
    ai.startActivity();
  }

  TN()
  {
    Resources::getInstance()->setOnUpdateEventListener(new TN::OnFieldUpdateEventListener);
  }

  int __x = 60;
  int __y = 20;
  Fl_Input *createField(std::string label, int type)
  {
    Fl_Input *input = new Fl_Input(__x, __y, 250, 30, label);
    Fl_Button *btn = new Fl_Button(__x + 250, __y, 60, 30, "Browse");
    btn->callback(&TN::buttonCallback, new int(type));
    return input;
  }

public:
  void onCreate()
  {
    super::onCreate();
    edit1 = createField("Image", 1);
    edit2 = createField("XLSX", 2);

    Fl_Button *btn = new Fl_Button(320, 140, 60, 30, "Convert");
    btn->callback(&TN::buttonCallback, new int(0));

    getWindow()->add(edit1);
    getWindow()->add(editBtn1);
    getWindow()->add(edit2);
    getWindow()->add(editBtn2);
    getWindow()->add(btn);
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