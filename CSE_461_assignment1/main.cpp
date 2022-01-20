#include <iostream>
#include <stdlib.h>

#ifdef __HOUSE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sstream>
using namespace std;

#define GLUT_KEY_ESCAPE 27
class Vector3f
{
public:
    float x, y, z;

    Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f operator+(Vector3f const &v)
    {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }

    Vector3f operator-(Vector3f &v)
    {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }

    Vector3f operator*(float n)
    {
        return Vector3f(x * n, y * n, z * n);
    }

    Vector3f operator/(float n)
    {
        return Vector3f(x / n, y / n, z / n);
    }

    Vector3f unit()
    {
        return *this / sqrt(x * x + y * y + z * z);
    }

    Vector3f cross(Vector3f v)
    {
        return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};

class house
{
public:
    Vector3f eye, center, up;

    house(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f)
    {
        eye = Vector3f(eyeX, eyeY, eyeZ);
        center = Vector3f(centerX, centerY, centerZ);
        up = Vector3f(upX, upY, upZ);
        Vector3f view = (center - eye).unit();
        eye = eye + view * -0.7;
        center = center + view * -0.7;
    }

    void moveX(float d)
    {
        Vector3f right = up.cross(center - eye).unit();
        eye = eye + right * d;
        center = center + right * d;
    }

    void moveY(float d)
    {
        eye = eye + up.unit() * d;
        center = center + up.unit() * d;
    }

    void moveZ(float d)
    {
        Vector3f view = (center - eye).unit();
        eye = eye + view * d;
        center = center + view * d;
    }

    void look()
    {
        gluLookAt(
                eye.x, eye.y, eye.z,
                center.x, center.y, center.z,
                up.x, up.y, up.z);
    }
};

house house;

void setFrontView()
{
    house.up.x = -0.00171101;
    house.up.y = 0.995962;
    house.up.z = -0.0897583;

    house.center.x = 0.0095462;
    house.center.y = 0.491564;
    house.center.z = 1.5339;

    house.eye.x = 0.0304264;
    house.eye.y = 0.590316;
    house.eye.z = 2.62926;
}
float _angleX = 180.0f;
float _angleY = 0.0f;
float _angleZ = 0.0f;
float _houseAngle = 180.0f;
float _scaleValue = 1.0f;
void onKeyPress(unsigned char key, int x, int y)
{
    float d = 0.01 * 10;

    switch (key)
    {
    case 'w':
        house.moveY(-d);
        break;
    case 's':
        house.moveY(d);
        break;
    case 'a':
        house.moveX(-d);
        break;
    case 'd':
        house.moveX(d);
        break;
    case 'q':
        _scaleValue += 0.1f;
        house.moveX(d/2);
       // house.moveY(d);
        break;
    case 'e':
        if(_scaleValue > 1.0f){

        	_scaleValue -= 0.1f;
        	house.moveX(-d/2);
        	//house.moveY(-d);
        }
        break;
    case 'u':
    	_angleY += -1.0f;
	    if (_angleY > 360) {
	        _angleY -= 360;
	    }
        break;
    case 'j':
        _angleY += 1.0f;
	    if (_angleY > 360) {
	        _angleY -= 360;
	    }
        break;
    case 'n':
    	_angleZ += -1.0f;
	    if (_angleZ > 360) {
	        _angleZ -= 360;
	    }
        break;
    case 'm':
        _angleZ += 1.0f;
	    if (_angleZ > 360) {
	        _angleZ -= 360;
	    }
        break;
    case 'h':
       	_angleX += 1.0f;
	    if (_angleX > 360) {
	        _angleX -= 360;
	    }
        break;
    case 'k':
        _angleX += -1.0f;
	    if (_angleX > 360) {
	        _angleX -= 360;
	    }
        break;
    case 'f':
        _angleX = 180.0f;
        _angleY = 0.0f;
        _angleZ = 0.0f;
        _houseAngle = 180.0f;
        _scaleValue = 1.0f;
        setFrontView();
        break;
    case GLUT_KEY_ESCAPE:
        exit(EXIT_SUCCESS);
    }

    glutPostRedisplay();
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);
}
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double) w / (double) h, 1.0, 200.0);
    setFrontView();
}


void setuphouse()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1000 / 799, 1, 200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    house.look();
}
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setuphouse();
    glRotatef(_houseAngle, 0.0f, 0.f, 0.0f);
    glTranslatef(-1.0f, -1.5f, -2.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5f, 1.0f, 0.0f);
    glRotatef(_angleX, 0.0, 1.0f, 0.0f);
    glRotatef(_angleY, 1.0, 0.0f, 0.0f);
    glRotatef(_angleZ, 0.0, 0.0f, 1.0f);
    glScalef(_scaleValue,_scaleValue,_scaleValue);
    glColor3f(1.0, 0.25, 1.0);
    glColor3f (.5, 0.5, .25);

    /* main rec */
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (.5, .75, .35);
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.1, 0.0);
    glVertex3f (0.9, 0.1, 0.0);
    glVertex3f (0.9, 0.575, 0.0);
    glVertex3f (0.2, 0.575, 0.0);
    glEnd();

    /*back rec*/
    glColor3f (.5, .75, .35);
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.1, 0.5);
    glVertex3f (0.9, 0.1, 0.5);
    glVertex3f (0.9, 0.575, 0.5);
    glVertex3f (0.2, 0.575, 0.5);
    glEnd();

    /* left rec */
    glColor3f (.75, 0.75, .25);
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.1, 0.5);
    glVertex3f (0.2, 0.1, 0.0);
    glVertex3f (0.2, 0.575, 0.0);
    glVertex3f (0.2, 0.575, 0.5);
    glEnd();

    /* right rec */
    glColor3f (.75, 0.75, .25);
    glBegin(GL_POLYGON);
    glVertex3f (0.9, 0.1, 0.5);
    glVertex3f (0.9, 0.1, 0.0);
    glVertex3f (0.9, 0.575, 0.0);
    glVertex3f (0.9, 0.575, 0.5);
    glEnd();

    /* left tri */
    glColor3f (.5, 0.5, .25);
    glBegin(GL_TRIANGLES);
    glVertex3f (0.9, 0.575, 0.0);
    glVertex3f (0.9, 0.575, 0.5);
    glVertex3f (0.9, 0.8, 0.25);
    glEnd();

    /* right tri */
    glColor3f (.5, 0.5, .25);
    glBegin(GL_TRIANGLES);
    glVertex3f (0.2, 0.575, 0.0);
    glVertex3f (0.2, 0.575, 0.5);
    glVertex3f (0.2, 0.8, 0.25);
    glEnd();

    /* roof */
    glColor3f (.55, 0.35, .2);
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.575, 0.0);
    glVertex3f (0.9, 0.575, 0.0);
    glVertex3f (0.9, 0.8, 0.25);
    glVertex3f (0.2, 0.8, 0.25);
    glEnd();

    /*back roof */
    glColor3f (.55, 0.35, .2);
    glBegin(GL_POLYGON);
    glVertex3f (0.2, 0.575, 0.5);
    glVertex3f (0.9, 0.575, 0.5);
    glVertex3f (0.9, 0.8, 0.25);
    glVertex3f (0.2, 0.8, 0.25);
    glEnd();

    /* door */
    glColor3f (.15, 0.2, .3);
    glBegin(GL_POLYGON);
    glVertex3f (0.47, 0.105, -0.000001);
    glVertex3f (0.65, 0.105, -0.000001);
    glVertex3f (0.65, 0.46, -0.000001);
    glVertex3f (0.47, 0.46, -0.000001);
    glEnd();

    /* window 1 */
    glColor3f (.3, 0.2, .1);
    glBegin(GL_POLYGON);
    glVertex3f (0.72, 0.25, -0.000001);
    glVertex3f (0.83, 0.25,-0.000001);
    glVertex3f (0.83, 0.4, -0.000001);
    glVertex3f (0.72, 0.4, -0.000001);
    glEnd();

    /* window 2 */
    glColor3f (.3, 0.2, .1);
    glBegin(GL_POLYGON);
    glVertex3f (0.27, 0.25, -0.000001);
    glVertex3f (0.38, 0.25, -0.000001);
    glVertex3f (0.38, 0.4, -0.000001);
    glVertex3f (0.27, 0.4, -0.000001);
    glEnd();

        /*flue*/
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f (0.7, 0.8, 0.1);
    glVertex3f (0.75, 0.8, 0.1);
    glVertex3f (0.75, 0.625, 0.1);
    glVertex3f (0.7, 0.625, 0.1);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f (0.7, 0.8, 0.15);
    glVertex3f (0.75, 0.8, 0.15);
    glVertex3f (0.75, 0.625, 0.15);
    glVertex3f (0.7, 0.625, 0.15);
    glEnd();

        glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f (0.7, 0.8, 0.1);
    glVertex3f (0.7, 0.8, 0.15);
    glVertex3f (0.7, 0.625, 0.15);
    glVertex3f (0.7, 0.625, 0.1);
    glEnd();

            glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f (0.75, 0.8, 0.1);
    glVertex3f (0.75, 0.8, 0.15);
    glVertex3f (0.75, 0.625, 0.15);
    glVertex3f (0.75, 0.625, 0.1);
    glEnd();
    glEnd();
    glFlush ();
    glPopMatrix();
    glutSwapBuffers();
}
void update(int value) {
    glutPostRedisplay();
        glutKeyboardFunc(onKeyPress);
    glutTimerFunc(25, update, 0);
}
int main(int argc, char * * argv) {
    glutInit( & argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800-0.000001);
    glutCreateWindow("3D House Screen");
    initRendering();
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(onKeyPress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}