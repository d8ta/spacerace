#include <iostream>
#include <cstdlib>

#include <GLee.h>
#if defined(__APPLE__) || defined(__APPLE_CC__)
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>		// OpenGL header
# include <GL/glu.h>	// OpenGL Utility header
# include <GL/glut.h>	// GLUT header
#endif

#include <oogl/gl_error.h>
#include <oogl/timer.h>

#include <oogl/Model.h>


oogl::Model* complexModel = NULL;

void cleanup();

void init() {
	atexit(cleanup);

}



void cleanup() {
}


/**
 * called when a frame should be rendered
 */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	LOG_GL_ERRORS();
	glutSwapBuffers();
}

/**
 * called when the window was resized
 * @param w new window width in pixel
 * @param h new window height in pixel
 */
void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ((float)w)/h,0.1f, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * called when nothing else needs to be done
 */
void idle() {
	//force a redisplay
	glutPostRedisplay();
}

/**
 * called when the user pressed a key
 * @param key ASCII character code
 * @param x mouse x position in pixel relative to the window, when the key was pressed
 * @param y mouse y position in pixel relative to the window, when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //27=esc
		exit(0);
		break;
	}
	glutPostRedisplay();
}

/**
 * called when the user pressed or released a mouse key
 * @param button which mouse button was pressed, one of GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON and GLUT_RIGHT_BUTTON
 * @param state button pressed (GLUT_DOWN) or released(GLUT_UP)
 * @param x mouse x position in pixel relative to the window, when the mouse button was pressed
 * @param y mouse y position in pixel relative to the window, when the mouse button was pressed
 */
void mouse(int button, int state, int x, int y) {
	glutPostRedisplay();
}

/**
 * called when the mouse moves
 * @param x mouse x position in pixel relative to the window
 * @param y mouse x position in pixel relative to the window
 */
void mouseMotion(int x, int y) {
}


int setupGLUT(int argc, char** argv) {
	glutInit(&argc, argv);
	// glutInitContextVersion(3, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);

	int windowId = glutCreateWindow("spacerace");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);

	return windowId;
}

int main(int argc, char** argv) {
	setupGLUT(argc, argv);

	oogl::dumpGLInfos();

	glutMainLoop();

	return 0;
}
