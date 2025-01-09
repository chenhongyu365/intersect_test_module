/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
/**
 * ACIS Compound
 */
#if !defined(RENDER_SCENE_HOLDER_HXX)
#    define RENDER_SCENE_HOLDER_HXX
#    include "acis.hxx"
#    include "dcl_compound.h"
class render_scene;
class entity_handle;
class component_handle;
class component_entity_handle;
/**
 * @file render_scene.hxx
 * \addtogroup ACISCOMPOUND
 * @{
 */
/**
 *<summary> Scene graph holder, contains an specific type of scene graph </summary>
 */

class DECL_COMPOUND render_scene_holder : public ACIS_OBJECT {
    render_scene* _impl;

  public:
    render_scene_holder();

    render_scene_holder(render_scene* impl);

    render_scene_holder(const render_scene_holder& other);

    render_scene_holder& operator=(const render_scene_holder& other);

    virtual ~render_scene_holder();

    void set_impl(render_scene* impl);

    render_scene* get_impl() const;

    bool operator==(const render_scene_holder& rhs);
};
/** @} */
#endif
