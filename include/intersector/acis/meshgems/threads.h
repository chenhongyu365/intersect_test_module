#ifndef __MESHGEMS_THREADS_H__
#define __MESHGEMS_THREADS_H__
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */
#include <meshgems/basic_types.h>
#include <meshgems/mdecl.h>
#include <meshgems/status.h>

/**
 * Type for a callback function to be called on thread creation.
 * @param user_data (in) : a user pointer.
 * @return a status code
 */
typedef meshgems_status_t (*meshgems_start_thread_callback_t)(void* user_data);

/**
 * Type for a callback function to be called on thread destruction.
 * @param user_data (in) : a user pointer.
 * @return a status code
 */
typedef meshgems_status_t (*meshgems_stop_thread_callback_t)(void* user_data);

#endif
