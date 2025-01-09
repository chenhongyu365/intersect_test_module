/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include "acis/annotation.hxx"
#include "acis/api.err"
#include "acis/blndanno.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/copyanno.hxx"
#include "acis/cstrapi.hxx"
#include "acis/geom_utl.hxx"
#include "acis/kernapi.hxx"
#include "acis/kernopts.hxx"
#include "acis/lop_api.hxx"
#include "acis/lop_opts.hxx"
#include "acis/loptanno.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis/transf.hxx"

// ACIS-specific Header Files
#include "acis/acis.hxx"
#include "acis/acis_journal.hxx"
#include "acis/add_pcu.hxx"
#include "acis/alltop.hxx"
#include "acis/api.hxx"
#include "acis/blendapi.hxx"
#include "acis/blndanno.hxx"
#include "acis/blndopts.hxx"
#include "acis/boolapi.hxx"
#include "acis/box.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/copyanno.hxx"
#include "acis/coverapi.hxx"
#include "acis/cstrapi.hxx"
#include "acis/efilter.hxx"
#include "acis/geom_utl.hxx"
#include "acis/getbox.hxx"
#include "acis/kernapi.hxx"
#include "acis/kernopts.hxx"
#include "acis/law.hxx"
#include "acis/lists.hxx"
#include "acis/logical.h"
#include "acis/lop_api.hxx"
#include "acis/lop_opts.hxx"
#include "acis/loptanno.hxx"
#include "acis/pcudef.hxx"
#include "acis/pcurve.hxx"
#include "acis/pick_ray.hxx"
#include "acis/point.hxx"
#include "acis/position.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/roll_utl.hxx"
#include "acis/shl_api.hxx"
#include "acis/skin_opts.hxx"
#include "acis/skinapi.hxx"
#include "acis/surdef.hxx"
#include "acis/surf_utl.hxx"
#include "acis/surface.hxx"
#include "acis/trace.hxx"
#include "acis/unitvec.hxx"
#include "acis/vector.hxx"
#include "acis/wire_utl.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//
//
// APIs:
//
// Description: Creates four-sided Prism and pyramid such that
// vertices of Pyramid lie on the edges of the Prism
outcome prism_pyramid1(double Height, double RadiusPyramid, BODY*& part) {
    double H = Height;
    double R = RadiusPyramid;
    double R1 = R * sqrt(2.0);

    API_BEGIN
    BODY* prism = NULL;
    BODY* pyramid = NULL;
    check_outcome(api_make_prism(H, R1, R1, 4, prism));
    check_outcome(api_make_pyramid(H, R, R, R / 2, 4, pyramid));

    // Translate and then delete the second block from the first.
    SPAtransf moveZ(translate_transf(SPAvector(0, 0, -1 * H / 2)));
    check_outcome(api_transform_entity(prism, moveZ));
    moveZ = translate_transf(SPAvector(0, 0, H / 2));
    check_outcome(api_transform_entity(pyramid, moveZ));

    check_outcome(api_unite(pyramid, prism));

    part = prism;

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//
//
// APIs:
//
// Description: Creates four-sided Prism and pyramid such that
// vertices of Pyramid lie on the edges of the Prism
outcome prism_pyramid2(double Height, double RadiusPyramid, BODY*& part) {
    double H = Height;
    double R = RadiusPyramid;
    double R1 = R * sqrt(2.0);

    API_BEGIN
    BODY* prism = NULL;
    BODY* pyramid = NULL;
    check_outcome(api_make_prism(H, R1, R1, 4, prism));
    check_outcome(api_make_pyramid(H, R, R, R / 2, 4, pyramid));

    // Translate and then delete the second block from the first.
    SPAtransf moveZ(translate_transf(SPAvector(0, 0, -1 * H / 2)));
    check_outcome(api_transform_entity(prism, moveZ));

    moveZ = translate_transf(SPAvector(0, 0, H / 2));
    check_outcome(api_transform_entity(pyramid, moveZ));
    SPAtransf rotateZ(rotate_transf(M_PI / 4.0, SPAvector(0, 0, 1)));
    check_outcome(api_transform_entity(pyramid, rotateZ));

    check_outcome(api_unite(pyramid, prism));
    part = prism;

    API_END

    return result;
}

LOCAL_PROC void HandleSplitAnnotations() {
    rgb_color Golden(0.9, 0.9, 0);
    rgb_color SteelBlue(18 / 255.0, 145 / 255.0, 205 / 255.0);
    ENTITY_LIST Annos;
    check_outcome(api_find_annotations(Annos, is_SPLIT_ANNOTATION));
    int Count = Annos.count();
    for(int iCnt = 0; iCnt < Count; iCnt++) {
        ENTITY* obj = NULL;
        obj = ((SPLIT_ANNOTATION*)Annos[iCnt])->get_old_ent();
        ENTITY* img = ((SPLIT_ANNOTATION*)Annos[iCnt])->get_new_ent();
        ENTITY* gap = ((SPLIT_ANNOTATION*)Annos[iCnt])->get_gap_ent();

        // The obj is an EE_LIST or an ATTRIB_TAG which contains the pointer to old-ent
        if(img) check_outcome(api_rh_set_entity_rgb(img, SteelBlue));
        if(gap) {
            if(is_EE_LIST(gap)) {
                ((EE_LIST*)gap)->init();
                while((obj = ((EE_LIST*)gap)->next()) != NULL) check_outcome(api_rh_set_entity_rgb(obj, Golden));
            } else
                check_outcome(api_rh_set_entity_rgb(gap, Golden));
        }
    }
    Annos.clear();

    return;
}
//-----------------------------------------------------------------------------------

LOCAL_PROC void HandleCopyAnnotations() {
    rgb_color Ruby(255 / 255.0, 128 / 255.0, 192 / 255.0);
    ENTITY_LIST Annos;
    check_outcome(api_find_annotations(Annos, is_COPY_ANNOTATION));
    int Count = Annos.count();
    for(int iCnt = 0; iCnt < Count; iCnt++) {
        ENTITY* obj = NULL;
        obj = ((COPY_ANNOTATION*)Annos[iCnt])->source();
        ENTITY* img = ((COPY_ANNOTATION*)Annos[iCnt])->copy();

        if(is_FACE(img)) {
            if(img) check_outcome(api_rh_set_entity_rgb(img, Ruby));
        }
    }
    Annos.clear();

    return;
}
//-----------------------------------------------------------------------------------

LOCAL_PROC void HandleTaperAnnotations() {
    rgb_color WineRed(190 / 255.0, 65 / 255.0, 137 / 255.0);
    ENTITY_LIST Annos;
    check_outcome(api_find_annotations(Annos, is_EDGE_TAPER_ANNO_FACE));
    for(int iCnt = 0; iCnt < Annos.count(); iCnt++) {
        ENTITY* ent = ((EDGE_TAPER_ANNO_FACE*)Annos[iCnt])->split_face();

        if(is_FACE(ent)) {
            if(ent) check_outcome(api_rh_set_entity_rgb(ent, WineRed));
        } else if(is_EE_LIST(ent)) {
            ((EE_LIST*)ent)->init();
            FACE* fc = (FACE*)((EE_LIST*)ent)->next();
            while(fc) {
                check_outcome(api_rh_set_entity_rgb(ent, WineRed));
                fc = (FACE*)((EE_LIST*)ent)->next();
            }
        }
    }
    Annos.clear();

    return;
}
//-----------------------------------------------------------------------------------

LOCAL_PROC void HandleBlendAnnotations() {
    rgb_color Blue(0, 0, 1);
    rgb_color Golden(0.9, 0.9, 0.1);
    ENTITY_LIST Annos;

    // Handling Annotations on Blend Edges
    check_outcome(api_find_annotations(Annos, is_BLEND_ANNO_EDGE));
    for(int iCnt = 0; iCnt < Annos.count(); iCnt++) {
        ENTITY* fc = ((BLEND_ANNO_EDGE*)Annos[iCnt])->blend_face();
        if(fc) check_outcome(api_rh_set_entity_rgb(fc, Blue));
    }
    Annos.clear();

    // Handling Annotations on Blend Vertices
    check_outcome(api_find_annotations(Annos, is_BLEND_ANNO_VERTEX));
    for(int jCnt = 0; jCnt < Annos.count(); jCnt++) {
        ENTITY* fc = ((BLEND_ANNO_EDGE*)Annos[jCnt])->blend_face();
        if(fc) check_outcome(api_rh_set_entity_rgb(fc, Golden));
    }
    Annos.clear();

    return;
}

void TrackAnnotations(logical state) {
    if(state) {
        // Turn the annotations ON
        annotations.push(TRUE);
    } else {
        HandleBlendAnnotations();
        HandleTaperAnnotations();
        HandleSplitAnnotations();
        HandleCopyAnnotations();

        // Pop state for annotations
        annotations.pop();
    }

    return;
}
