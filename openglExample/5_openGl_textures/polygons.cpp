#include <GL/gl.h>
#include <GL/glut.h>

void draw_3colors_triangle(float x, float y, float a){
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex2f(x,y);
		glVertex2f(x+a,y);
		glVertex2f(x,y+a);
	glEnd();
}