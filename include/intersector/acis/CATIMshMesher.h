#ifndef CATIMshMesher_h
#define CATIMshMesher_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U4
 */
//=============================================================================
//
// CATIMshMesher :
// Interface to manage a meshing component
//
//=============================================================================

#include "CATMshBase.h"
#include "CATMshInterrupt.h"
#include "CATMshMessage.h"
#include "ExportedByCATMshMesherCore.h"

class CATIMshMesh;

class ExportedByCATMshMesherCore CATIMshMesher : public CATMshBase {
public:
    virtual void MessageCallback(CATMshMessage& msg) const {}
    virtual int InterruptCallback() { return CATMSH_INTERRUPT_CONTINUE; };

    /**
     * Set the interrupt callback function.
     * @param iCallback (in)
     *   The interrupt callback (or NULL to remove any previous callback)
     * @param iUserData (in)
     *   The user pointer which will be given to iCallback as a parameter
     * @return
     *   an error code
     */
    virtual HRESULT SetInterruptCallback(CATMshInterruptCB iCallback,
                                         void* iUserData) = 0;

    /**
     * Set the message callback function.
     * @param iCallback (in)
     *   The message callback (or NULL to remove any previous callback)
     * @param iUserData (in)
     *   The user pointer which will be given to iCallback as a parameter
     * @return
     *   an error code
     */
    virtual HRESULT SetMessageCallback(CATMshMessageCB iCallback,
                                       void* iUserData) = 0;

    /**
     * Generate the mesh
     * @return
     *   an error code
     */
    virtual HRESULT Mesh() = 0;

    /**
     * Returns the mesh generated
     * @return
     *   an error code
     */
    virtual CATIMshMesh* GetMesh() = 0;
};

#endif
