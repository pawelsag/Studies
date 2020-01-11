#include <GL/gl.h>
#include <GL/glut.h>

namespace pwrgl::light
{
	enum LIGHT_ID
	{
		LIGHT_1 = 0,
		LIGHT_2 = 1,
	};

	GLfloat base_color[][4] = {{1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}}; 

	GLfloat light_position[][4] = {{0.0, 0.0, 10.0, 1.0}, {0.0, 0.0, 10.0, 1.0}}; 

    GLfloat mat_ambient[][4]  = {{1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}};       
    // współczynniki ka =[kar,kag,kab] dla światła otoczenia

    GLfloat mat_diffuse[][4]  = {{1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}};
    // współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

    GLfloat mat_specular[][4] = {{1.0, 1.0, 1.0, 1.0},{1.0, 1.0, 1.0, 1.0}};
    // współczynniki ks =[ksr,ksg,ksb] dla światła odbitego               
   
    GLfloat mat_shininess[]  = {20.0, 20.0};


    GLfloat light_ambient[][4] = {{1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}};
    // składowe intensywności świecenia źródła światła otoczenia
    // Ia = [Iar,Iag,Iab]

    GLfloat light_diffuse[][4] = {{1.0, 1.0, 1.0, 1.0},{1.0, 1.0, 1.0, 1.0}};       
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

    GLfloat light_specular[][4]= {{1.0, 1.0, 1.0, 1.0},{1.0, 1.0, 1.0, 1.0}};
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie kierunkowe Is = [Isr,Isg,Isb]

    GLfloat att_constant[]  = {1.0,1.0};
    // składowa stała ds dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_linear[] = {0.05,0.05};
    // składowa liniowa dl dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_quadratic[]  = {0.001, 0.001};
    // składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
    // odległości od źródła
}