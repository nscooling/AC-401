/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer - C++

  Signal Objects

*/
/*
DISCLAIMER:
Feabhas is furnishing this item "as is". Feabhas does not provide any warranty
of the item whatsoever, whether express, implied, or statutory, including, but
not limited to, any warranty of merchantability or fitness for a particular
purpose or any warranty that the contents of the item will be error-free.
In no respect shall Feabhas incur any liability for any damages, including, but
limited to, direct, indirect, special, or consequential damages arising out of,
resulting from, or any way connected to the use of the item, whether or not
based upon warranty, contract, tort, or otherwise; whether or not injury was
sustained by persons or property or otherwise; and whether or not loss was
sustained from, or arose out of, the results of, the item, or any services that
may be provided by Feabhas.
*/
/* ---------------------------------------------------------------------------*/
#ifndef SIGNAL_H
#define SIGNAL_H

#include "feabhOS_signal.h"

namespace feabhOS
{
  class Signal
  {
  public:
    Signal();
    ~Signal();
    feabhOS_error wait(duration_mSec_t timeout);
    void          notifyOne();
    void          notifyAll();
  
  private:
    feabhOS_SIGNAL handle;
    
    // not implemented
    Signal(const Signal&);
    Signal& operator=(const Signal&);
  };

} // namespace feabhOS

#endif // SIGNAL_H