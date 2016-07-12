/* ---------------------------------------------------------------------------*/
/*

  FeabhOS OS abstraction layer - C++

  Message Queue

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
#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "TemplateBuffer.h"
#include "Mutex.h"
#include "Condition.h"

namespace feabhOS
{
  template<typename MessageType = int, unsigned int sz = 8>
  class MessageQueue : private Buffer<MessageType, sz>
  {
  public:
    MessageQueue();
    feabhOS_error post(const MessageType& in_msg, duration_mSec_t timeout = WAIT_FOREVER);
    feabhOS_error get(MessageType& inout_msg, duration_mSec_t timeout = WAIT_FOREVER);
    bool isEmpty();

  private:
    MessageQueue(const MessageQueue&);
    MessageQueue& operator=(const MessageQueue&);

    typedef Buffer<MessageType, sz> BufferBase;
    Mutex mutex;
    Condition notEmpty;
    Condition notFull;
  };
  

  template<typename MessageType, unsigned int sz>
  MessageQueue<MessageType, sz>::MessageQueue() :
    Buffer<MessageType, sz>(),
    mutex(),
    notEmpty(),
    notFull()
  {
  }


  template<typename MessageType, unsigned int sz>
  feabhOS_error MessageQueue<MessageType, sz>::post(const MessageType& in_msg, duration_mSec_t timeout)
  {
    CRITICAL_SECTION(mutex)
    {
      // Speculatively attempt to add to the buffer. If it's
      // full we'll get a FULL error message back.  If that's
      // the case, suspend until another task retrieves a
      // value.
      //
      while(BufferBase::add(in_msg) == BufferBase::FULL)
      {
        if(notFull.wait(mutex, timeout) != ERROR_OK)
        {
          return ERROR_TIMED_OUT;
        }
      }
    }
    // Wake any tasks waiting for data in the buffer.
    //
    notEmpty.notify();
    return ERROR_OK;
  }

  
  template<typename MessageType, unsigned int sz>
  feabhOS_error MessageQueue<MessageType, sz>::get(MessageType& inout_msg, duration_mSec_t timeout)
  {
    CRITICAL_SECTION(mutex)
    {
      // NOTE: Here we must make a direct call
      // to the base class isEmpty() function,
      // rather than call our public method.  If
      // we call the public method we will deadlock
      // the system because we've already locked
      // the mutex!
      //
      while(BufferBase::isEmpty())
      {
        if(notEmpty.wait(mutex, timeout) != ERROR_OK)
        {
          return ERROR_TIMED_OUT;
        }
      }
      BufferBase::get(inout_msg);
    }
    // Wake any threads waiting for there to
    // be some space in the buffer.
    //
    notFull.notify();
    return ERROR_OK;
  }


  template<typename MessageType, unsigned int sz>
  bool MessageQueue<MessageType, sz>::isEmpty()
  {
    CRITICAL_SECTION(mutex)
    {
      return BufferBase::isEmpty();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace no_feabhOS
{
  using feabhOS::Buffer;

  template<typename MessageType = int, unsigned int sz = 8>
  class MessageQueue : private Buffer<MessageType, sz>
  {
  public:
    MessageQueue();
    feabhOS_error post(const MessageType& in_msg, duration_mSec_t timeout = NO_WAIT);
    feabhOS_error get(MessageType& inout_msg, duration_mSec_t timeout  = NO_WAIT);
    bool isEmpty();

  private:
    MessageQueue(const MessageQueue&);
    MessageQueue& operator=(const MessageQueue&);

    typedef Buffer<MessageType, sz> BufferBase;
  };


  template<typename MessageType, unsigned int sz>
  MessageQueue<MessageType, sz>::MessageQueue() :
    Buffer<MessageType, sz>()
  {
  }


  template<typename MessageType, unsigned int sz>
  feabhOS_error MessageQueue<MessageType, sz>::post(const MessageType& in_msg, duration_mSec_t timeout)
  {
    BufferBase::Error error;
    error = BufferBase::add(in_msg);
    return((error == BufferBase::OK) ? ERROR_OK : ERROR_QUEUE_FULL);
  }


  template<typename MessageType, unsigned int sz>
  feabhOS_error MessageQueue<MessageType, sz>::get(MessageType& inout_msg, duration_mSec_t timeout)
  {
    BufferBase::Error error;
    error = BufferBase::get(inout_msg);
    return((error == BufferBase::OK) ? ERROR_OK : ERROR_QUEUE_EMPTY);
  }


  template<typename MessageType, unsigned int sz>
  bool MessageQueue<MessageType, sz>::isEmpty()
  {
    return BufferBase::isEmpty();
  }
}


#endif // MESSAGEQUEUE_H