#include <csignal>
#include <iostream>
#include <functional>
#include <future>
#include <clog/clog.h>
#include <xlsxwriter.h>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Input.H>

#include "Activity.hpp"
#include "Sheet.hpp"

#define TN_MAIN "TIFFNumbering"
#define UI_MAIN "UI"

class TN : public Activity
{
private:
  typedef Activity super;
  static TN *instance;
  TN();
  void convert();
  void browse(int);
  std::string sheetPath;
  std::string imagePath;

  Fl_Input *edit1;
  Fl_Button *editBtn1;

  Fl_Input *edit2;
  Fl_Button *editBtn2;

  static void buttonCallback(Fl_Widget *, void *);

public:
  static TN *getInstance();
  void onCreate() override;
  void onDestroy() override;
  ~TN();
};