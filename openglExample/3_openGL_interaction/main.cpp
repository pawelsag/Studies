#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

typedef float point3[3];
constexpr double pi = 3.14159265358979323846;

static GLfloat viewer[]= { 0.0, 1.0, 10.0 };
static GLfloat target_pos[]= { 0.0, 0.0, 0.0 };

static GLfloat thetay = 0.0;   
static GLfloat thetax = 0.0;   
static GLfloat pix2anglex;     
static GLfloat pix2angley;     
static GLfloat last_diff=0.0;     
static GLfloat last_view_y=0.0;     
static GLfloat cam_zoom=0.0;     

static GLint status = 0;       
static GLint zoom_status = 0;                                                            

static int x_pos_old=0;       
static int y_pos_old=0;       

static int delta_x = 0;        
static GLfloat delta_zoom = 1.0;        
static int delta_y = 0;        
                                      
static int round_i=0;
static GLfloat R;
static GLfloat azimuth = 0.0; 
static GLfloat elevation = 0.0; 

int direction = 1;

void RenderScene(void);

GLfloat calcR()
{
    return sqrt( (viewer[0]- target_pos[0]) * (viewer[0]- target_pos[0]) + (viewer[1]- target_pos[1])*(viewer[1]- target_pos[1]) + (viewer[2]- target_pos[2])*(viewer[2]- target_pos[2]));
}

GLfloat calc_x(GLfloat a, GLfloat b)
{
    return (R+cam_zoom)*cos(a)*cos(b);
}

GLfloat calc_y(GLfloat a, GLfloat b)
{
    return (R+cam_zoom)*sin(b);    
}

GLfloat calc_z(GLfloat a, GLfloat b)
{
    return (R+cam_zoom)*sin(a)*cos(b);     
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
    if(key == 'p') delta_zoom += 0.1;
    if(key == 'm') delta_zoom -= 0.1;
    if(key == 'w') elevation += 0.1;
    if(key == 's') elevation -= 0.1;
    if(key == 'a') azimuth += 0.1;
    if(key == 'd') azimuth -= 0.1;
    if(key == 'b') cam_zoom += 0.1;
    if(key == 'n') cam_zoom -= 0.1;

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
    if(cam_zoom >=5.0)
        cam_zoom = 5.0;
    else if(cam_zoom <=-5.0)
        cam_zoom = -5.0;

    viewer[0] = calc_x(azimuth,elevation);
    viewer[1] = calc_y(azimuth,elevation);
    viewer[2] = calc_z(azimuth,elevation);

    if(abs(elevation) > pi/2 && abs(elevation) < pi*1.5)
    {
        direction =-1;
    }else
        direction =1;

    if(abs(elevation) >= 2*pi )
        elevation=0.0;

    gluLookAt(viewer[0],viewer[1],viewer[2], target_pos[0], target_pos[1], target_pos[2], 0.0, direction, 0.0);
    
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
    
    glutWireTeapot(3.0);
    
    glFlush();
    
    glutSwapBuffers();

 }

void MyInit(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

    R=calcR();
    
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