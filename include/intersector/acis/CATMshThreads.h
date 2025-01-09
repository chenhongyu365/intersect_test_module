#ifndef CATMshThreads_h
#define CATMshThreads_h

// COPYRIGHT Dassault Systemes 2022
/**
 * @CAA2Level L0
 * @CAA2Usage U3
 */

//===================================================================
//
// CATMshThreads.h
// Define the thread callbacks
//
//===================================================================

/**
 * Type for a callback function to be called on thread creation.
 * @param iUserData (in) : a user pointer.
 * @return a HRESULT
 */
typedef HRESULT (*CATMshStartThreadCB)(void *iUserData);

/**
 * Type for a callback function to be called on thread destruction.
 * @param iUserData (in) : a user pointer.
 * @return a HRESULT
 */
typedef HRESULT(*CATMshStopThreadCB)(void *iUserData);

#endif
