#ifndef _TN_EVENT
#define _TN_EVENT
#include <iostream>
#include <map>
#include <functional>

#include <TNView.hpp>

namespace tn
{
typedef std::function<void(TNView *)> Callback;

enum class Event
{
    Start,
    Close,

    ExcelOpenFail,
    ExcelOpenSuccess,
    ExcelBrowse,

    ImageOpenFail,
    ImageOpenSuccess,
    ImageBrowse,

    ConvertFail,
    ConvertSuccess,
    Convert
};

class TNEvent
{
  private:
    static TNEvent *instance;
    TNEvent()
    {
    }

  public:
    std::map<Event, Callback> events;

    void addEventHandler(Event event, tn::Callback callback)
    {
        TNEvent::getInstance()->events[event] = callback;
    }

    void fireEvent(Event event, TNView *v)
    {
        TNEvent::getInstance()->events[event](v);
    }

    static TNEvent *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new TNEvent();
        }
        return instance;
    }
};
TNEvent *TNEvent::instance = nullptr;
}
#endif