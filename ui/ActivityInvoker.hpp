#ifndef _ACT_INV_H
#define _ACT_INV_H "ActivityInvoker"
#include <FL/Fl.H>
template <class T>
class ActivityInvoker
{
    static bool _gui_instance;

  public:
    T *t;
    ActivityInvoker()
    {
        t = T::getInstance();
    }
    ActivityInvoker(T *t)
    {
        this->t = t;
    }

    int startActivity()
    {
        t->onStart();
        if (!_gui_instance)
        {
            _gui_instance = true;
            Fl::run();
        }
        return 0;
    }
};
template <class T>
bool ActivityInvoker<T>::_gui_instance = false;
#endif
