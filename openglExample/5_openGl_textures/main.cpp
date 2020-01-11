#include <time.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include "egg.hpp"
#include "polygons.hpp"
#include "light_config.hpp"

thread_local std::mt19937 gen{std::random_device{}()};
const char* tex1 = "tekstura.tga";
const char* tex2 = "D1_t.tga";
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
static int text_mode = 0;
static point3 norm= {0.0f, 0.0f, 1.0f};
int direction = 1;

int target_render = 0;

void RenderScene(void);
GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{
/*************************************************************************************/
// Struktura dla nagłówka pliku  TGA
    #pragma pack(1)           
    typedef struct                       
    {
        GLbyte    idlength;             
        GLbyte    colormaptype;          
        GLbyte    datatypecode;            
        unsigned short    colormapstart; 
        unsigned short    colormaplength;
        unsigned char     colormapdepth;  
        unsigned short    x_orgin;        
        unsigned short    y_orgin;        
        unsigned short    width;         
        unsigned short    height;        
        GLbyte    bitsperpixel;                  
        GLbyte    descriptor;            
    }TGAHEADER;
    #pragma pack(8)
    FILE *pFile;                   
    TGAHEADER tgaHeader;           
    unsigned long lImageSize;       
    short sDepth;                   
    GLbyte    *pbitsperpixel = NULL; 
          
/*************************************************************************************/ 
// Wartości domyślne zwracane w przypadku błędu
    *ImWidth = 0;               
    *ImHeight = 0;
    *ImFormat = GL_BGR_EXT;
    *ImComponents = GL_RGB8;
   
    pFile = fopen(FileName, "rb");
    if(pFile == NULL)
      return NULL;
/*************************************************************************************/
// Przeczytanie nagłówka pliku 
    fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);
                
/*************************************************************************************/
// Odczytanie szerokości, wysokości i głębi obrazu
    *ImWidth = tgaHeader.width;
    *ImHeight = tgaHeader.height;
    sDepth = tgaHeader.bitsperpixel / 8;
/*************************************************************************************/
// Sprawdzenie, czy głębia spełnia założone warunki (8, 24, lub 32 bity)
   
    if(tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
        return NULL;
/*************************************************************************************/
// Obliczenie rozmiaru bufora w pamięci
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
/*************************************************************************************/   
// Alokacja pamięci dla danych obrazu
     pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
   
      if(pbitsperpixel == NULL)
        return NULL;
    if(fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
        {
        free(pbitsperpixel);
        return NULL;
        }
   
/*************************************************************************************/
// Ustawienie formatu OpenGL
    switch(sDepth)
        {
        case 3:    
            *ImFormat = GL_BGR_EXT;
            *ImComponents = GL_RGB8;
            break;
        case 4:
            *ImFormat = GL_BGRA_EXT;
            *ImComponents = GL_RGBA8;
            break;
        case 1:
            *ImFormat = GL_LUMINANCE;
            *ImComponents = GL_LUMINANCE8;
            break;
        };
     
    fclose(pFile);
       
    return pbitsperpixel;
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
    case '1':
      text_mode =0;
    break;
    case '2':
      text_mode =1;
    break;
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
     case 't':
      target_render = 2;
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

void load_texture(const char* file)
{

    GLbyte *pBytes;
    GLint ImWidth, ImHeight, ImComponents;
    GLenum ImFormat;

   /*************************************************************************************/
   // Teksturowanie będzie prowadzone tyko po jednej stronie ściany
    glEnable(GL_CULL_FACE);
   /*************************************************************************************/
   //  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga
    pBytes = LoadTGAImage(file, &ImWidth, &ImHeight, &ImComponents, &ImFormat);
    /*************************************************************************************/
   // Zdefiniowanie tekstury 2-D
    glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);
   /*************************************************************************************/
   // Zwolnienie pamięci
   free(pBytes);
   /*************************************************************************************/
   // Włączenie mechanizmu teksturowania
    glEnable(GL_TEXTURE_2D);
   /*************************************************************************************/
   // Ustalenie trybu teksturowania
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   /*************************************************************************************/
   // Określenie sposobu nakładania tekstur
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
}

void Axes(void)
{

    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};
    

    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};
    

    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};
    

    glBegin(GL_LINES); 

        glVertex3fv(x_min);
        glVertex3fv(x_max);

    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  
    glBegin(GL_LINES);  

        glVertex3fv(y_min);
        glVertex3fv(y_max);                           

    glEnd();
  
    glBegin(GL_LINES); 

        glVertex3fv(z_min);
        glVertex3fv(z_max);

    glEnd();

}

void draw_3colors_triangle(){
  
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  
  glNormal3fv(norm);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0.0,0.0);
  
  glNormal3fv(norm);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(5.0,0.0);
  
  glNormal3fv(norm);
  glTexCoord2f(0.5f, 1.0f);
  glVertex2f(2.5,5.0);
  glEnd();
}
void generate_cube()
{
  //front
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0,0.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0,1.0,0.0);
  glEnd();

glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0,1.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,1.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
  glEnd();
  


  // left
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0,0.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0,0.0,-1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0,1.0,-1.0);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0,1.0,-1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0,1.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0,0.0,0.0);
  glEnd();
  
// right
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,1.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0,1.0,-1.0);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0,1.0,-1.0);

    glNormal3fv(norm);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0,0.0,-1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
  glEnd();

  // top
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,1.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0,1.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0,1.0,-1.0);   
  glEnd();
glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0,1.0,-1.0);

    glNormal3fv(norm);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,1.0,-1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,1.0,0.0);
  glEnd();

  // bottom
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0, 0.0, -1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0,0.0,0.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0,0.0,0.0);
  glEnd();

glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0,0.0,0.0);

    glNormal3fv(norm);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,0.0,-1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0, 0.0, -1.0);
  glEnd();

   // back
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0, 0.0, -1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0, 0.0, -1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0, 1.0, -1.0);
  glEnd();

glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glNormal3fv(norm);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0, 1.0, -1.0);

    glNormal3fv(norm);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0, 1.0, -1.0);
    
    glNormal3fv(norm);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0, 0.0, -1.0);
  glEnd();
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    if(abs(elevation) >= 2*pi )
        elevation=0.0;

    gluLookAt(viewer[0],viewer[1],viewer[2], target_pos[0], target_pos[1], target_pos[2], 0.0, 1.0, 0.0);

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
    if(text_mode ==0 )
      load_texture(tex1);
    else
      load_texture(tex2);

    if (target_render == 1 )
      pwrgl::egg::renderEgg();
    else if (target_render == 2)
      draw_3colors_triangle();
    else
      generate_cube();
    glFlush();
    
    glutSwapBuffers();
 }

void MyInit(void)
{
    using namespace pwrgl::light;
    load_texture(tex1);
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