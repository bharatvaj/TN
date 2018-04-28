#ifndef _ON_EVE_H
#define _ON_EVE_H "OnEventListener"
#include <ui/Activity.hpp>

namespace tn
{
template <class T>
class OnEventListener
{
public:
  OnEventListener()
  {
  }
  virtual void onEvent(Activity *, T) = 0;
};
}

#endif