// This may look like C, but it's really -*- C++ -*-

//=============================================================================
/**
 *  @file    Wait_On_LF_No_Upcall.h
 *
 *  $Id$
 *
 *  @author  Chris Cleeland <cleeland@ociweb.com>
 */
//=============================================================================


#ifndef TAO_WAIT_ON_LF_NO_UPCALL_H
#define TAO_WAIT_ON_LF_NO_UPCALL_H
#include "ace/pre.h"

#include "tao/Wait_On_Leader_Follower.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

/**
 * @class TAO_Wait_On_LF_No_Upcall
 *
 * @brief Wait according to the Leader-Follower model (like
 * TAO_Wait_On_Leader_Follower), but do not allow nested upcalls.
 *
 * This implementation sets a thread-specific flag on entering wait()
 * that indicates that the thread is unavailable to service upcalls.
 * Connection handler that are acting in a server role cooperate by
 * checking this flag in their handle_input, and returning if they're
 * in a thread that is currently suspending upcalls.  The flag gets
 * reset once the reply is received.
 */

class TAO_Export TAO_Wait_On_LF_No_Upcall : public TAO_Wait_On_Leader_Follower
{
public:
  typedef TAO_Wait_On_Leader_Follower base;
  
  TAO_Wait_On_LF_No_Upcall (TAO_Transport *t) : TAO_Wait_On_Leader_Follower (t) { }
  virtual ~TAO_Wait_On_LF_No_Upcall (void);

  virtual int wait (ACE_Time_Value *max_wait_time,
                    TAO_Synch_Reply_Dispatcher &rd);
};

#include "ace/post.h"
#endif /* TAO_WAIT_ON_LF_NO_UPCALL_H */
