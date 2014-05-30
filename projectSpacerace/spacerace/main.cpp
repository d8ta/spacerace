#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <GLee.h>
#include <oogl/glutIncludes.h>
#include <oogl/gl_error.h>
#include <oogl/Model.h>
#include <oogl/Texture2D.h>
#include <oogl/GLSLProgram.h>



int windowWidth, windowHeight;


bool leftMouseButtonDown = false;
int mousePosX = 0, mousePosY = 0;
float rotationX = 0, rotationY = 0;

/** global variables **/
float moveX = 0.0f;
float moveY = 0.0f;
float moveZ = 0.0f;

// Universal Rotation!
float rotX = 0.0f;
float rotY = 0.0f;
float rotZ = 0.0f;
float rotAngle = 0.0f;

// Planet rot.
float planetaryRotX = 0;
float planetaryRotY = 0;

// Asteroid movment
float asteroidZ = -5000;

//UFO moovement
float angle = 0;



float reflectionMatrix[] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};


//oogl::GLSLProgram* phongshader;
oogl::Texture2D* skybox;


//void setLights() {
//
//    
//    GLfloat mat_shininess[] = { 100.0 };
//    GLfloat mat_ambient[] = { 1.0, .7, .5, 1.0 };
//    GLfloat light_position[] = { 10.0, 10.0, 5.0, 0.0 };
//    glClearColor (0.0, 0.0, 0.0, 0.0);
//    glShadeModel (GL_SMOOTH);
//    
//    
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//    
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_DEPTH_TEST);
//    
//}
//

void init() {
    
	// enable lighting
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat mat_ambient[] = { 1.0, .7, .5, 1.0 };
    GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    
    
//    phongshader = oogl::GLSLProgram::create("/Users/danielraudschus/Documents/spacerace/projectSpacerace/spacerace/data/shader/textShader.vert", "/Users/danielraudschus/Documents/spacerace/projectSpacerace/spacerace/data/shader/textShader.frag");
    skybox = oogl::Texture2D::load(oogl::Image::load("/Users/danielraudschus/Documents/spacerace/build/bin/Debug/data/textures/comic.jpg"));
    
	// set clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


float ufoAngle = 0.0f;
float ufoSlant = 0.0f;
float engineColorY = 0.2f;
float engineColorX = 0.2f;


/* UFO */
void drawUFO() {
	// Color
	glColor3f(0.4f, 0.4f, 0.4f);
	glRotatef(0.0f, -1.0f, 0.0f, 0.0f);
	
	// Bottom
	glPushMatrix();
	{
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -10.0f);
		gluCylinder(gluNewQuadric(), 10, 20, 5, 100, 10);
	}
	glPopMatrix();
	
	// Top
	glPushMatrix();
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(gluNewQuadric(), 10, 20, 5, 100, 10);
	}
	glPopMatrix();
	
	// Cockpit
	glColor4f(0.2f, 0.2f, 0.2f, 0.2f);
	glutSolidSphere(10.0, 50.0, 100.0);
    
	// Engines
	glColor3f(0.2f, 0.2f, engineColorY);
	glPushMatrix();
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -5.0f, 14.0f);
		glutSolidSphere(3.0, 50.0, 100.0);
	}
	glPopMatrix();
    
	glPushMatrix();
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -5.0f, -14.0f);
		glutSolidSphere(3.0, 50.0, 100.0);
	}
	glPopMatrix();
    
	glPushMatrix();
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(14.0f, -5.0f, 0.0f);
		glutSolidSphere(3.0, 50.0, 100.0);
	}
	glPopMatrix();
    
	glPushMatrix();
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(-14.0f, -5.0f, 0.0f);
		glutSolidSphere(3.0, 50.0, 100.0);
	}
	glPopMatrix();
}


///* Kreis */
//void drawCircle()
//{
//	glBegin(GL_POLYGON);
//	for (int i = 0; i < 20; i++)
//	{
//		angle = i * 3.14159 / 10;
//		glVertex2f(cos(angle), sin(angle));
//	}
//	glEnd();
//};



// red rectangles for the flightpath
void drawFlightpath () {
    
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  0.0 );
    glVertex3f(  0, 100, 0 );
    glVertex3f(  0, 90, 0 );
    glVertex3f( 100, 90, 0 );
    glVertex3f( 100, 100, 0 );
    glEnd();
    
    
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  0.0 );
    glVertex3f(  0, 0, 0 );
    glVertex3f(  0, 10, 0 );
    glVertex3f( 100, 10, 0 );
    glVertex3f( 100, 0, 0 );
    glEnd();
    
    
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  0.0 );
    glVertex3f(  0, 0, 0 );
    glVertex3f(  0, 100, 0 );
    glVertex3f( 10, 100, 0 );
    glVertex3f( 10, 0, 0 );
    glEnd();
    
    glTranslated(90, 0, 0);
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  0.0 );
    glVertex3f(  0, 0, 0 );
    glVertex3f(  0, 100, 0 );
    glVertex3f( 10, 100, 0 );
    glVertex3f( 10, 0, 0 );
    glEnd();
}

void path(int x, int y, int z) {
    glPushMatrix(); {
        glTranslatef(x, y, z);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        drawFlightpath();
    }
    glPopMatrix();
}




void drawUniverse() {
    
    glPushMatrix();
    {
        // Moon
        glTranslatef(-1500, 800, -4050);
        glColor3f(1.0f, 1.0f, 1.0f);
        glutSolidSphere(1000.0, 180, 180);
    }
    glPopMatrix();


    // sun
    glPushMatrix();
    {
    glTranslatef(8000, 1000, -18060);
    glColor3f(1.0f, .7f, 0.0f);
    glutSolidSphere(5000.0, 60, 60);
    }
    glPopMatrix();
    
    // thats no moon
    glPushMatrix();
    {
        glTranslatef(planetaryRotX, planetaryRotY, -10000);
        glColor3f(.2f, .2f, .2f);
        glutSolidSphere(500.0, 60, 60);
        
    }
    glPopMatrix();
    
    
    // Asteroids
    glPushMatrix();
    {
        glTranslatef(50, 50, asteroidZ + 400);
        glColor3f(.2f, .2f, .2f);
        glutSolidSphere(10.0, 33, 15);
        
        glTranslatef(10, 50, asteroidZ -100);
        glColor3f(.2f, .2f, .2f);
        glutSolidSphere(17.0, 33, 15);
        
        glTranslatef(80, 50, asteroidZ + 200);
        glColor3f(.2f, .2f, .2f);
        glutSolidSphere(20.0, 33, 15);
        
        
    }
    glPopMatrix();
    

    
    // draw flightpath
    path(50, -50, 200);
    path(120, -10, -200);
    path(-50, -60, -800);
    path(100, -30, -1600);
    path(150, -20, -2200);
    path(-50, -70, -2800);
    path(195, -80, -3200);
    path(-80, -40, -3800);
    path(155, -50, -4200);
    path(100, -10, -4600);
    path(-150, 5, -5000);
    path(-180, 20, -5400);
}



void fly() {
    moveZ += 4;
}


void drawCube() {
    
//    // Enable/Disable features
//    glPushAttrib(GL_ENABLE_BIT);
//    glEnable(GL_TEXTURE_2D);
//    glDisable(GL_DEPTH_TEST);
//    glDisable(GL_LIGHTING);
//    glDisable(GL_BLEND);
//    
    
    // Render the front quad
    glPushMatrix();
    {
    skybox->bind();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();

        
        
        
    // Render the left quad

        glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
    glEnd();

    
    
    // Render the back quad

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
    glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
    glEnd();

    
    
    // Render the right quad

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
    glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glEnd();

    
    // Render the top quad

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
    glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
    glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();




    // Render the bottom quad
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
    glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
    glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glEnd();
    skybox->unbind();
    }
    glPopMatrix();

}


/* Triebwerke drehen */
void engineRotation(int value) {
	angle += 2.0f;
	if (angle > 360)
	{
		angle -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, engineRotation, 0);
}

/* Triebwerke Licht */
void engineLight(int value)
{
	engineColorY += 0.1f;
	glutPostRedisplay();
	glutTimerFunc(25, engineLight, 0); //request to call again in at least 25ms
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer
	// switch to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    // Cam fokus on Object
    //gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ, moveX, moveY, moveZ, 0.0, 20.0, 0.0);
    
    // add rotation to the mouse
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    

    /* UFO + Vantage Point */
	glTranslatef(0.0f, -10.0f, -50.0f);
	
	glPushMatrix();
	{
		glRotatef(ufoAngle, 0.0f, 0.0f, ufoSlant);
		glTranslatef(0.0f, 0.0f, -20.0f);
		drawUFO();
	}
	glPopMatrix();
    
    
    glPushMatrix();
    {
        glScaled(50000, 50000, 50000);
        drawCube();
    }
    glPopMatrix();
    

    glPushMatrix();
    {
	// rotate the universe and all objects, the ship and cam are fixed
    glRotatef(rotAngle, rotX, rotY, rotZ);
	glTranslatef(moveX, moveY, moveZ);
    fly();
    drawUniverse();
    }
    glPopMatrix();



	LOG_GL_ERRORS();
	glutSwapBuffers(); // draw scene
}


void update(int value) {
    
    
	//increment angle variable and keep it in the range of 0..32s
	planetaryRotX += 2;
    planetaryRotY += 2;
    asteroidZ += 14;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0); //request to call again in at least 25ms
}

void reshape(int w, int h) {
	windowWidth = w;
	windowHeight = h;
    
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, w/(float)h, 1.0, 100000.0);  // near clipping plane 1.0 and far clipping  plane 100000.0
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


/* Tastatur */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
        case 27: //27=esc
            exit(0);
            break;
        case 'w':
            std::cout << "fly up" << std::endl;
            moveZ += 15;
			ufoSlant = 0.0f;
            break;
        case 's':
            std::cout << "fly down" << std::endl;
            moveZ -= 15;
            break;
        case 'a':
            std::cout << "fly left" << std::endl;
            moveX += 15;
			ufoAngle -= 5.0f;
			if(ufoSlant != -1.0f)
			{
				ufoSlant -= 0.2f;
			}
            break;
        case 'd':
            std::cout << "fly right" << std::endl;
            moveX -= 15;
			ufoAngle += 5.0f;
			if (ufoSlant != -1.0f)
			{
				ufoSlant -= 0.2f;
			}
            break;
	}
	glutPostRedisplay();
}


// alte steuerung
//void keyboard(unsigned char key, int x, int y) {
//	switch (key) {
//        case 27: //27=esc
//            exit(0);
//            break;
//        case 'w':
//            std::cout << "strafe down" << std::endl;
//            moveY -= 7;
//            break;
//        case 's':
//            std::cout << "strafe up" << std::endl;
//            moveY += 7;
//            break;
//        case 'a':
//            std::cout << "strafe left" << std::endl;
//            moveX += 7;
//            break;
//        case 'd':
//            std::cout << "strafe right" << std::endl;
//            moveX -= 7;
//            break;
//            
//	}
//	glutPostRedisplay();
//}



//void SpecialKeys(int key, int x, int y)
//{
//    switch (key)
//	{
//		case GLUT_KEY_LEFT:
//            std::cout << "faster" << std::endl;
//            rotY = 1.0f;
//            rotX = 0.0f;
//            rotAngle -= 5.0f;
//            break;
//		case GLUT_KEY_RIGHT:
//            std::cout << "slower" << std::endl;
//            rotY = 1.0f;
//            rotX = 0.0f;
//            rotAngle += 5.0f;
//            break;
//		case GLUT_KEY_UP:
//            std::cout << "faster" << std::endl;
//            moveZ -= 2;
//
//			break;
//		case GLUT_KEY_DOWN:
//            std::cout << "slower" << std::endl;
//            moveZ += 2;
//			break;
//	}
//    glutPostRedisplay();
//}

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
		rotationX -= mousePosY - y;
		rotationY -= mousePosX - x;
        
		mousePosX = x;
		mousePosY = y;
	}
}
/* GLUT Setup */
int setupGLUT(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1400, 1200);
	glutInitWindowPosition(100, 100);
	int windowId = glutCreateWindow("spacerace_building better worlds!");
    
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
    
	glutTimerFunc(25, engineRotation, 0);
	glutTimerFunc(25, engineLight, 0);
    
	return windowId;
}
int main(int argc, char** argv) {
	setupGLUT(argc, argv);
	oogl::dumpGLInfos();
	init();
    
    // for the arrow keys
    //glutSpecialFunc(SpecialKeys);
	
    glutMainLoop();
    
    // have to delete the textres.. dont run automatically
    delete skybox;
    
	return 0;
}
