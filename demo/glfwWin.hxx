/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#pragma once
#include "stdafx.h"
#include "glfw\include\glfw3.h"

//========================================================================
// Window key press callback function
//========================================================================
void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
//========================================================================
// Window close callback function
//========================================================================
void closeCallback(GLFWwindow* window);
//========================================================================
// Window close callback function
//========================================================================
void closeCallback(GLFWwindow* window);
//========================================================================
// Window focus callback function
//========================================================================
void focusCallback(GLFWwindow* window, int focused);
//========================================================================
// Window resize callback function
//========================================================================
void resizeCallback(GLFWwindow* window, int width, int height);
//========================================================================
// Window cursor position callback function
//========================================================================
void cursorPosCallback(GLFWwindow* window, double x, double y);
//========================================================================
// Window mouse button callback function
//========================================================================
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

struct glfwWinState
{
	// ACIS model bounding sphere
	float radius;
	// UI state - user is rotating, user is scaling, or redraw/refresh is needed
	bool do_rotate;
	bool do_scale;
	bool do_redraw_once;
	bool do_translate;
	// Mouse position and rotation
	double xpos, ypos;
	// rotation angles, used to update the GL_MODELVIEW_MATRIX when the user is rotating
	int rot_x, rot_y, rot_z;
	// translation vector, used to update the GL_MODELVIEW_MATRIX when the user is translating
	int trans_x, trans_y;
	// scale factor, used to update the GL_MODELVIEW_MATRIX when the user is scaling
	GLdouble scaleF;

	glfwWinState() : radius(0.0), do_scale(false), do_rotate(false), do_redraw_once(false),do_translate(false),
					 xpos(0.0), ypos(0.0), rot_x(0), rot_y(0), rot_z(0), trans_x(0), trans_y(0), scaleF(1.0) {};
};
