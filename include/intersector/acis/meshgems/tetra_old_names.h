#ifndef __MESHGEMS_TETRA_OLD_NAMES__
#define __MESHGEMS_TETRA_OLD_NAMES__

#ifndef MESHGEMS_NO_OLD_NAMES
#    define tetmesh_session_new meshgems_tetra_session_new
#    define tetmesh_session_delete meshgems_tetra_session_delete
#    define tetmesh_set_message_callback meshgems_tetra_set_message_callback
#    define tetmesh_set_interrupt_callback meshgems_tetra_set_interrupt_callback
#    define tetmesh_set_surface_mesh meshgems_tetra_set_surface_mesh
#    define tetmesh_set_volume_mesh meshgems_tetra_set_volume_mesh
#    define tetmesh_set_sizemap meshgems_tetra_set_sizemap
#    define tetmesh_set_param meshgems_tetra_set_param
#    define tetmesh_optim_level_t meshgems_tetra_optim_level_t
#    define tetmesh_mesh meshgems_tetra_mesh
#    define tetmesh_mesh_boundary meshgems_tetra_mesh_boundary
#    define tetmesh_insert_volume_vertices meshgems_tetra_insert_volume_vertices
#    define tetmesh_optimise_volume meshgems_tetra_optimise_volume
#    define tetmesh_optimise_volume_overconstrained meshgems_tetra_optimise_volume_overconstrained
#    define tetmesh_optimise_volume_sliver meshgems_tetra_optimise_volume_sliver
#    define tetmesh_get_mesh meshgems_tetra_get_mesh
#    define tetmesh_regain_mesh meshgems_tetra_regain_mesh
#    define tetmesh_get_sizemap meshgems_tetra_get_sizemap
#    define tetmesh_regain_sizemap meshgems_tetra_regain_sizemap
#    define tetmesh_get_subdomain_seed meshgems_tetra_get_subdomain_seed
#    define tetmesh_get_subdomain_count meshgems_tetra_get_subdomain_count
#    define tetmesh_session_t meshgems_tetra_session_t

#    define distene_tetmesh_optim_level_t_ meshgems_tetra_optim_level_t_
#    define distene_tetmesh_optim_level_t meshgems_tetra_optim_level_t
#    define tetmesh_optim_level_t_ meshgems_tetra_optim_level_t_
#    define tetmesh_optim_level_t meshgems_tetra_optim_level_t

#    define DISTENE_TETMESH_NO_OPTIMISATION MESHGEMS_TETRA_NO_OPTIMISATION
#    define DISTENE_TETMESH_LIGHT_OPTIMISATION MESHGEMS_TETRA_LIGHT_OPTIMISATION
#    define DISTENE_TETMESH_MEDIUM_OPTIMISATION MESHGEMS_TETRA_MEDIUM_OPTIMISATION
#    define DISTENE_TETMESH_STANDARD_OPTIMISATION MESHGEMS_TETRA_STANDARD_OPTIMISATION
#    define DISTENE_TETMESH_STRONG_OPTIMISATION MESHGEMS_TETRA_STRONG_OPTIMISATION
#    define DISTENE_TETMESH_HEAVY_OPTIMISATION MESHGEMS_TETRA_HEAVY_OPTIMISATION
#    define DISTENE_TETMESH_EXTREM_OPTIMISATION MESHGEMS_TETRA_EXTREM_OPTIMISATION

#    define TETMESH_NO_OPTIMISATION MESHGEMS_TETRA_NO_OPTIMISATION
#    define TETMESH_LIGHT_OPTIMISATION MESHGEMS_TETRA_LIGHT_OPTIMISATION
#    define TETMESH_MEDIUM_OPTIMISATION MESHGEMS_TETRA_MEDIUM_OPTIMISATION
#    define TETMESH_STANDARD_OPTIMISATION MESHGEMS_TETRA_STANDARD_OPTIMISATION
#    define TETMESH_STRONG_OPTIMISATION MESHGEMS_TETRA_STRONG_OPTIMISATION
#    define TETMESH_HEAVY_OPTIMISATION MESHGEMS_TETRA_HEAVY_OPTIMISATION
#    define TETMESH_EXTREM_OPTIMISATION MESHGEMS_TETRA_EXTREM_OPTIMISATION

#    define TETMESH_VERSION MESHGEMS_VERSION
#    define TETMESH_PATCHRE MESHGEMS_PATCHRE
#    define TETMESH_RELEASE MESHGEMS_RELEASE
#    define TETMESH_VERSION_LONG MESHGEMS_VERSION_LONG

#    define STATUS_TETMESH_ABS_START MESHGEMS_STATUS_TETMESH_ABS_START
#    define STATUS_TETMESH_ABS_END MESHGEMS_STATUS_TETMESH_ABS_END
#    define TETMESH_ERRCODE(x) MESHGEMS_TETMESH_ERRCODE(x)
#    define TETMESH_WARCODE(x) MESHGEMS_TETMESH_WARCODE(x)
#    define STATUS_TETMESH_CANNOT_INSERT_POINTS MESHGEMS_STATUS_TETMESH_CANNOT_INSERT_POINTS
#    define STATUS_TETMESH_COINCIDENT_POINTS MESHGEMS_STATUS_TETMESH_COINCIDENT_POINTS
#    define STATUS_TETMESH_COINCIDENT_POINTS2 MESHGEMS_STATUS_TETMESH_COINCIDENT_POINTS2
#    define STATUS_TETMESH_CANNOT_INSERT_POINT MESHGEMS_STATUS_TETMESH_CANNOT_INSERT_POINT
#    define STATUS_TETMESH_COINCIDENT_POINTS3 MESHGEMS_STATUS_TETMESH_COINCIDENT_POINTS3
#    define STATUS_TETMESH_COINCIDENT_POINTS4 MESHGEMS_STATUS_TETMESH_COINCIDENT_POINTS4
#    define STATUS_TETMESH_BOUNDARY_REGENERATION_FAILURE MESHGEMS_STATUS_TETMESH_BOUNDARY_REGENERATION_FAILURE
#    define STATUS_TETMESH_BOUNDARY_EDGE_REGENERATION_FAILURE MESHGEMS_STATUS_TETMESH_BOUNDARY_EDGE_REGENERATION_FAILURE
#    define STATUS_TETMESH_BOUNDARY_FACE_REGENERATION_FAILURE MESHGEMS_STATUS_TETMESH_BOUNDARY_FACE_REGENERATION_FAILURE
#    define STATUS_TETMESH_BOUNDARY_FACE_REGENERATION_FAILURE2 MESHGEMS_STATUS_TETMESH_BOUNDARY_FACE_REGENERATION_FAILURE2
#    define STATUS_TETMESH_NO_DOMAIN MESHGEMS_STATUS_TETMESH_NO_DOMAIN
#    define STATUS_TETMESH_NO_DOMAIN2 MESHGEMS_STATUS_TETMESH_NO_DOMAIN2
#    define STATUS_TETMESH_NO_DOMAIN3 MESHGEMS_STATUS_TETMESH_NO_DOMAIN3
#    define STATUS_TETMESH_EDGE_WITH_EDGE MESHGEMS_STATUS_TETMESH_EDGE_WITH_EDGE
#    define STATUS_TETMESH_EDGE_WITH_FACE MESHGEMS_STATUS_TETMESH_EDGE_WITH_FACE
#    define STATUS_TETMESH_POINT_WITH_FACE MESHGEMS_STATUS_TETMESH_POINT_WITH_FACE
#    define STATUS_TETMESH_EDGE_WITH_FACE2 MESHGEMS_STATUS_TETMESH_EDGE_WITH_FACE2
#    define STATUS_TETMESH_POINT_WITH_EDGE MESHGEMS_STATUS_TETMESH_POINT_WITH_EDGE
#    define STATUS_TETMESH_NO_DOMAIN4 MESHGEMS_STATUS_TETMESH_NO_DOMAIN4
#    define STATUS_TETMESH_TEDIOUS_REGENERATION MESHGEMS_STATUS_TETMESH_TEDIOUS_REGENERATION
#    define STATUS_TETMESH_SMALL_VOLUME MESHGEMS_STATUS_TETMESH_SMALL_VOLUME
#    define STATUS_TETMESH_NEGATIVE_VOLUME MESHGEMS_STATUS_TETMESH_NEGATIVE_VOLUME
#    define STATUS_TETMESH_NEGATIVE_VOLUME2 MESHGEMS_STATUS_TETMESH_NEGATIVE_VOLUME2
#    define STATUS_TETMESH_SMALL_VOLUME2 MESHGEMS_STATUS_TETMESH_SMALL_VOLUME2
#    define STATUS_TETMESH_BAD_TETRA MESHGEMS_STATUS_TETMESH_BAD_TETRA
#    define STATUS_TETMESH_BAD_TRIANGLE MESHGEMS_STATUS_TETMESH_BAD_TRIANGLE
#    define STATUS_TETMESH_BAD_TRIANGLE2 MESHGEMS_STATUS_TETMESH_BAD_TRIANGLE2

#    define DISTENE_TETMESH_WARCODE MESHGEMS_TETRA_WARCODE
#    define DISTENE_TETMESH_ERRCODE MESHGEMS_TETRA_ERRCODE

#    define distene_tetmesh_session_t_ meshgems_tetra_session_t_
#    define distene_tetmesh_session_t meshgems_tetra_session_t

#    define distene_tetmesh_session_new meshgems_tetra_session_new
#    define distene_tetmesh_session_delete meshgems_tetra_session_delete
#    define distene_tetmesh_set_message_callback meshgems_tetra_set_message_callback
#    define distene_tetmesh_set_interrupt_callback meshgems_tetra_set_interrupt_callback
#    define distene_tetmesh_set_surface_mesh meshgems_tetra_set_surface_mesh
#    define distene_tetmesh_set_volume_mesh meshgems_tetra_set_volume_mesh
#    define distene_tetmesh_set_sizemap meshgems_tetra_set_sizemap
#    define distene_tetmesh_set_param meshgems_tetra_set_param
#    define distene_tetmesh_mesh meshgems_tetra_mesh

#    define distene_tetmesh_mesh_boundary meshgems_tetra_mesh_boundary
#    define distene_tetmesh_insert_volume_vertices meshgems_tetra_insert_volume_vertices
#    define distene_tetmesh_optimise_volume meshgems_tetra_optimise_volume
#    define distene_tetmesh_optimise_volume_overconstrained meshgems_tetra_optimise_volume_overconstrained
#    define distene_tetmesh_optimise_volume_sliver meshgems_tetra_optimise_volume_sliver
#    define distene_tetmesh_get_mesh meshgems_tetra_get_mesh
#    define distene_tetmesh_regain_mesh meshgems_tetra_regain_mesh
#    define distene_tetmesh_get_sizemap meshgems_tetra_get_sizemap
#    define distene_tetmesh_regain_sizemap meshgems_tetra_regain_sizemap
#    define distene_tetmesh_get_subdomain_seed meshgems_tetra_get_subdomain_seed
#    define distene_tetmesh_get_subdomain_count meshgems_tetra_get_subdomain_count

/* status_t RANGE from +-1000000 to +-1999999 reserved for Tetmesh (see status.h) */

#    define DISTENE_STATUS_TETMESH_CANNOT_INSERT_POINTS DISTENE_TETMESH_ERRCODE(2002)
#    define DISTENE_STATUS_TETMESH_COINCIDENT_POINTS DISTENE_TETMESH_ERRCODE(2003)
#    define DISTENE_STATUS_TETMESH_COINCIDENT_POINTS2 DISTENE_TETMESH_ERRCODE(2004)
#    define DISTENE_STATUS_TETMESH_CANNOT_INSERT_POINT DISTENE_TETMESH_ERRCODE(2012)
#    define DISTENE_STATUS_TETMESH_COINCIDENT_POINTS3 DISTENE_TETMESH_ERRCODE(2014)
#    define DISTENE_STATUS_TETMESH_COINCIDENT_POINTS4 DISTENE_TETMESH_ERRCODE(2103)

#    define DISTENE_STATUS_TETMESH_BOUNDARY_REGENERATION_FAILURE DISTENE_TETMESH_ERRCODE(3000)
#    define DISTENE_STATUS_TETMESH_BOUNDARY_EDGE_REGENERATION_FAILURE DISTENE_TETMESH_ERRCODE(3009)
#    define DISTENE_STATUS_TETMESH_BOUNDARY_FACE_REGENERATION_FAILURE DISTENE_TETMESH_ERRCODE(3019)
#    define DISTENE_STATUS_TETMESH_BOUNDARY_FACE_REGENERATION_FAILURE2 DISTENE_TETMESH_ERRCODE(3029)
#    define DISTENE_STATUS_TETMESH_NO_DOMAIN DISTENE_TETMESH_ERRCODE(3100)
#    define DISTENE_STATUS_TETMESH_NO_DOMAIN2 DISTENE_TETMESH_ERRCODE(3101)
#    define DISTENE_STATUS_TETMESH_NO_DOMAIN3 DISTENE_TETMESH_ERRCODE(3102)
#    define DISTENE_STATUS_TETMESH_EDGE_WITH_EDGE DISTENE_TETMESH_ERRCODE(3103)
#    define DISTENE_STATUS_TETMESH_EDGE_WITH_FACE DISTENE_TETMESH_ERRCODE(3104)
#    define DISTENE_STATUS_TETMESH_POINT_WITH_FACE DISTENE_TETMESH_ERRCODE(3105)
#    define DISTENE_STATUS_TETMESH_EDGE_WITH_FACE2 DISTENE_TETMESH_ERRCODE(3106)
#    define DISTENE_STATUS_TETMESH_POINT_WITH_EDGE DISTENE_TETMESH_ERRCODE(3107)
#    define DISTENE_STATUS_TETMESH_NO_DOMAIN4 DISTENE_TETMESH_ERRCODE(3209)
#    define DISTENE_STATUS_TETMESH_TEDIOUS_REGENERATION DISTENE_TETMESH_ERRCODE(3500)

#    define DISTENE_STATUS_TETMESH_SMALL_VOLUME DISTENE_TETMESH_ERRCODE(9000)
#    define DISTENE_STATUS_TETMESH_NEGATIVE_VOLUME DISTENE_TETMESH_ERRCODE(9001)
#    define DISTENE_STATUS_TETMESH_NEGATIVE_VOLUME2 DISTENE_TETMESH_ERRCODE(9002)
#    define DISTENE_STATUS_TETMESH_SMALL_VOLUME2 DISTENE_TETMESH_ERRCODE(9003)
#    define DISTENE_STATUS_TETMESH_BAD_TETRA DISTENE_TETMESH_ERRCODE(9100)
#    define DISTENE_STATUS_TETMESH_BAD_TRIANGLE DISTENE_TETMESH_ERRCODE(9102)
#    define DISTENE_STATUS_TETMESH_BAD_TRIANGLE2 DISTENE_TETMESH_ERRCODE(9112)

#endif /* MESHGEMS_NO_OLD_NAMES */

#endif /* __MESHGEMS_TETRA_OLD_NAMES__ */
