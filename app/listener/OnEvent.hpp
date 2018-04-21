#ifndef _ON_EVE_H
#define _ON_EVE_H "OnEvent"

template <class T>
class OnEvent
{
  public:
    OnEvent()
    {
    }
    virtual void onEvent(T t)
    {
    }
};

#endif