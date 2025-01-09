#ifndef SPACSMbridge_hxx
#define SPACSMbridge_hxx

#include <functional>
#include <memory>
#include <map>
#include <vector>

#include "param.hxx"
#include "position.hxx"

#include "CATIMshMesh.h"
#include "CATMshCSMCommon.h"
#include "CATMshCSMGeneric.h"
#include "CATMshCVMSpa.h"

#include "SPA3dPmACIS.h"

class ENTITY;
class VERTEX;
class EDGE;
class FACE;
class CELL;
class ENTITY_LIST;


/**
* @file SPACSMbridge.hxx
* @CAA2Level L1
* @CAA2Usage U1
* \addtogroup ACIS3DPM
*
* @{
*/

namespace SpaCsmCvm
{

/**
* The <tt>auto_release_unique_ptr</tt> is a smart pointer utility structure that works like <tt>std::unique_ptr</tt>.
* It calls the <tt>Release</tt> function of the pointer when the object's destructor is called.
*/
template<typename T>
struct auto_release_unique_ptr : std::unique_ptr<T, std::function<void (T*)>>
{
	auto_release_unique_ptr(T *p) :
		std::unique_ptr<T, std::function<void (T*)>>(p, [](T *q){ if (q) q->Release(); })
	{}
};

/**
* Specifies a point on an <tt>EDGE</tt> or a <tt>COEDGE</tt>.
*/
struct DiscretizationPoint
{
	/**
	* The edge or coedge parameter of the point.
	*/
	SPAparameter t;

	/**
	* The uv surface parameter of the point.
	* Ignored if the discretized entity is an edge,
	* or the discretized entity is a coedge belonging to a wire,
	* or <tt>uv_valid</tt> is <tt>false</tt>.
	*/
	SPApar_pos uv;

	/**
	* The xyz 3D position of the point in world coordinates, (not body coordinates).
	* This means that any body transformation must have already been applied to these coordinates.
	* Ignored if <tt>xyz_valid</tt> is <tt>false</tt>.
	*/
	SPAposition xyz;

	/**
	* True if the uv parameters are valid.
	* False if the uv parameters are to be computed internally.
	*/
	bool uv_valid : 1;

	/**
	* True if the xyz coordinates are valid.
	* False if the xyz coordinates are to be computed internally.
	*/
	bool xyz_valid : 1;
};

/**
* This type is a map of edges/coedges with a list of discrete points on each edge/coedge.
* The key type, <tt>ENTITY*</tt>, should always be either an <tt>EDGE*</tt> or a <tt>COEDGE*</tt>.
* It is allowed to have a mixture of edges and coedges in the same map.
* The meaning of the <tt>t</tt> value in <tt>DiscretizationPoint</tt> depends on whether
* the given key in the map is an edge or a coedge: <tt>t</tt> is an edge parameter if
* the key is an edge, it is a coedge parameter if the key is a coedge.
*/
using DiscretizationInfo = std::map<ENTITY*, std::vector<DiscretizationPoint>>;

/**
* The <tt>CSMAcisMesher</tt> class is the Acis interface to the CSM (surface mesher) functionality.
* The CSM functionality itself can be utilized through
* the base class <tt>CATMshCSMGeneric</tt>. The additional functions let the user create a mesh from an Acis list of entities
* (<tt>ENTITY_LIST</tt>), and maintain association information between Acis topological entities (<tt>FACE</tt>, <tt>EDGE</tt>, 
* <tt>VERTEX</tt>) and CSM tags (<tt>CATMshTag</tt>). The input entities must not be deleted while the <tt>CSMAcisMesher</tt>
* object is alive. When the <tt>CSMAcisMesher</tt> object is no longer needed, call <tt>Release</tt>, or use 
* <tt>auto_release_unique_ptr</tt> to decrement the reference counter inside the object.
*/
class DECL_SPA3dpm CSMAcisMesher : public CATMshCSMGeneric
{
public:
	/**
	* Class factory function. The returned pointer must be released through the <tt>Release</tt> function, or 
	* <tt>auto_release_unique_ptr</tt>.
	*/
	static CSMAcisMesher *NewCSMAcisMesher();

	/**
	* Specifies the input list of Acis entities for the mesher. Optional discretization information can 
	* prescribe for the mesher how certain edges/coedges must be discretized.
	*/
	virtual HRESULT SetSupport(const ENTITY_LIST &input_entities, const DiscretizationInfo *discretization_info = nullptr) = 0;

	/**
	* Find the tag corresponding to a FACE*. Returns 0 if face is not found.
	*/
	virtual CATMshTag GetFaceId(FACE *face) const = 0;

	/**
	* Find the tag corresponding to an EDGE*. Returns 0 if edge is not found.
	*/
	virtual CATMshTag GetEdgeId(EDGE *edge) const = 0;

	/**
	* Find the tag corresponding to a VERTEX*. Returns 0 if vertex is not found.
	*/
	virtual CATMshTag GetVertexId(VERTEX *vertex) const = 0;

	/**
	* Find the face corresponding to a CSM face tag. Returns nullptr if face is not found.
	*/
	virtual FACE *GetFace(CATMshTag faceId) const = 0;

	/**
	* Find the edge corresponding to a CSM edge tag. Returns nullptr if edge is not found.
	*/
	virtual EDGE *GetEdge(CATMshTag edgeId) const = 0;

	/**
	* Find the vertex corresponding to a CSM vertex tag. Returns nullptr if vertex is not found.
	*/
	virtual VERTEX *GetVertex(CATMshTag vertexId) const = 0;

protected:
	/**
	* Protected constructor prevents directly creating a <tt>CSMAcisMesher</tt> object.
	*/
	CSMAcisMesher();
	/**
	* Protected destructor prevents directly calling delete on a <tt>CSMAcisMesher</tt> pointer.
	*/
	virtual ~CSMAcisMesher() override;
};

/**
* The <tt>CVMAcisMesher</tt> class is the Acis interface to the CVM (volume mesher) functionality.
* The CVM functionality itself can be utilized through
* the base class <tt>CATMshCVMSpa</tt>.
* <tt>CVMAcisMesher</tt> does not add new functions to the interface. Yet it is useful, because
* it unlocks the CVM base class with the product key that was used to unlock Acis.
* When the <tt>CVMAcisMesher</tt> object is no longer needed, call <tt>Release</tt>, or use 
* <tt>auto_release_unique_ptr</tt> to decrement the reference counter inside the object.
*/
class DECL_SPA3dpm CVMAcisMesher : public CATMshCVMSpa
{
public:
	/**
	* Class factory function. The returned pointer must be released through the <tt>Release</tt> function, or 
	* <tt>auto_release_unique_ptr</tt>.
	*/
	static CVMAcisMesher *NewCVMAcisMesher();

private:
	/**
	* Private constructor prevents directly creating a <tt>CVMAcisMesher</tt> object.
	*/
	CVMAcisMesher();
	/**
	* Private destructor prevents directly calling delete on a <tt>CVMAcisMesher</tt> pointer.
	*/
	virtual ~CVMAcisMesher() override;
};

/**
* The <tt>CellDomainAssociativity</tt> class can be used to find 3D volume mesh elements for an Acis CELL or
* a CELL for a volume mesh element. To create an object, the user must pass a CVM volume mesh and the
* <tt>CSMAcisMesher</tt> object that was originally used to create the first surface mesh from the Acis entities.
* When the <tt>CellDomainAssociativity</tt> object is no longer needed, call <tt>Release</tt>, or use 
* <tt>auto_release_unique_ptr</tt> to decrement the reference counter inside the object.
*/
class DECL_SPA3dpm CellDomainAssociativity : public CATMshBase
{
public:
	/**
	* Class factory function. The returned pointer must be released through the <tt>Release</tt> function, or 
	* <tt>auto_release_unique_ptr</tt>.
	* @param[in] volume_mesh_in : a CVM volume mesh containing the domains
	* @param[in] original_surface_mesher_in : pointer to the <tt>CSMAcisMesher</tt> object that was originally used to create the surface mesh from the Acis entities
	*/
	static CellDomainAssociativity *NewCellDomainAssociativity(CATIMshMesh *volume_mesh_in, CSMAcisMesher *original_surface_mesher_in);

	/**
	* Find the Acis CELL corresponding to a CVM domain index.
	*/
	virtual CELL *GetCell(CATMshDomainIndex domain_index_in) const = 0;

	/**
	* Find the Acis CELL corresponding to a CVM domain tag.
	*/
	virtual CELL *GetCell(CATMshTag domaint_tag_in) const = 0;

	/**
	* Find all the CVM 3D volume elements that are contained within the given Acis CELL.
	* @param[in] cell_in : input Acis CELL
	* @param[out] domain_index_out : index of the CVM domain corresponding to cell_in CELL
	* @param[out] domain_tag_out : tag of the CVM domain corresponding to cell_in CELL
	* @return pointer to the container of 3d elements. Call <tt>Release</tt>, or use <tt>auto_release_unique_ptr</tt> to discard the return object.
	*/
	virtual CATIMshMesh::elementsContainer *NewGetDomainElements(CELL *cell_in, CATMshDomainIndex &domain_index_out, CATMshTag &domain_tag_out) = 0;

protected:
	/**
	* Protected constructor prevents directly creating a <tt>CellDomainAssociativity</tt> object.
	*/
	CellDomainAssociativity();
	/**
	* Protected destructor prevents directly calling delete on a <tt>CellDomainAssociativity</tt> pointer.
	*/
	virtual ~CellDomainAssociativity() override;
};

}

/** @} */
#endif
