#ifndef __MESHGEMS_PATCHSURF_SHORT_NAMES__
#define __MESHGEMS_PATCHSURF_SHORT_NAMES__

// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */
/**
 * Short names. Allow the caller to omit the meshgems_ prefix.
 */

#ifndef MESHGEMS_NO_SHORT_NAMES

#define patchsurf_boundary_edge_is_internal meshgems_patchsurf_boundary_edge_is_internal
#define patchsurf_calloc_generic_buffer meshgems_patchsurf_calloc_generic_buffer
#define patchsurf_compute_mesh meshgems_patchsurf_compute_mesh
#define patchsurf_free_generic_buffer meshgems_patchsurf_free_generic_buffer
#define patchsurf_get_mesh meshgems_patchsurf_get_mesh
#define patchsurf_get_param meshgems_patchsurf_get_param
#define patchsurf_regain_mesh meshgems_patchsurf_regain_mesh
#define patchsurf_session_delete meshgems_patchsurf_session_delete
#define patchsurf_session_new meshgems_patchsurf_session_new
#define patchsurf_set_boundary_mesh meshgems_patchsurf_set_boundary_mesh
#define patchsurf_set_interrupt_callback meshgems_patchsurf_set_interrupt_callback
#define patchsurf_set_message_callback meshgems_patchsurf_set_message_callback
#define patchsurf_set_param meshgems_patchsurf_set_param
#define patchsurf_set_parameterisation meshgems_patchsurf_set_parameterisation
#define patchsurf_session_t meshgems_patchsurf_session_t
#define PATCHSURF_ERROR(x_) MESHGEMS_CADSURF_ERROR(x_)
#define PATCHSURF_WARNING(x_) MESHGEMS_CADSURF_WARNING(x_)
#endif /* MESHGEMS_NO_SHORT_NAMES */
#endif /* __MESHGEMS_CADSURF_SHORT_NAMES__ */
