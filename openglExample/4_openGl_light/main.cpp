#include <time.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include "egg.hpp"
#include "light_config.hpp"

thread_local std::mt19937 gen{std::random_device{}()};

template<typename T>
T random(T min, T max) {
    using dist = std::conditional_t<
        std::is_integral<T>::value,
        std::uniform_int_distribution<T>,
        std::uniform_real_distribution<T>
    >;
    return dist{min, max}(gen);
}

typedef float point3[3];

constexpr double pi = 3.14159265358979323846;

static GLfloat target_pos[]= {0.0, 0.0, 0.0};
static GLfloat viewer[]= { 0.0, 1.0, 10.0 };

static GLfloat thetay = 0.0;   
static GLfloat thetax = 0.0;   
static GLfloat pix2anglex;     
static GLfloat pix2angley;     

static GLint status = 0;       
static GLint zoom_status = 0;               

static int x_pos_old=0;       
static int y_pos_old=0;       

static int delta_x = 0;        
static GLfloat delta_zoom = 1.0;        
static int delta_y = 0;        

static GLfloat azimuth = 0.0; 
static GLfloat elevation = 0.0; 


int direction = 1;

int target_render = 0;

void RenderScene(void);

void randomizeLightColors()
{
  pwrgl::light::base_color[pwrgl::light::LIGHT_1][0] = random(0.0, 1.0);
  pwrgl::light::base_color[pwrgl::light::LIGHT_1][1] = random(0.0, 1.0);
  pwrgl::light::base_color[pwrgl::light::LIGHT_1][2] = random(0.0, 1.0);
  pwrgl::light::base_color[pwrgl::light::LIGHT_2][0] = random(0.0, 1.0);
  pwrgl::light::base_color[pwrgl::light::LIGHT_2][1] = random(0.0, 1.0);
  pwrgl::light::base_color[pwrgl::light::LIGHT_2][2] = random(0.0, 1.0);
}

GLfloat calcR(int id)
{
  using namespace pwrgl::light;
    return sqrt((light_position[id][0]) * (light_position[id][0]) +
                (light_position[id][1]) * (light_position[id][1]) +
                (light_position[id][2]) * (light_position[id][2]));
}

GLfloat calc_x(GLfloat a, GLfloat b, GLfloat R)
{
    return R*cos(a)*cos(b);
}

GLfloat calc_y(GLfloat a, GLfloat b, GLfloat R)
{
    return R*sin(b);    
}

GLfloat calc_z(GLfloat a, GLfloat b, GLfloat R)
{
    return R*sin(a)*cos(b);     
}

void Mouse(int btn, int state, int x, int y)
{

    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)       
    {
        x_pos_old=x;        
                             
        y_pos_old=y;
        status = 1;          
    }
    else
        status = 0;
}


void keys(unsigned char key, int x, int y)
{
    switch(key)
    {
     case 'p':
      delta_zoom += 0.1;
      break;
     case 'm':
      delta_zoom -= 0.1;
      break;
     case 'w':
      elevation += 0.1;
      break;
     case 's':
      elevation -= 0.1;
      break;
     case 'a':
      azimuth += 0.1;
      break;
     case 'd':
      azimuth -= 0.1;
      break;
     case 'j':
      target_render = 1;
      break;
     case 'c':
      target_render = 0;
      break;
   }
   glutPostRedisplay(); 
}

void Motion( GLsizei x, GLsizei y )
{
   
    delta_x=x-x_pos_old;     
    delta_y=y-y_pos_old;
    x_pos_old=x;            
    y_pos_old=y;
    glutPostRedisplay();     
}

void Axes(void)
{

    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};
    

    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};
    

    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};
    

    glColor3f(1.0f, 0.0f, 0.0f);  
    glBegin(GL_LINES); 

        glVertex3fv(x_min);
        glVertex3fv(x_max);

    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  
    glBegin(GL_LINES);  

        glVertex3fv(y_min);
        glVertex3fv(y_max);                           

    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);  
    glBegin(GL_LINES); 

        glVertex3fv(z_min);
        glVertex3fv(z_max);

    glEnd();

}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    pwrgl::light::light_position[pwrgl::light::LIGHT_1][0] = calc_x(azimuth, elevation, calcR(pwrgl::light::LIGHT_1));
    pwrgl::light::light_position[pwrgl::light::LIGHT_1][1] = calc_y(azimuth, elevation, calcR(pwrgl::light::LIGHT_1));
    pwrgl::light::light_position[pwrgl::light::LIGHT_1][2] = calc_z(azimuth, elevation, calcR(pwrgl::light::LIGHT_1));
    pwrgl::light::light_position[pwrgl::light::LIGHT_2][0] = -calc_x(azimuth, elevation, calcR(pwrgl::light::LIGHT_2));
    pwrgl::light::light_position[pwrgl::light::LIGHT_2][1] = -calc_y(azimuth, elevation, calcR(pwrgl::light::LIGHT_2));
    pwrgl::light::light_position[pwrgl::light::LIGHT_2][2] = -calc_z(azimuth, elevation, calcR(pwrgl::light::LIGHT_2));
    glLightfv(GL_LIGHT0, GL_POSITION, pwrgl::light::light_position[pwrgl::light::LIGHT_ID::LIGHT_1]);
    glLightfv(GL_LIGHT1, GL_POSITION, pwrgl::light::light_position[pwrgl::light::LIGHT_ID::LIGHT_2]);
    
    randomizeLightColors();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, pwrgl::light::base_color[pwrgl::light::LIGHT_ID::LIGHT_1]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, pwrgl::light::base_color[pwrgl::light::LIGHT_ID::LIGHT_1]);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, pwrgl::light::base_color[pwrgl::light::LIGHT_ID::LIGHT_2]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, pwrgl::light::base_color[pwrgl::light::LIGHT_ID::LIGHT_2]);

    if(abs(elevation) >= 2*pi )
        elevation=0.0;

    gluLookAt(viewer[0],viewer[1],viewer[2], target_pos[0], target_pos[1], target_pos[2], 0.0, 1.0, 0.0);
    Axes();

    if(status == 1)                     
    {
       thetay += delta_y*pix2angley;    
       thetax += delta_x*pix2anglex;    
    }                                  
    
    if( delta_zoom < 1.0)
        delta_zoom = 1.0;

    glRotatef(thetax, 0.0, 1.0, 0.0);  
    glRotatef(thetay, 1.0, 0.0, 0.0);  
    glScalef(delta_zoom, delta_zoom, delta_zoom);

    glColor3f(1.0f, 1.0f, 1.0f);
    if (target_render == 1 )
      pwrgl::egg::renderEgg();
    else
      glutSolidTeapot(3.0);
    glFlush();
    
    glutSwapBuffers();
 }

void MyInit(void)
{
    using namespace pwrgl::light;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Definicja materiału z jakiego zrobiony jest czajnik
    pwrgl::egg::initEgg();

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[LIGHT_ID::LIGHT_1]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[LIGHT_ID::LIGHT_1]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[LIGHT_ID::LIGHT_1]);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess[LIGHT_ID::LIGHT_1]);

/*************************************************************************************/
// Ustawienie parametrów źródła

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient[LIGHT_ID::LIGHT_1]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, base_color[LIGHT_ID::LIGHT_1]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, base_color[LIGHT_ID::LIGHT_1]);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position[LIGHT_ID::LIGHT_1]);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant[LIGHT_ID::LIGHT_1]);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear[LIGHT_ID::LIGHT_1]);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic[LIGHT_ID::LIGHT_1]);


    glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
    glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
    glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
    glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora


    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient[LIGHT_ID::LIGHT_2]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, base_color[LIGHT_ID::LIGHT_2]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, base_color[LIGHT_ID::LIGHT_2]);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position[LIGHT_ID::LIGHT_2]);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant[LIGHT_ID::LIGHT_2]);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear[LIGHT_ID::LIGHT_2]);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic[LIGHT_ID::LIGHT_2]);


    glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
    glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
    glEnable(GL_LIGHT1);     // włączenie źródła o numerze 0
    glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
    pix2anglex = 360.0/(float)horizontal;  
    pix2angley = 360.0/(float)vertical;  

    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    gluPerspective(70, 1.0, 1.0, 30.0);
    
    if(horizontal <= vertical)
        glViewport(0, (vertical-horizontal)/2, horizontal, horizontal);
    else
        glViewport((horizontal-vertical)/2, 0, vertical, vertical);
    
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}
 
int main(int argc, char *argv[])
{          

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    
    glutInitWindowSize(300, 300);

    glutCreateWindow("Rzutowanie perspektywiczne");
                  
    glutDisplayFunc(RenderScene);
    
    glutMouseFunc(Mouse);
       
    glutMotionFunc(Motion);
    
    glutKeyboardFunc(keys);

    glutReshapeFunc(ChangeSize);
    MyInit();
    
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
    
    srand(time(0));
    return 0;

}