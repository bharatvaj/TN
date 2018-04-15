#include <csignal>
#include <iostream>
#include <functional>
#include <future>
#include <clog/clog.h>
#include <xlsxwriter.h>
#include "Activity.hpp"

#define TN_MAIN "TIFFNumbering"
#define UI_MAIN "UI"

class TN : public Activity
{
  private:
    typedef Activity super;
    static TN *instance;
    TN();
    void convert();
    void onCreate() override;
    void onDestroy() override;

    static void but_cb(Fl_Widget *, void *);

  public:
    static TN *getInstance();
    ~TN();
};