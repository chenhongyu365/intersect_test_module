// $Id: blend_smoke_test.hxx,v 1.4 2002/01/28 16:53:03 rocon Exp $
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#include "ACIS_mesh.hxx"

#include <assert.h>

#include <string>

#include "acis/af_api.hxx"
#include "acis/edge.hxx"
#include "acis/face.hxx"
#include "acis/fct_utl.hxx"
#include "acis/get_top.hxx"
#include "acis/getowner.hxx"
#include "acis/kernapi.hxx"
#include "acis/lists.hxx"
#include "acis/rnd_api.hxx"
#include "acis/transf.hxx"
#include "glfwWin.hxx"
#include "stdio.h"

// ACIS forward declarations
void process(outcome& result) {
    if(!result.ok()) {
        std::string err(find_err_mess(result.error_number()));
        std::wstring errW(err.begin(), err.end());
        MessageBox(NULL, errW.c_str(), L"Error!", NULL);
    }
    err_mess_type* warnings = NULL;
    int nwarn = get_warnings(warnings);
    for(int i = 0; i < nwarn; ++i) {
        printf("Warning %d : %s\n", warnings[i], find_err_mess(warnings[i]));
    }
}

static void get_triangles_from_faceted_face(FACE* face, std::vector<float>& coords, std::vector<int>& triangles, std::vector<float>& normalCoords) {
    af_serializable_mesh* sm = GetSerializableMesh(face);
    if(NULL == sm) {
        // Application decision: do we throw for unfaceted faces?
        return;
    }
    SPAtransf tr = get_owner_transf(face);

    const int nv = sm->number_of_vertices();
    int ntri = sm->number_of_polygons();

    coords.resize(3 * nv);
    sm->serialize_positions(coords.data());  // if std::vector::data is not available, &(coords[0]) will also work.
    if(!tr.identity()) {
        for(int ii = 0; ii < nv; ii++) {
            int jj = 3 * ii;
            SPAposition pos(coords[jj], coords[jj + 1], coords[jj + 2]);
            pos *= tr;
            coords[jj] = (float)pos.x();
            coords[jj + 1] = (float)pos.y();
            coords[jj + 2] = (float)pos.z();
        }
    }

    bool const has_normals = sm->has_normals() == TRUE;
    if(has_normals) {
        normalCoords.resize(3 * nv);
        sm->serialize_normals(normalCoords.data());
    }

    triangles.resize(3 * ntri);
    int ntri_actual = sm->serialize_triangles(triangles.data());
    while(ntri_actual < ntri) {
        triangles.pop_back();
        ntri_actual = static_cast<int>(triangles.size());
    }
}

static void get_triangles_from_faceted_faces(ENTITY_LIST& faces, std::vector<AcisMesh::FaceMesh>& faceData, std::vector<float>& coords, std::vector<int>& triangles, std::vector<float>& normalCoords) {
    int nF = 0;
    int nV = 0;
    int nI = 0;
    int numFaces = faces.iteration_count();
    assert(numFaces == faceData.size());
    for(ENTITY* ent = faces.first(); ent; ent = faces.next()) {
        assert(nF < numFaces);
        assert(is_FACE(ent));
        if(!is_FACE(ent)) {
            continue;
        }

        FACE* face = (FACE*)ent;
        std::vector<float> temp_coords;
        std::vector<int> temp_triangles;
        std::vector<float> temp_normalCoords;
        get_triangles_from_faceted_face(face, temp_coords, temp_triangles, temp_normalCoords);
        {
            int nCoordsStart = (int)coords.size() / 3;
            int nCoords = (int)temp_coords.size();
            for(int ii = 0; ii < nCoords; ii++) {
                coords.push_back(temp_coords[ii]);
                normalCoords.push_back(temp_normalCoords[ii]);
            }
            int nTri = (int)temp_triangles.size();
            for(int jj = 0; jj < nTri; jj++) {
                triangles.push_back(temp_triangles[jj] + nCoordsStart);
            }
        }
        logical found = FALSE;
        outcome out = api_rh_get_entity_rgb(ent, faceData[nF].color, TRUE, found);
        if(!out.ok() || !found) {
            faceData[nF].color = rgb_color(1., 1., 1.);
        }
        faceData[nF].numIndices = (unsigned int)temp_triangles.size();
        faceData[nF].baseIndex = (unsigned int)nI;
        faceData[nF].baseVertex = (unsigned int)nV;

        nI += (unsigned int)temp_triangles.size();
        nV += (unsigned int)temp_coords.size();
        nF++;
    }
}

static void get_polylines_from_faceted_edges(ENTITY_LIST& edges, std::vector<AcisMesh::EdgeMesh>& edgeData, std::vector<float>& coords) {
    int nE = 0;
    int nV = 0;
    int numEdges = edges.iteration_count();
    assert(numEdges == edgeData.size());
    for(ENTITY* ent = edges.first(); ent; ent = edges.next()) {
        assert(nE < numEdges);
        assert(is_EDGE(ent));
        if(!is_EDGE(ent)) {
            continue;
        }

        SPAtransf tr = get_owner_transf(ent);
        EDGE* edge = (EDGE*)ent;
        SPAposition* pos = NULL;

        int nP = 0;
        outcome out = api_get_facet_edge_points(edge, pos, nP);
        if(!out.ok()) {
            ACIS_DELETE[] pos;
            continue;
        }
        for(int ii = 0; ii < nP; ii++) {
            pos[ii] *= tr;
            coords.push_back((float)pos[ii].x());
            coords.push_back((float)pos[ii].y());
            coords.push_back((float)pos[ii].z());
        }
        ACIS_DELETE[] pos;
        pos = NULL;
        logical found = FALSE;
        out = api_rh_get_entity_rgb(ent, edgeData[nE].color, TRUE, found);
        if(!out.ok() || !found) {
            edgeData[nE].color = rgb_color(0., 0., 0.);
        }
        edgeData[nE].numIndices = 3 * nP;
        edgeData[nE].baseVertex = nV;
        nV += 3 * nP;
        nE++;
    }
}

bool CreateMeshFromEntityList(ENTITY_LIST& el, AcisMesh::DisplayData& dd) {
    int numEnt = el.iteration_count();
    if(0 == numEnt) {
        return false;
    }
    {
        for(ENTITY* ent = el.first(); ent; ent = el.next()) {
            outcome out = api_facet_entity(ent);
            if(!out.ok()) {
                return false;
            }
        }
    }
    ENTITY_LIST faces;
    {
        for(ENTITY* ent = el.first(); ent; ent = el.next()) {
            if(is_EDGE(ent)) {
                continue;
            }
            outcome out = api_get_faces(ent, faces);
            if(!out.ok()) {
                return false;
            }
        }
    }
    int numFaces = faces.iteration_count();
    dd.faceMesh.resize(numFaces);

    ENTITY_LIST edges;
    {
        for(ENTITY* ent = el.first(); ent; ent = el.next()) {
            outcome out = api_get_edges(ent, edges);
            if(!out.ok()) {
                return false;
            }
        }
    }
    int numEdges = edges.iteration_count();
    dd.edgeMesh.resize(numEdges);

    if(0 == numEdges + numFaces) {
        return false;
    }
    get_triangles_from_faceted_faces(faces, dd.faceMesh, dd.faceCoords, dd.triangles, dd.normalCoords);
    get_polylines_from_faceted_edges(edges, dd.edgeMesh, dd.edgeCoords);

    return true;
}

bool AcisMesh::Display() const {
    if(nullptr == m_data) {
        return false;
    }

    GLFWAPI GLFWwindow* s_pWindow = NULL;
    {
        int width = GetSystemMetrics(SM_CXSCREEN);
        int height = GetSystemMetrics(SM_CYSCREEN);
        s_pWindow = glfwCreateWindow(width, height, "ACIS", NULL, NULL);
        if(!s_pWindow) {
            MessageBox(NULL, L"Could not create an OpenGL window, exiting", L"Fatal Error!", NULL);
            return false;
        }
        glfwSetWindowSize(s_pWindow, 800, 600);
    }

    glfwWinState glState;
    const double radiusFactor = 1.5;

    // Initialize the glfw context
    glfwMakeContextCurrent(s_pWindow);
    // Initialize glfw callbacks
    glfwSetCursorPosCallback(s_pWindow, cursorPosCallback);
    glfwSetMouseButtonCallback(s_pWindow, mouseButtonCallback);
    glfwSetKeyCallback(s_pWindow, keyCallback);
    glfwSetWindowFocusCallback(s_pWindow, focusCallback);
    glfwSetWindowCloseCallback(s_pWindow, closeCallback);
    glfwSetFramebufferSizeCallback(s_pWindow, resizeCallback);

    // compute a bounding sphere
    double radius = 0;
    {
        for(size_t ii = 0; ii < m_data->faceCoords.size(); ii++) {
            if(fabs(m_data->faceCoords[ii]) > radius) {
                radius = fabs(m_data->faceCoords[ii]);
            }
        }
    }
    {
        for(size_t ii = 0; ii < m_data->edgeCoords.size(); ii++) {
            if(fabs(m_data->edgeCoords[ii]) > radius) {
                radius = fabs(m_data->edgeCoords[ii]);
            }
        }
    }
    radius *= radiusFactor;
    glState.radius = (float)radius;

    // Set the window user pointer to the window state.
    glState.do_redraw_once = true;
    glState.do_rotate = false;
    glfwSetWindowUserPointer(s_pWindow, (void*)&glState);
    // Enable scissor test
    // Clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Size the window
    GLint width, height;
    glfwGetFramebufferSize(s_pWindow, &width, &height);
    GLdouble ratio = width / (float)height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio * glState.radius, ratio * glState.radius, -glState.radius, glState.radius, -2 * glState.radius, 2 * glState.radius);
    glMatrixMode(GL_MODELVIEW);
    // For perspective view, use solid rendering
    glPolygonMode(GL_FRONT, GL_FILL);

    // Enable face culling (faster rendering)
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);
    // Configure and enable lighting
    const GLfloat light_position[4] = {0, 0, 20 * glState.radius, 0.0f};
    const GLfloat light_diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat light_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat light_ambient[4] = {0.2f, 0.2f, 0.3f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // Main loop drawing as needed to respond to user events.
    // Terminate when a window close request is received.
    glPushMatrix();
    while(!glfwWindowShouldClose(s_pWindow)) {
        if(glState.do_rotate || glState.do_redraw_once || glState.do_scale || glState.do_translate) {
            glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if(glState.do_rotate) {
                GLdouble model[16];
                glGetDoublev(GL_MODELVIEW_MATRIX, model);
                // Rotate the object about axes corresponding to view left and view up
                glRotated(glState.rot_x * 0.5f, model[1], model[5], model[9]);
                glRotated(glState.rot_y * 0.5f, model[0], model[4], model[8]);
            } else if(glState.do_scale) {
                glScalef((GLfloat)glState.scaleF, (GLfloat)glState.scaleF, (GLfloat)glState.scaleF);
            } else if(glState.do_translate) {
                GLint width, height;
                glfwGetFramebufferSize(s_pWindow, &width, &height);
                GLdouble xScale = glState.trans_x * glState.radius / (GLdouble)width;
                GLdouble yScale = glState.trans_y * glState.radius / (GLdouble)height;
                GLdouble ratio = width / (float)height;
                GLdouble model[16];
                glGetDoublev(GL_MODELVIEW_MATRIX, model);
                // scaleF is how much the model has been scaled interactively
                double scaleF = sqrt(model[1] * model[1] + model[5] * model[5] + model[9] * model[9]);
                // xScale and yScale make the interactive translation roughly simulate the model following the cursor,
                // but we neglect the ratio of width:height
                yScale *= radiusFactor / (scaleF * scaleF);
                xScale *= radiusFactor / (scaleF * scaleF);

                // Translate the object about axes corresponding to view left and view up
                GLdouble trX = yScale * model[1] + xScale * model[0];
                GLdouble trY = yScale * model[5] + xScale * model[4];
                GLdouble trZ = yScale * model[9] + xScale * model[8];
                glTranslated(trX, trY, trZ);
            }

            for(unsigned int jj = 0; jj < m_data->faceMesh.size(); jj++) {
                const GLfloat red = (GLfloat)m_data->faceMesh[jj].color.red();
                const GLfloat green = (GLfloat)m_data->faceMesh[jj].color.green();
                const GLfloat blue = (GLfloat)m_data->faceMesh[jj].color.blue();
                const GLfloat model_diffuse[4] = {red, green, blue, 0.0f};
                const GLfloat model_specular[4] = {red, green, blue, 0.0f};
                const GLfloat model_shininess = 100.0f;
                glMaterialfv(GL_FRONT, GL_DIFFUSE, model_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, model_specular);
                glMaterialf(GL_FRONT, GL_SHININESS, model_shininess);

                glBegin(GL_TRIANGLES);
                unsigned int nT = (unsigned int)(m_data->faceMesh[jj].numIndices / 3);
                for(unsigned int ii = 0; ii < nT; ii++) {
                    int ll = 3 * ii + m_data->faceMesh[jj].baseIndex;
                    int kk = 3 * m_data->triangles[ll];
                    glNormal3f(m_data->normalCoords[kk], m_data->normalCoords[kk + 1], m_data->normalCoords[kk + 2]);
                    glVertex3f(m_data->faceCoords[kk], m_data->faceCoords[kk + 1], m_data->faceCoords[kk + 2]);
                    kk = 3 * m_data->triangles[ll + 1];
                    glNormal3f(m_data->normalCoords[kk], m_data->normalCoords[kk + 1], m_data->normalCoords[kk + 2]);
                    glVertex3f(m_data->faceCoords[kk], m_data->faceCoords[kk + 1], m_data->faceCoords[kk + 2]);
                    kk = 3 * m_data->triangles[ll + 2];
                    glNormal3f(m_data->normalCoords[kk], m_data->normalCoords[kk + 1], m_data->normalCoords[kk + 2]);
                    glVertex3f(m_data->faceCoords[kk], m_data->faceCoords[kk + 1], m_data->faceCoords[kk + 2]);
                }
                glEnd();
            }
            glLineWidth(1);
            glDisable(GL_LIGHTING);
            for(unsigned int nn = 0; nn < m_data->edgeMesh.size(); nn++) {
                const GLfloat red = (GLfloat)m_data->edgeMesh[nn].color.red();
                const GLfloat green = (GLfloat)m_data->edgeMesh[nn].color.green();
                const GLfloat blue = (GLfloat)m_data->edgeMesh[nn].color.blue();
                glColor3f(red, green, blue);
                glBegin(GL_LINE_STRIP);
                unsigned int nI = (unsigned int)(m_data->edgeMesh[nn].numIndices / 3);
                for(unsigned int ii = 0; ii < nI; ii++) {
                    int ll = 3 * ii + m_data->edgeMesh[nn].baseVertex;
                    glVertex3f(m_data->edgeCoords[ll], m_data->edgeCoords[ll + 1], m_data->edgeCoords[ll + 2]);
                }
                glEnd();
            }
            glEnable(GL_LIGHTING);

            glfwSwapBuffers(s_pWindow);
            glState.do_redraw_once = false;
        }
        glfwWaitEvents();
    }
    glPopMatrix();
    glfwDestroyWindow(s_pWindow);
    s_pWindow = NULL;
    return true;
}

AcisMesh::~AcisMesh() {
    if(m_data != nullptr) {
        delete m_data;
        m_data = nullptr;
    }
}
AcisMesh::AcisMesh(DisplayData* dd) {
    m_data = dd;
}

void display_entity_list(ENTITY_LIST& el) {
    if(0 == el.iteration_count()) {
        return;
    }
    AcisMesh::DisplayData* dd = new AcisMesh::DisplayData;
    // Generate the facet data
    // We are generating a temporary display, and do not want to change the model.
    bool createdMesh = false;
    API_NOP_BEGIN
    createdMesh = CreateMeshFromEntityList(el, *dd);
    API_NOP_END
    if(createdMesh) {
        AcisMesh Afm(dd);
        Afm.Display();
    } else {
        delete dd;
    }
    dd = nullptr;
}

void display_one_entity(ENTITY* ent) {
    ENTITY_LIST el;
    el.add(ent);
    display_entity_list(el);
}
