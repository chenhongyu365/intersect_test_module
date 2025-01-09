#ifndef CATMshInterrupt_H
#define CATMshInterrupt_H
// COPYRIGHT Dassault Systemes 2022
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//===================================================================
//
// CATMshInterrupt.h
// Define the CATMshInterrupt callback
//
//===================================================================

#include "CATMshBase.h"
#include "ExportedByCATMshMesherCore.h"


/** Value to use in the implementation of an interrupt callback to
    request the process to cleanly stop */
#define CATMSH_INTERRUPT_STOP 1
/** Value to use in the implementation of an interrupt callback
    request the process to immediately abort */
#define CATMSH_INTERRUPT_ABORT 2
/** Value to use in the implementation of an interrupt callback to
    request the process to continue */
#define CATMSH_INTERRUPT_CONTINUE 0


/**
 * Type for an interrupt callback function. This function will be called by a module to
 * to know whether it should stop its curent computation or not.
 * @param iUserData : 
 *   a user pointer.
 * @param oInterruptStatus :
 *   the user decision to stop or not. (see define above)
 */
typedef HRESULT (*CATMshInterruptCB)(int &oInterruptStatus, void *iUserData);

/**
* @nodoc : intern usage only
*/
ExportedByCATMshMesherCore HRESULT InterruptCBEmpty(int &oInterruptStatus, void *iUserData);

#endif
