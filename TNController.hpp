#ifndef _TN_CONT_H
#define _TN_CONT_H "TNController"

#include <TN.hpp>

namespace tn
{
class TNController
{

  private:
    TN *tn;
    static TNController *instance;

    TNController()
    {
        tn = new TN();
        /*
        tn->onImageSelected(tn->sheetSelected);
        tn->onSheetSelected(tn->imageSelected);
        tn->onConvertButtonPressed(TN::convertButtonPressed);
        tn->run();
        */
        ActivityInvoker<TN> ai(tn);
        ai.startActivity();
        //onEventListener->onEvent(tn, imagePath);
        //onEventListener->onEvent(tn, sheetPath);
    }

  public:
    static TNController *getInstance()
    {
        {
            instance = new TNController();
        }
        return instance;
    }
};
TNController *TNController::instance = nullptr;
}
#endif