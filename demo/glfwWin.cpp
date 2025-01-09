/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include "glfwWin.hxx"
// define the GLFW window callback functions
//========================================================================
// Window key press callback function
//========================================================================
void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
//========================================================================
// Window close callback function
//========================================================================
void closeCallback(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window,GL_TRUE);
}
//========================================================================
// Window focus callback function
//========================================================================
void focusCallback(GLFWwindow* window, int focused)
{
	if (GL_TRUE==focused)
	{
		glfwMakeContextCurrent(window);
	}
	else
	{
		glfwMakeContextCurrent(NULL);
	}
}
//========================================================================
// Window resize callback function
//========================================================================
void resizeCallback(GLFWwindow* window, int width, int height)
{
 	glfwWinState* glState = static_cast<glfwWinState*> (glfwGetWindowUserPointer(window));
	if (glState)
	{
		double radius = glState->radius;
		GLdouble ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio*radius, ratio*radius, -radius, radius, -2*radius, 2*radius);
	    glMatrixMode(GL_MODELVIEW);	
	}
	glState->do_redraw_once = true;
}
//========================================================================
// Window cursor position callback function
//========================================================================
void cursorPosCallback(GLFWwindow* window, double x, double y)
{
 	glfwWinState* glState = static_cast<glfwWinState*> (glfwGetWindowUserPointer(window));
	if (!glState)
	{
		return;
	}
	if (glState->do_rotate)
	{
		glState->rot_y = (int) (y - glState->ypos);
		glState->rot_x = (int) (x - glState->xpos);
	}
	else if (glState->do_scale)
	{
		GLint width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glState->scaleF = 1.0 + 10.0*(glState->ypos - y)/(double)height;
	}
	else if (glState->do_translate)
	{
		glState->trans_y = (int) (glState->ypos - y);
		glState->trans_x = (int) (x - glState->xpos);
	}
	// Remember cursor position
	glState->xpos = x;
	glState->ypos = y;
}
//========================================================================
// Window mouse button callback function
//========================================================================
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
 	glfwWinState* glState = static_cast<glfwWinState*> (glfwGetWindowUserPointer(window));
	if (!glState)
	{
		return;
	}
	if ((button == GLFW_MOUSE_BUTTON_LEFT))
	{
		if (action == GLFW_PRESS)
		{
			glState->do_rotate = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			glState->do_rotate = 0;
		}
	}
	else if ((button == GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (action == GLFW_PRESS)
		{
			glState->do_scale = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			glState->do_scale = 0;
			glState->scaleF = 1.0;
		}
	}
	else if ((button == GLFW_MOUSE_BUTTON_MIDDLE))
	{
		if (action == GLFW_PRESS)
		{
			glState->do_translate = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			glState->do_translate = 0;
		}
	}

}
