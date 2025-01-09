/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include "mt_examples.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/af_api.hxx"
#include "acis/alltop.hxx"
#include "acis/api.err"
#include "acis/boolapi.hxx"
#include "acis/box_opts.hxx"
#include "acis/bulletin.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/intrapi.hxx"
#include "acis/kernapi.hxx"
#include "acis/kernopts.hxx"
#include "acis/model_state.hxx"
#include "acis/process_mt.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis/roll_utl.hxx"
#include "acis/skin_opts.hxx"
#include "acis/skinapi.hxx"
#include "acis/surf_utl.hxx"
#include "acis/sweepapi.hxx"
#include "acis/thmgr.hxx"
#include "acis/vrtx_utl.hxx"
#include "assert.h"

// Get the exact bounding box for the entity given
LOCAL_PROC
void ComputeExactBox(ENTITY* e, SPAposition& low, SPAposition& high) {
    SPAboxing_options bo(nullptr, SPAboxing_exact);
    check_outcome(api_get_entity_box(e, low, high, &bo));
}

namespace mt_egg_slice {
    LOCAL_PROC SPAtransf move_along_z(double distance) {
        SPAvector direction(0.0, 0.0, distance);
        return translate_transf(direction);
    }

    // one of the bodies from smoke tests
    outcome skin_bottle(BODY*& skin_bottle) {
        skin_bottle = NULL;
        API_BEGIN {
            const SPAposition center(0.0, 0.0, 0.0);
            EDGE* circle1_edge[1];
            EDGE* circle2_edge[1];
            check_outcome(result = api_curve_arc(center, 8, 0.0, 2 * M_PI, circle1_edge[0]));
            check_outcome(result = api_curve_arc(center, 2, 0.0, 2 * M_PI, circle2_edge[0]));
            check_outcome(result = api_transform_entity((ENTITY*)circle2_edge[0], move_along_z(20.0)));

            BODY* circle1 = NULL;
            api_make_ewire(1, circle1_edge, circle1);
            BODY* circle2 = NULL;
            api_make_ewire(1, circle2_edge, circle2);

            EDGE* edge_path[1];
            SPAposition path_points[3];
            path_points[0].set_x(0.0);
            path_points[0].set_y(0.0);
            path_points[0].set_z(-10.0);
            path_points[1].set_x(0.0);
            path_points[1].set_y(1.0);
            path_points[1].set_z(25.0);
            path_points[2].set_x(0.0);
            path_points[2].set_y(0.0);
            path_points[2].set_z(25.0);
            check_outcome(result = api_curve_spline(3, path_points, NULL, NULL, edge_path[0]));

            BODY* path = NULL;
            api_make_ewire(1, edge_path, path);

            BODY* wires[2];
            wires[0] = circle1;
            wires[1] = circle2;

            skin_options* opts = ACIS_NEW skin_options();
            result = api_skin_wires(2, wires, path, skin_bottle, opts);

            api_del_entity(path);
            api_del_entity(circle1);
            api_del_entity(circle2);
            ACIS_DELETE opts;
            check_outcome(result);
        }
        API_END
        return result;
    }

    int start_acis() {
        return api_start_modeller(0).ok();
    }

    int stop_acis() {
        return api_stop_modeller().ok();
    }

    struct history_stream_sentry {
        HISTORY_STREAM* local_stream;
        history_stream_sentry(HISTORY_STREAM* stream) {
            api_get_default_history(local_stream);
            api_set_default_history(stream);
        }
        ~history_stream_sentry() { api_set_default_history(local_stream); }
    };

    class EggSlicer : public thread_work_base {
        // needed by all threads
        const BODY* const body;
        const int n_slices;
        const int n_threads;

        modeler_state ms;

        struct thread_local_data {
            int idx;
            HISTORY_STREAM* stream;
            ENTITY_LIST slice_wires;
        };
        std::vector<thread_local_data> local_data_array;

      protected:
        void process(void* arg) {
            ms.activate();

            // get thread local data
            thread_local_data& local_data = *(static_cast<thread_local_data*>(arg));
            ENTITY_LIST& slice_wires = local_data.slice_wires;

            // set/reset default history streams
            history_stream_sentry s(local_data.stream);

            EXCEPTION_BEGIN
            BODY* copy = NULL;
            EXCEPTION_TRY
            // deep down copy body
            check_outcome(api_deep_down_copy_entity(const_cast<BODY*>(body), (ENTITY*&)copy, TRUE));

            // tight body box
            SPAposition min_pt, max_pt;
            SPAboxing_options box_opts(NULL, SPAboxing_tight);
            check_outcome(api_get_entity_box(const_cast<BODY*>(copy), min_pt, max_pt, &box_opts));

            // distance between two planar slices
            const SPAvector diag = SPAvector(max_pt - min_pt);
            const double x_dim = diag.x();
            const double width = x_dim / n_slices;

            // root of plane
            const SPAposition root(min_pt.x(), min_pt.y() + diag.y() / 2.0, min_pt.z() + diag.z() / 2.0);

            // normal of plane
            const SPAunit_vector nrml(1.0, 0.0, 0.0);

            const int nColors = 10;
            rgb_color colors[nColors] = {
              rgb_color(0.0, 0.0, 1.0),  // Blue
              rgb_color(1.0, 0.0, 0.0),  // Red
              rgb_color(0.0, 1.0, 0.0),  // Green
              rgb_color(1.0, 1.0, 0.0),  // Yellow
              rgb_color(1.0, 0.0, 1.0),  // Magenta
              rgb_color(1.0, 0.5, 0.5),  // Pink
              rgb_color(0.5, 0.5, 0.5),  // Gray
              rgb_color(0.5, 0.0, 0.0),  // Brown
              rgb_color(1.0, 0.5, 0.0),  // Orange
              rgb_color(1.0, 1.0, 1.0)   // White
            };
            // do all planar slices
            {
                for(int j = local_data.idx; j < n_slices; j += n_threads) {
                    const double shift = j * width;
                    if(shift > x_dim) {
                        break;
                    }
                    const SPAposition rt(root.x() + shift, root.y(), root.z());

                    BODY* slice_wire = NULL;
                    outcome result = api_planar_slice(copy, rt, nrml, slice_wire);
                    if(result.ok() && slice_wire) {
                        check_outcome(api_rh_set_entity_rgb(slice_wire, colors[local_data.idx % nColors]));
                        slice_wires.add(slice_wire);
                    }
                }
            }
            EXCEPTION_CATCH_TRUE
            check_outcome(api_del_entity(copy));
            EXCEPTION_END
        }

      public:
        EggSlicer(const BODY* _body, const int _n_slices): body(_body), n_slices(_n_slices), n_threads(thread_count()) {}

        outcome slice(ENTITY_LIST& slice_wires) {
            assert(body);

            API_BEGIN {
                // generate tasks
                local_data_array.resize(n_threads);
                {
                    for(int idx = 0; idx < n_threads; ++idx) {
                        local_data_array.at(idx).idx = idx;
                        check_outcome(api_create_history(local_data_array.at(idx).stream));
                    }
                }

                // schedule tasks on threads
                {
                    for(int idx = 0; idx < n_threads; ++idx) {
                        thread_work_base::run(&local_data_array.at(idx));
                    }
                }

                // wait till all threads have completed their tasks
                thread_work_base::sync();

                // merge thread results
                slice_wires.clear();
                {
                    for(int idx = 0; idx < n_threads; ++idx) {
                        const thread_local_data& local_data = local_data_array.at(idx);
                        merge_child_state(local_data.stream);
                        check_outcome(api_delete_history(local_data.stream));
                        slice_wires.add(local_data.slice_wires);
                    }
                }
            }
            API_END

            return result;
        }
    };
};  // namespace mt_egg_slice
// **********************************************************************************
// C++ Example:
//
// Title:
//	  mt_egg_slice
//
// APIs:
//    api_deep_down_copy_entity
//	  api_planar_slice
//
// Description:
//	  Demonstrates the multithreaded planar slice of a body.

outcome aei_MT_EGG_SLICE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    const int n_slices = 100;
    const int n_threads = 10;  // *** number of worker threads ***

    // Entities not deleted
    API_BEGIN {
        BODY* body = NULL;
        check_outcome(mt_egg_slice::skin_bottle(body));

        thread_work_base::initialize(n_threads, mt_egg_slice::start_acis, mt_egg_slice::stop_acis);
        mt_egg_slice::EggSlicer es(body, n_slices);
        outcome out = es.slice(output_ents);
        thread_work_base::terminate();
        check_outcome(out);
        check_outcome(api_del_entity(body));
    }
    API_END
    return result;
}

//**********************************************************************************
// C++ Example:
//
// Title:
//		Multi-threading api
//
// APIs:
//		api_process_mt
//
// Description:
//		Demonstrates the use of a multi-threading API for processing user-defined work packets
//----------------------------------------------------------------------------------
outcome aei_PROCESS_MT(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    const int n_slices = 100;
    const int n_threads = 16;

    // Define a work_packet for calculating planar slices
    // Each work packet is responsible for one slice operation
    struct planar_slice_work_packet : public work_packet {
        BODY* body = nullptr;  // Body to be sliced
        SPAposition plane_pt;
        SPAunit_vector plane_normal;
        BODY* slice_res = nullptr;

        planar_slice_work_packet(BODY* bdy, SPAposition pt, SPAunit_vector normal)  // this is to support the use of emplace_back when populating the work_packet_queue
            : body(bdy), plane_pt(pt), plane_normal(normal) {}

        void process(void) override {
            BODY* bodyCopy = static_cast<BODY*>(create_working_copy(body));

            EXCEPTION_BEGIN
            outcome result;
            EXCEPTION_TRY
            // Perform the planar slice
            result = api_planar_slice(bodyCopy, plane_pt, plane_normal, slice_res);
            check_outcome(result);

            EXCEPTION_CATCH_TRUE
            check_outcome(api_del_entity(bodyCopy));
            EXCEPTION_END
        }
    };

    // Create a list of work_packets
    std::vector<planar_slice_work_packet> wps;
    wps.reserve(n_slices);

    /* API Call Block */
    API_BEGIN
    // Create the input body for performing the slices
    BODY* body = NULL;
    check_outcome(mt_egg_slice::skin_bottle(body));

    // The slice planes are along the body diagonal of the bounding box
    // of the body with the normal along the diagonal direction.
    SPAposition low_pos, high_pos;
    ComputeExactBox(body, low_pos, high_pos);
    SPAunit_vector plane_normal = normalise(high_pos - low_pos);
    double pitch = (high_pos - low_pos).len() / n_slices;  // Distance between
                                                           // consecutive slices

    // Create planes for the slicing
    for(size_t i = 0; i < n_slices; ++i) {
        SPAposition plane_pt = low_pos + i * pitch * plane_normal;
        wps.emplace_back(static_cast<BODY*>(body), plane_pt, plane_normal);
    }

    // Process the work packets
    check_outcome(api_process_mt(wps, n_threads, mt_egg_slice::start_acis, mt_egg_slice::stop_acis));

    if(result.ok()) {
        // Consume the results of the slice operation
        size_t num_failures = 0;
        for(const planar_slice_work_packet& wp: wps) {
            if(wp.status != 0) {
                // Failure in performing this particular slice operation
                num_failures++;
                error_info* e_info = outcome(wp.status).get_error_info();
            } else {
                // Add the slice result to the output entity list
                output_ents.add(wp.slice_res);
            }
        }
    }

    // Delete the input body
    check_outcome(api_del_entity(body));

    API_END

    return result;
}

//**********************************************************************************
// C++ Example:
//
// Title:
//		Multi-threading api
//
// APIs:
//
//
// Description:
//		Demonstrates the use of the 'work_packet_queue' for scheduling and
//			processing user-defined work packets
//----------------------------------------------------------------------------------
mutex_resource mutex_for_parallel_facetting;
outcome aei_MT_WORK_PACKET_QUEUE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    const int n_threads = 16;

    // Define a work packet to facet a face
    struct facet_face_work_packet : public work_packet {
        FACE* input_face = nullptr;

        facet_face_work_packet(FACE* fc)  // this is to support the use of emplace_back when populating the work_packet_queue
            : input_face(fc) {}

        void process(void) override {
            ENTITY* copy_face = create_working_copy(input_face);
            api_facet_entity(copy_face);
            ATTRIB* att = copy_face->attrib();
            {
                CRITICAL_BLOCK(mutex_for_parallel_facetting);
                att->move(input_face);
            }
            api_del_entity(copy_face);
        }
    };

    // Define a work_packet for calculating EDGE boxes
    struct edge_box_work_packet : public work_packet {
        EDGE* ed = nullptr;
        SPAposition low;
        SPAposition high;

        edge_box_work_packet(EDGE* edge)  // this is to support the use of emplace_back when populating the work_packet_queue
            : ed(edge) {}

        void process(void) override {
            ENTITY* edCopy = create_working_copy(ed);
            ComputeExactBox(edCopy, low, high);
            check_outcome(api_del_entity(edCopy));
        }
    };

    // Create a list of work_packets for computing edge boxes and faceting faces
    std::vector<edge_box_work_packet> edgebox_wps;
    std::vector<facet_face_work_packet> facet_wps;

    /* API Call Block */
    API_BEGIN

    // Create the input body for the operations
    BODY* body = NULL;
    check_outcome(mt_egg_slice::skin_bottle(body));

    // Get the edges & faces in the body
    ENTITY_LIST edge_list, face_list;
    api_get_edges(body, edge_list);
    api_get_faces(body, face_list);

    edgebox_wps.reserve(edge_list.iteration_count());
    facet_wps.reserve(face_list.iteration_count());
    size_t num_work_packets = edgebox_wps.capacity() + facet_wps.capacity();

    // Worker queue to process the different types of work packets
    work_packet_queue wpq(num_work_packets, n_threads, mt_egg_slice::start_acis, mt_egg_slice::stop_acis);

    // Create work packets to compute the edge boxes & add to the queue
    edge_list.init();
    while(ENTITY* ed = edge_list.next()) {
        edgebox_wps.emplace_back(static_cast<EDGE*>(ed));
        wpq.add_and_process_work_packet(&edgebox_wps.back());
    }

    // Create work packets to facet faces & add to the queue
    face_list.init();
    while(ENTITY* fc = face_list.next()) {
        facet_wps.emplace_back(static_cast<FACE*>(fc));
        wpq.add_and_process_work_packet(&facet_wps.back());
    }
    // Wait for the queue to be completely processed
    wpq.wait_for_work_to_complete();

    if(result.ok()) {
        // Consume the results of the slice operation
        size_t num_failures = 0;
        for(const facet_face_work_packet& wp: facet_wps) {
            if(wp.status != 0) {
                // Failure in performing this particular slice operation
                num_failures++;
                error_info* e_info = outcome(wp.status).get_error_info();
            } else {
                // Add the faceted face to the output list
                BODY* bdy = nullptr;
                check_outcome(api_unhook_face(wp.input_face, bdy));
                output_ents.add(bdy);
            }
        }
    }

    // Delete the input body
    check_outcome(api_del_entity(body));

    API_END

    return result;
}
