#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

typedef float point3[3];

namespace pwrgl::egg
{
	constexpr int N =64;

	point3 space[N][N];
	point3 normal[N][N];
	point3 WHITE = {255,255,255};
	constexpr point3 LIGHT_SOURCE = {0.0, 0.0, 1.0};

	double points[N];
	constexpr double PI = 3.14159265;

	constexpr double calc_x(double u, double v)
	{
	    return  (-90*pow(u,5) + 225*pow(u,4) - 270*pow(u,3) + 180*pow(u,2) - 45*u) * cos(PI * v);
	}

	constexpr double calc_y(double u, double v)
	{
	    return  160*pow(u,4) - 320*pow(u,3) + 160*pow(u,2)-5.6;
	}

	constexpr double calc_z(double u, double v)
	{
	    return  (-90*pow(u,5) + 225*pow(u,4) - 270*pow(u,3) + 180*pow(u,2) - 45*u) * sin(PI * v);
	}


	constexpr double calc_x_derivative_u(double u, double v)
	{
	    return  (-450*pow(u,4) + 900*pow(u,3) -810*pow(u,2) + 360*u-45) * cos(PI * v);
	}

	constexpr double calc_x_derivative_v(double u, double v)
	{
	    return  PI*(90*pow(u,5) - 225*pow(u,4) + 270*pow(u,3) -180 * pow(u,2) + 45*u) * sin(PI * v);
	}

	constexpr double calc_y_derivative_u(double u, double v)
	{
	    return  640*pow(u,3) -960*pow(u,2) + 320*u;
	}

	constexpr double calc_y_derivative_v(double u, double v)
	{
	    return  0;
	}

	constexpr double calc_z_derivative_u(double u, double v)
	{
	    return  (-450*pow(u,4) + 900*pow(u,3) - 810*pow(u,2) + 360*u -45) * sin(PI * v);
	}

	constexpr double calc_z_derivative_v(double u, double v)
	{
	    return  -PI*(90*pow(u,5) -225*pow(u,4) + 270*pow(u,3) - 180*pow(u,2) +45*u)*cos(PI * v);
	}

	constexpr double vec_length(const point3 vec)
	{
	    return  sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
	}

	void generate_points(){
	    for(int i =0 ; i < N; i++)
	    {
	      points[i] = float(i) / (N-1);
	    }
	}
	constexpr double LIGHT_SOURCE_VEC_LEN = vec_length(LIGHT_SOURCE);

	void generate_object()
	{
		int sign = 1;
	    for(int u=0; u < N ; u++){
	        for(int v=0; v < N ; v++){
	    		sign = 1;

	            space[u][v][0] = calc_x(points[u], points[v]);
	            space[u][v][1] = calc_y(points[u], points[v]);
	            space[u][v][2] = calc_z(points[u], points[v]);

	            normal[u][v][0] = calc_y_derivative_u(points[u], points[v]) *
	            				  calc_z_derivative_v(points[u], points[v]) -
	            				  calc_z_derivative_u(points[u], points[v]) *
	            				  calc_y_derivative_v(points[u], points[v]);

	            normal[u][v][1] = calc_z_derivative_u(points[u], points[v]) *
	            				  calc_x_derivative_v(points[u], points[v]) -
	            				  calc_x_derivative_u(points[u], points[v]) *
	            				  calc_z_derivative_v(points[u], points[v]);

	            normal[u][v][2] = calc_x_derivative_u(points[u], points[v]) *
	            				  calc_y_derivative_v(points[u], points[v]) -
	            				  calc_y_derivative_u(points[u], points[v]) *
	            				  calc_x_derivative_v(points[u], points[v]);
  	
	            double l = vec_length(normal[u][v]);  
            
	            normal[u][v][0] /= l;
	            normal[u][v][1] /= l;
	            normal[u][v][2] /= l;
	          	if(u > N/2){
		            normal[u][v][0] *= -1;
		            normal[u][v][1] *= -1;
		            normal[u][v][2] *= -1;
		        }

	        }
    	}
	}

	void initEgg()
	{
		generate_points();
		generate_object();
	}

	void renderEgg()
	{
	    glBegin(GL_TRIANGLES);
	     glColor3f(WHITE[0], WHITE[1], WHITE[2]);
	     for(int u=0; u < N -1; u++){
	        for(int v=0; v < N -1; v++){
	           glNormal3fv(normal[u][v]);
	           glTexCoord2f(space[u][v][0], space[u][v][1]);
	           glVertex3fv(space[u][v]);

	           glNormal3fv(normal[u][v+1]);
	           glTexCoord2f(space[u][v+1][0], space[u][v+1][1]);
	           glVertex3fv(space[u][v+1]);
	           
	           glNormal3fv(normal[u+1][v+1]);
	           glTexCoord2f(space[u+1][v+1][0], space[u+1][v+1][1]);
	           glVertex3fv(space[u+1][v+1]);

	           glNormal3fv(normal[u][v]);
	           glTexCoord2f(space[u+1][v+1][0], space[u+1][v+1][1]);
	           glVertex3fv(space[u][v]);

	           glNormal3fv(normal[u+1][v]);
	           glTexCoord2f(space[u+1][v][0], space[u+1][v][1]);
	           glVertex3fv(space[u+1][v]);

	           glNormal3fv(normal[u+1][v+1]);
	           glTexCoord2f(space[u][v][0], space[u][v][1]);
	           glVertex3fv(space[u+1][v+1]);
	        }
	     }
	    glEnd();
	}
}
