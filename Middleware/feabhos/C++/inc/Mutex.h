/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer - C++

  Mutex Objects

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
#ifndef MUTEX_H
#define MUTEX_H

#include "feabhOS_mutex.h"


namespace feabhOS
{
  class Mutex
  {
  public:
    Mutex();
    ~Mutex();
    feabhOS_error lock(duration_mSec_t timeout);
    void          unlock();
    
  private:
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex&);

    // feabhOS-specific implementation
    //
    feabhOS_MUTEX handle;
  };
  
  
  // ---------------------------------------------------
  // ScopeLock implements the 
  // scope-locked idiom for 
  // mutexes.
  //
  class ScopeLock
  {
  public:
    ScopeLock(Mutex& mtx) : mutex(mtx) { mutex.lock(WAIT_FOREVER); }
    ~ScopeLock() { mutex.unlock(); }
    operator bool() { return true; }
    
  private:
    Mutex& mutex;
  };
  
} // namespace feabhOS  
  
// Neat little macro to simplify code.
// Requires the ScopeLock class to implement
// operator bool()
//
#define CRITICAL_SECTION(mtx) if(feabhOS::ScopeLock s = mtx)



#endif // MUTEX_H