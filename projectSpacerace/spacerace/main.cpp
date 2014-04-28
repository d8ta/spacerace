#include <iostream>
#include <iomanip>
#include <cstdlib>

#include <GLee.h>
#include <oogl/glutIncludes.h>
#include <oogl/gl_error.h>

#include <oogl/Model.h>


int windowWidth, windowHeight;

bool leftMouseButtonDown = false;
int mousePosX = 0, mousePosY = 0;
float rotationX = 0, rotationY = 0;

/** Globale Translate Variablen **/
float moveX = 0.0f;
float moveY = 0.0f;
float moveZ = 0.0f;

double cameraPositionX = 0.0;
double cameraPositionY = 1.0;
double cameraPositionZ = 0.0;



float angle = 0.0f;
/*----------6.1----------*/
float reflectionMatrix[] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};

/*----------11.1----------*/

void init() {
    /*----------11.2----------*/
    
	glEnable(GL_DEPTH_TEST); // we enable the depth test, to handle occlusions
    
	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
    
	// set clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawCube() {

    //draw player
    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  5, -5, 5 );
    glVertex3f(  5,  5, 5 );
    glVertex3f( -5,  5, 5 );
    glVertex3f( -5, -5, 5 );
    glEnd();
    
    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 5, -5, -5 );
    glVertex3f( 5,  5, -5 );
    glVertex3f( 5,  5,  5 );
    glVertex3f( 5, -5,  5 );
    glEnd();
    
    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -5, -5,  5 );
    glVertex3f( -5,  5,  5 );
    glVertex3f( -5,  5, -5 );
    glVertex3f( -5, -5, -5 );
    glEnd();
    
    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  5,  5,  5 );
    glVertex3f(  5,  5, -5 );
    glVertex3f( -5,  5, -5 );
    glVertex3f( -5,  5,  5 );
    glEnd();
    
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  5, -5, -5 );
    glVertex3f(  5, -5,  5 );
    glVertex3f( -5, -5,  5 );
    glVertex3f( -5, -5, -5 );
    glEnd();
    
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(  0.0,  0.0,  0.0 );
    glVertex3f(  5, 5, -5 );
    glVertex3f(  -5, 5, -5 );
    glVertex3f( -5, -5, -5 );
    glVertex3f( 5, -5, -5 );
    glEnd();
    
    
}

void drawSpheres() {
    
	//draw the sphere
//    glColor3f(1.5f, 1.0f, 0.0f);
//    glutSolidSphere(10.0, 60, 60);
    
glPushMatrix();
    {
    glTranslatef(30, 20, -10);
	glColor3f(0.0f, 1.0f, 1.0f);
	glutSolidSphere(5.0, 60, 60);
    
    glTranslatef(10, 10, 10);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidSphere(5.0, 60, 60);
    }
glPopMatrix();
    }


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer

	// switch to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    //gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ, moveX, moveY, moveZ, 0.0, 20.0, 0.0);
    
	// set vantage point
	glTranslatef(0.0f, 0.0f, -50.0f);
    
    // add rotation
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    

	/** Projektaufrufe **/
    drawSpheres();

    glTranslatef(moveX, moveY, moveZ);
    drawCube();
    
    
	LOG_GL_ERRORS();
	glutSwapBuffers(); // draw scene
}


/**
 * callback function, which can be used for the glutTimerFunc
 * @param value parameter, which can be specified in glutTimerFunc
 */
void update(int value) {
    
    
    /*----------11.4----------*/
	//increment angle variable and keep it in the range of 0..32s
	angle += 2.0f;
	if (angle > 360)
		angle -= 360;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0); //request to call again in at least 25ms
}

void reshape(int w, int h) {
	windowWidth = w;
	windowHeight = h;
    
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, w/(float)h, 1.0, 1000.0);
}

void idle() {
	glutPostRedisplay(); //force a redisplay
}

//utility method to dump a float matrix
void dumpMatrix(float* m, int c, int r) {
	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < c; ++j)
			std::cout << std::fixed << std::setw(4) << std::setprecision(3) << m[i*c+j] << " ";
		std::cout << std::endl;
	}
}


/** Projektfunktion für Movement **/
//void move(){
//    float moveZ = 500;
//    glTranslatef(0.0f, 0.0f, moveZ);
//    //moveZ += 1;
//    glutPostRedisplay();
//}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
        case 27: //27=esc
            exit(0);
            break;
        case 'w':
            std::cout << "Cam forward" << std::endl;
            moveZ += 5;
            break;
        case 's':
            std::cout << "Cam backward" << std::endl;
            moveZ -= 5;
            break;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		leftMouseButtonDown = true;
	else
		leftMouseButtonDown = false;
    
	mousePosX = x;
	mousePosY = y;
}

void mouseMotion(int x, int y) {
	if (leftMouseButtonDown) {
		//add the relative movement of the mouse to the rotation variables
		rotationX += mousePosY - y;
		rotationY += mousePosX - x;
        
		mousePosX = x;
		mousePosY = y;
	}
}

int setupGLUT(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	int windowId = glutCreateWindow("spacerace_building better worlds!");
    
	glutDisplayFunc(display);
	//glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
    
	glutTimerFunc(25, update, 0);  //request to call in at least 25ms
    
	return windowId;
}

int main(int argc, char** argv) {
	setupGLUT(argc, argv);
    
	oogl::dumpGLInfos();
    
	init();
    
	glutMainLoop();
    
	return 0;
}
