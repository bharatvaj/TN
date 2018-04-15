#ifndef _ACT_H
#define _ACT_H "Activity"

#include <clog/clog.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

class Activity
{
private:
  Fl_Window *win = nullptr;

protected:
  virtual void onCreate()
  {
    log_inf(_ACT_H, "Activity created onCreate()");
  }
  virtual void onStart()
  {
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

public:
  Activity()
  {
    win = new Fl_Window(400, 200, "TIFF Numbering");
    win->show();
    log_inf(_ACT_H, "Main UI created");
    onStart();
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
    onCreate();
    return Fl::run();
  }
};

#endif