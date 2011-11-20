////////////////////////////////////////////////////////////////////////////////
/// @brief mutexes, locks and condition variables
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2011 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2011, triagens GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_PHILADELPHIA_BASICS_LOCKS_H
#define TRIAGENS_PHILADELPHIA_BASICS_LOCKS_H 1

#include <Basics/Common.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief posix threads
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_HAVE_POSIX_THREADS
#include <Basics/locks-posix.h>
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief posix spins
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_HAVE_POSIX_THREADS
#include <Basics/locks-posix.h>
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief Mac OS X spins
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_HAVE_MACOS_SPIN
#include <Basics/locks-macos.h>
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief windows threads
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_HAVE_WIN32_THREADS
#include <Basics/locks-win32.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// --SECTION--                                                             MUTEX
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a new mutex
////////////////////////////////////////////////////////////////////////////////

void TRI_InitMutex (TRI_mutex_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroyes a mutex
////////////////////////////////////////////////////////////////////////////////

void TRI_DestroyMutex (TRI_mutex_t*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief locks mutex
////////////////////////////////////////////////////////////////////////////////

void TRI_LockMutex (TRI_mutex_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief unlocks mutex
////////////////////////////////////////////////////////////////////////////////

void TRI_UnlockMutex (TRI_mutex_t*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                              SPIN
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a new spin-lock
////////////////////////////////////////////////////////////////////////////////

void TRI_InitSpin (TRI_spin_t* spin);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroyes a spin-lock
////////////////////////////////////////////////////////////////////////////////

void TRI_DestroySpin (TRI_spin_t* spin);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief locks spin-lock
////////////////////////////////////////////////////////////////////////////////

void TRI_LockSpin (TRI_spin_t* spin);

////////////////////////////////////////////////////////////////////////////////
/// @brief unlocks spin-lock
////////////////////////////////////////////////////////////////////////////////

void TRI_UnlockSpin (TRI_spin_t* spin);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                   READ-WRITE LOCK
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a new read-write lock
////////////////////////////////////////////////////////////////////////////////

void TRI_InitReadWriteLock (TRI_read_write_lock_t* lock);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroyes a read-write lock
////////////////////////////////////////////////////////////////////////////////

void TRI_DestroyReadWriteLock (TRI_read_write_lock_t* lock);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief read locks read-write lock
////////////////////////////////////////////////////////////////////////////////

void TRI_ReadLockReadWriteLock (TRI_read_write_lock_t* lock);

////////////////////////////////////////////////////////////////////////////////
/// @brief read unlocks read-write lock
////////////////////////////////////////////////////////////////////////////////

void TRI_ReadUnlockReadWriteLock (TRI_read_write_lock_t* lock);

////////////////////////////////////////////////////////////////////////////////
/// @brief write locks read-write lock
////////////////////////////////////////////////////////////////////////////////

void TRI_WriteLockReadWriteLock (TRI_read_write_lock_t* lock);

////////////////////////////////////////////////////////////////////////////////
/// @brief write unlocks read-write lock
////////////////////////////////////////////////////////////////////////////////

void TRI_WriteUnlockReadWriteLock (TRI_read_write_lock_t* lock);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                CONDITION VARIABLE
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a new condition variable
////////////////////////////////////////////////////////////////////////////////

void TRI_InitCondition (TRI_condition_t* cond);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a new condition variable with existing mutex
////////////////////////////////////////////////////////////////////////////////

void TRI_Init2Condition (TRI_condition_t* cond, TRI_mutex_t* mutex);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroys a condition variable
////////////////////////////////////////////////////////////////////////////////

void TRI_DestroyCondition (TRI_condition_t* cond);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief signals a condition variable
///
/// Note that you must hold the lock.
////////////////////////////////////////////////////////////////////////////////

void TRI_SignalCondition (TRI_condition_t* cond);

////////////////////////////////////////////////////////////////////////////////
/// @brief broad casts a condition variable
///
/// Note that you must hold the lock.
////////////////////////////////////////////////////////////////////////////////

void TRI_BroadcastCondition (TRI_condition_t* cond);

////////////////////////////////////////////////////////////////////////////////
/// @brief waits for a signal on a condition variable
///
/// Note that you must hold the lock.
////////////////////////////////////////////////////////////////////////////////

void TRI_WaitCondition (TRI_condition_t* cond);

////////////////////////////////////////////////////////////////////////////////
/// @brief locks the mutex of a condition variable
////////////////////////////////////////////////////////////////////////////////

void TRI_LockCondition (TRI_condition_t* cond);

////////////////////////////////////////////////////////////////////////////////
/// @brief unlocks the mutex of a condition variable
////////////////////////////////////////////////////////////////////////////////

void TRI_UnlockCondition (TRI_condition_t* cond);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// @addtogroup\\|// --SECTION--\\)"
// End:
