#ifndef _ON_EVE_H
#define _ON_EVE_H "OnEventListener"

#include <TNEvent.hpp>
#include <Caller.hpp>

namespace tn
{
class OnEventListener
{
public:
  OnEventListener()
  {
  }
  virtual void onEvent(Caller call)
  {
  }
};
}

#endif