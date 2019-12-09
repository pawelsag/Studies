#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <random>
#include <time.h>

typedef float point3[3];

constexpr double PI = 3.14159265;

constexpr int N = 50;

int model = 1;  
static GLfloat theta[] = {0.0, 0.0, 0.0}; 

void RenderScene(void);
void MyInit(void);
void keys(unsigned char key, int x, int y)
{
    if(key == 'p') model = 1;
    if(key == 'w') model = 2;
    if(key == 's') model = 3;
   
    RenderScene(); 
}


point3 space[N][N];
point3 colors[N][N]; 
double points[N];

void generate_point(){
    for(int i =0 ; i < N; i++){
        points[i] = float(i) / (N-1);
    }
}

void generate_colors(){
    for(int i =0 ; i < N; i++){
        for(int j =0 ; j < N; j++){
            colors[i][j][0] = rand()%256 /255.0; 
            colors[i][j][1] = rand()%256 /255.0;
            colors[i][j][2] = rand()%256 /255.0;
        }
    }
}

void spinEgg()
{

    theta[0] -= 0.5;
    if( theta[0] > 360.0 ) theta[0] -= 360.0;

    theta[1] -= 0.5;
    if( theta[1] > 360.0 ) theta[1] -= 360.0;

    theta[2] -= 0.5;
    if( theta[2] > 360.0 ) theta[2] -= 360.0;

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
constexpr double calc_x(double u, double v)
{
    return  (-90*pow(u,5) + 225*pow(u,4) - 270*pow(u,3) + 180*pow(u,2) - 45*u) * cos(PI * v);
}

constexpr double calc_y(double u, double v)
{
    return  160*pow(u,4) - 320*pow(u,3) + 160*pow(u,2) -5.0;
}

constexpr double calc_z(double u, double v)
{
    return  (-90*pow(u,5) + 225*pow(u,4) - 270*pow(u,3) + 180*pow(u,2) - 45*u) * sin(PI * v);
}


void drawEgg()
{

    for(int u=0; u < N ; u++){
        for(int v=0; v < N ; v++){
            space[u][v][0] = calc_x(points[u], points[v]);
            space[u][v][1] = calc_y(points[u], points[v]);
            space[u][v][2] = calc_z(points[u], points[v]);
        }
    }

    glColor3f(1.0f, 1.0f, 1.0f);  
    if(model == 1){
        glBegin(GL_POINTS);
            for(int u=0; u < N ; u++){
                for(int v=0; v < N ; v++){
                   glVertex3fv(space[u][v]);
                }
            }
        glEnd();
    }

    else if(model  == 2){
     glBegin(GL_LINES);
        for(int u=0; u < N -1; u++){
            for(int v=0; v < N-1 ; v++){
               glVertex3fv(space[u][v]);
               glVertex3fv(space[u][v+1]);
               glVertex3fv(space[u][v]);
               glVertex3fv(space[u+1][v+1]);
               glVertex3fv(space[u][v]);
               glVertex3fv(space[u+1][v]);
            }
        }
      glEnd();
    }else{
        glBegin(GL_TRIANGLES);
            for(int u=0; u < N -1; u++){
                for(int v=0; v < N -1; v++){
                   glColor3f(colors[u][v][0], colors[u][v][1], colors[u][v][2]);
                   glVertex3fv(space[u][v]);
                   glColor3f(colors[u][v+1][0], colors[u][v+1][1], colors[u][v+1][2]);
                   glVertex3fv(space[u][v+1]);
                   glColor3f(colors[u+1][v+1][0], colors[u+1][v+1][1], colors[u+1][v+1][2]);
                   glVertex3fv(space[u+1][v+1]);

                   glColor3f(colors[u][v][0], colors[u][v][1], colors[u][v][2]);
                   glVertex3fv(space[u][v]);
                   glColor3f(colors[u+1][v][0], colors[u+1][v][1], colors[u+1][v][2]);
                   glVertex3fv(space[u+1][v]);
                   glColor3f(colors[u+1][v+1][0], colors[u+1][v+1][1], colors[u+1][v+1][2]);
                   glVertex3fv(space[u+1][v+1]);
                }
            }
        glEnd();
    }
}

void RenderScene(void)
{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    glLoadIdentity();
    

    Axes();
    
    
    glRotatef(theta[0], 1.0, 0.0, 0.0);

    glRotatef(theta[1], 0.0, 1.0, 0.0);

    glRotatef(theta[2], 0.0, 0.0, 1.0);

    drawEgg();

    glFlush();
    

    glutSwapBuffers();
    

 }

void MyInit(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ChangeSize(GLsizei horizontal, GLsizei vertical )
{

    GLfloat AspectRatio;
    
    if(vertical == 0)  

        vertical = 1;  

    glViewport(0, 0, horizontal, vertical);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    
    if(horizontal <= vertical)

        glOrtho(-7.5,7.5,-7.5/AspectRatio,7.5/AspectRatio,10.0, -10.0); 

    else

        glOrtho(-7.5*AspectRatio,7.5*AspectRatio,-7.5,7.5,10.0,-10.0);                     

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}
 
int main(int argc, char *argv[])
{          
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    generate_point();
    generate_colors();
    glutIdleFunc(spinEgg);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutCreateWindow("Układ współrzędnych 3-D");
                  
    glutDisplayFunc(RenderScene);
 
    glutReshapeFunc(ChangeSize);
 
    MyInit();
    
    glutKeyboardFunc(keys);

    glEnable(GL_DEPTH_TEST);
 
    glutMainLoop();
}