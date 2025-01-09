// $Id: blend_smoke_test.hxx,v 1.4 2002/01/28 16:53:03 rocon Exp $
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#pragma once
#include <vector>

#include "acis/rgbcolor.hxx"
#include "glfw/include/glfw3.h"
#include "stdafx.h"

class ENTITY_LIST;

#define NUMBUFF 4
class AcisMesh {
  public:
    struct FaceMesh {
        unsigned int numIndices;
        unsigned int baseVertex;
        unsigned int baseIndex;
        rgb_color color;
        FaceMesh() {
            numIndices = 0;
            baseVertex = 0;
            baseIndex = 0;
            color = 0;
        }
    };
    struct EdgeMesh {
        unsigned int numIndices;
        unsigned int baseVertex;
        rgb_color color;
        EdgeMesh() {
            numIndices = 0;
            baseVertex = 0;
            color = 0;
        }
    };

    struct DisplayData {
        std::vector<float> faceCoords;
        std::vector<int> triangles;
        std::vector<float> normalCoords;
        std::vector<float> edgeCoords;
        std::vector<AcisMesh::FaceMesh> faceMesh;
        std::vector<AcisMesh::EdgeMesh> edgeMesh;
    };
    // Takes ownership of the DisplayData
    AcisMesh(DisplayData* dd);
    ~AcisMesh();

    bool Display() const;

  private:
    int m_level;
    DisplayData* m_data;
};
