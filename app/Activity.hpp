#ifndef _ACT_H
#define _ACT_H "Activity"

#include <clog/clog.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#include "Resources.hpp"

class Activity
{
private:
  Fl_Window *win = nullptr;
  int _x = 0;
  int _y = 0;

protected:
public:
  Activity()
  {
    win = new Fl_Window(400, 200, "TIFF Numbering");
    log_inf(_ACT_H, "Main UI created");
  }
  virtual void onCreate()
  {
    log_inf(_ACT_H, "onCreate()");
    win->show();
  }
  virtual void onStart()
  {
    log_inf(_ACT_H, "onStart()");
    onCreate();
  }
  virtual void onResume()
  {
  }
  virtual void onPause()
  {
  }
  virtual void onStop()
  {
  }
  virtual void onRestart()
  {
  }
  virtual void onDestroy()
  {
  }

  Fl_Window *getWindow(int x, int y)
  {
    win->size(x, y);
    return win;
  }
  Fl_Window *getWindow()
  {
    return win;
  }

  int run()
  {
    return Fl::run();
  }
};

#endif