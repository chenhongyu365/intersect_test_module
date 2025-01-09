#ifndef __MESHGEMS_TETRA_SHORT_NAMES__
#define __MESHGEMS_TETRA_SHORT_NAMES__

/**
 * Short names. Allow the caller to omit the meshgems_ prefix.
 */

#ifndef MESHGEMS_NO_SHORT_NAMES
#define tetra_check_volume_mesh meshgems_tetra_check_volume_mesh
#define tetra_compute_hautel meshgems_tetra_compute_hautel
#define tetra_compute_mesh meshgems_tetra_compute_mesh
#define tetra_compute_outdie meshgems_tetra_compute_outdie
#define tetra_compute_outqua meshgems_tetra_compute_outqua
#define tetra_compute_outvol meshgems_tetra_compute_outvol
#define tetra_compute_qualfa meshgems_tetra_compute_qualfa
#define tetra_compute_volcon meshgems_tetra_compute_volcon
#define tetra_default_actions meshgems_tetra_default_actions
#define tetra_get_current_session meshgems_tetra_get_current_session
#define tetra_get_edges_length_sizemap meshgems_tetra_get_edges_length_sizemap
#define tetra_get_mesh meshgems_tetra_get_mesh
#define tetra_get_mesh_boite meshgems_tetra_get_mesh_boite
#define tetra_get_mesh_with_outer_box meshgems_tetra_get_mesh_with_outer_box
#define tetra_get_sizemap meshgems_tetra_get_sizemap
#define tetra_get_subdomain_count meshgems_tetra_get_subdomain_count
#define tetra_get_subdomain_seed meshgems_tetra_get_subdomain_seed
#define tetra_get_tetra_from_coordinates meshgems_tetra_get_tetra_from_coordinates
#define tetra_get_version_ident_string meshgems_tetra_get_version_ident_string
#define tetra_get_version_major meshgems_tetra_get_version_major
#define tetra_get_version_minor meshgems_tetra_get_version_minor
#define tetra_get_version_patch meshgems_tetra_get_version_patch
#define tetra_get_version_string meshgems_tetra_get_version_string
#define tetra_init_num_threads meshgems_tetra_init_num_threads
#define tetra_init_threads meshgems_tetra_init_threads
#define tetra_insert_volume_vertices meshgems_tetra_insert_volume_vertices
#define tetra_mesh meshgems_tetra_mesh
#define tetra_mesh_after_boundary_integrity meshgems_tetra_mesh_after_boundary_integrity
#define tetra_mesh_before_boundary_integrity meshgems_tetra_mesh_before_boundary_integrity
#define tetra_mesh_boundary meshgems_tetra_mesh_boundary
#define tetra_newcoderr_str meshgems_tetra_newcoderr_str
#define tetra_optimise_volume meshgems_tetra_optimise_volume
#define tetra_optimise_volume_overconstrained meshgems_tetra_optimise_volume_overconstrained
#define tetra_optimise_volume_regular meshgems_tetra_optimise_volume_regular
#define tetra_optimise_volume_sliver meshgems_tetra_optimise_volume_sliver
#define tetra_regain_mesh meshgems_tetra_regain_mesh
#define tetra_regain_sizemap meshgems_tetra_regain_sizemap
#define tetra_reset_actions meshgems_tetra_reset_actions
#define tetra_session_delete meshgems_tetra_session_delete
#define tetra_session_new meshgems_tetra_session_new
#define tetra_set_actions meshgems_tetra_set_actions
#define tetra_set_interrupt_callback meshgems_tetra_set_interrupt_callback
#define tetra_set_message_callback meshgems_tetra_set_message_callback
#define tetra_set_param meshgems_tetra_set_param
#define tetra_set_sizemap meshgems_tetra_set_sizemap
#define tetra_set_surface_mesh meshgems_tetra_set_surface_mesh
#define tetra_set_volume_mesh meshgems_tetra_set_volume_mesh
#define tetra_unset_actions meshgems_tetra_unset_actions
#define tetra_optim_level_t meshgems_tetra_optim_level_t
#define tetra_session_t meshgems_tetra_session_t
#define tetra_unlock_product meshgems_tetra_unlock_product
#define TETRA_PATCHRE MESHGEMS_TETRA_PATCHRE
#define TETRA_RELEASE MESHGEMS_TETRA_RELEASE
#define STATUS_TETRA_ABS_START MESHGEMS_STATUS_TETRA_ABS_START
#define STATUS_TETRA_ABS_END MESHGEMS_STATUS_TETRA_ABS_END
#define TETRA_ERRCODE(x) MESHGEMS_TETRA_ERRCODE(x)
#define TETRA_WARCODE(x) MESHGEMS_TETRA_WARCODE(x)
#define STATUS_TETRA_CANNOT_INSERT_POINTS MESHGEMS_STATUS_TETRA_CANNOT_INSERT_POINTS
#define STATUS_TETRA_COINCIDENT_POINTS MESHGEMS_STATUS_TETRA_COINCIDENT_POINTS
#define STATUS_TETRA_COINCIDENT_POINTS2 MESHGEMS_STATUS_TETRA_COINCIDENT_POINTS2
#define STATUS_TETRA_CANNOT_INSERT_POINT MESHGEMS_STATUS_TETRA_CANNOT_INSERT_POINT
#define STATUS_TETRA_COINCIDENT_POINTS3 MESHGEMS_STATUS_TETRA_COINCIDENT_POINTS3
#define STATUS_TETRA_COINCIDENT_POINTS4 MESHGEMS_STATUS_TETRA_COINCIDENT_POINTS4
#define STATUS_TETRA_BOUNDARY_REGENERATION_FAILURE MESHGEMS_STATUS_TETRA_BOUNDARY_REGENERATION_FAILURE
#define STATUS_TETRA_BOUNDARY_EDGE_REGENERATION_FAILURE MESHGEMS_STATUS_TETRA_BOUNDARY_EDGE_REGENERATION_FAILURE
#define STATUS_TETRA_BOUNDARY_FACE_REGENERATION_FAILURE MESHGEMS_STATUS_TETRA_BOUNDARY_FACE_REGENERATION_FAILURE
#define STATUS_TETRA_BOUNDARY_FACE_REGENERATION_FAILURE2 MESHGEMS_STATUS_TETRA_BOUNDARY_FACE_REGENERATION_FAILURE2
#define STATUS_TETRA_NO_DOMAIN MESHGEMS_STATUS_TETRA_NO_DOMAIN
#define STATUS_TETRA_NO_DOMAIN2 MESHGEMS_STATUS_TETRA_NO_DOMAIN2
#define STATUS_TETRA_NO_DOMAIN3 MESHGEMS_STATUS_TETRA_NO_DOMAIN3
#define STATUS_TETRA_EDGE_WITH_EDGE MESHGEMS_STATUS_TETRA_EDGE_WITH_EDGE
#define STATUS_TETRA_EDGE_WITH_FACE MESHGEMS_STATUS_TETRA_EDGE_WITH_FACE
#define STATUS_TETRA_POINT_WITH_FACE MESHGEMS_STATUS_TETRA_POINT_WITH_FACE
#define STATUS_TETRA_EDGE_WITH_FACE2 MESHGEMS_STATUS_TETRA_EDGE_WITH_FACE2
#define STATUS_TETRA_POINT_WITH_EDGE MESHGEMS_STATUS_TETRA_POINT_WITH_EDGE
#define STATUS_TETRA_NO_DOMAIN4 MESHGEMS_STATUS_TETRA_NO_DOMAIN4
#define STATUS_TETRA_TEDIOUS_REGENERATION MESHGEMS_STATUS_TETRA_TEDIOUS_REGENERATION
#define STATUS_TETRA_SMALL_VOLUME MESHGEMS_STATUS_TETRA_SMALL_VOLUME
#define STATUS_TETRA_NEGATIVE_VOLUME MESHGEMS_STATUS_TETRA_NEGATIVE_VOLUME
#define STATUS_TETRA_NEGATIVE_VOLUME2 MESHGEMS_STATUS_TETRA_NEGATIVE_VOLUME2
#define STATUS_TETRA_SMALL_VOLUME2 MESHGEMS_STATUS_TETRA_SMALL_VOLUME2
#define STATUS_TETRA_BAD_TETRA MESHGEMS_STATUS_TETRA_BAD_TETRA
#define STATUS_TETRA_BAD_TRIANGLE MESHGEMS_STATUS_TETRA_BAD_TRIANGLE
#define STATUS_TETRA_BAD_TRIANGLE2 MESHGEMS_STATUS_TETRA_BAD_TRIANGLE2
#endif /* MESHGEMS_NO_SHORT_NAMES */
#endif /* __MESHGEMS_TETRA_SHORT_NAMES__ */
