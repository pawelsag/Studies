#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>
#include <random>
#include <time.h>
#include <math.h>
void draw_square(float, float, float);
void random_color_draw_square(float x, float y, float a);
void draw_2colors_triangle(float x, float y, float a);
void draw_3colors_triangle(float x, float y, float a);
void sierpinski_carper(float x, float y, float a);

constexpr float init_color[] = {1.0, 1.0, 0.0};
constexpr float white[] = {1.0, 1.0, 1.0};
constexpr float black[] = {0, 0, 0};


void render_scence(){
	glClear(GL_COLOR_BUFFER_BIT);

	random_color_draw_square(0, 0, 0.8f);
	draw_2colors_triangle(-1.0f, -1.0f, 0.5);
	draw_3colors_triangle(-0.5f, -0.5f, 0.5);
	
	sierpinski_carper(-1, 0.0, 0.5);
	
	glFlush();
}

void my_init(){
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void set_random_color(){
	glColor3f(rand()*1.0f/ RAND_MAX, rand()*1.0f/ RAND_MAX, rand()*1.0f/ RAND_MAX);
}

void draw_square(float x, float y, float a, const float*colors){

	glColor3f(colors[0], colors[1], colors[2]);
	glBegin(GL_TRIANGLES);
		glVertex2f(x,y);
		glVertex2f(x+a,y);
		glVertex2f(x,y+a);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2f(x+a,y);
		glVertex2f(x,y+a);
		glVertex2f(x+a,y+a);
	glEnd();
}

void random_color_draw_square(float x, float y, float a){

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		set_random_color();
		glVertex2f(x,y);
		set_random_color();
		glVertex2f(x+a,y);
		set_random_color();
		glVertex2f(x,y+a);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2f(x+a,y);
		glVertex2f(x,y+a);
		set_random_color();
		glVertex2f(x+a,y+a);
	glEnd();
}

void draw_2colors_triangle(float x, float y, float a){
	
	glBegin(GL_TRIANGLES);
	    glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x,y);
	    glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(x+a,y);
		glVertex2f(x,y+a);
	glEnd();
}

void draw_3colors_triangle(float x, float y, float a){
	set_random_color();
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	    glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x,y);
	    glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(x+a,y);
	    glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(x,y+a);
	glEnd();
}
 
void sierpinski_carper(float x, float y, float a){
	draw_square(x, y, a, init_color);
	
	a /= 3;
	draw_square(x + a, y + a, a, white);

	for(int frac =0 ; frac < 3; frac++){
		float a_copy = a;
		a /= 3;
		for(int j =0 ; j < pow(3, frac+1); j++){
	      for(int i =0 ; i < pow(3, frac+1); i++)
	      	draw_square(x + a +i*a_copy, y+ a +j*a_copy, a, black);
		}
	}

}


int main(int argc, char *argv[])
{

srand(time(0));
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
glutCreateWindow("Fraktale LAB 1");
glutDisplayFunc(render_scence);

my_init();

glutMainLoop();

return 0;

}