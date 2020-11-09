

#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <math.h>


double f(double a, double b, double t) { return a * (1 - t) + b * t; }

double f2(double p0, double p1, double p2, double p3, double t)
{
	return p0 * (1 - t) * (1 - t) * (1 - t) + 3 * t * p1 * (1 - t) * (1 - t) + 3 * t * t * p2 * (1 - t) + t * t * t * p3; //Безье 3-го порядка
}

double fer(double p1, double p4, double r1, double r4, double t)
{
	return p1 * (2 * t * t * t - 3 * t * t + 1) + p4 * (3 * t * t - 2 * t * t * t) + r1 * (t * t * t - 2 * t * t + t) + r4 * (t * t * t - t * t); //Эрмитa
}

double f666(double p1, double p4, double r1, double r4, double t)
{
	return p1 * (2 * t * t * t - 3 * t * t + 1) + p4 * (3 * t * t - 2 * t * t * t) + r1 * (t * t * t - 2 * t * t + t) + r4 * (t * t * t - t * t); //Эрмитa
}



double t_max = 0;
void Render(double delta_time)
{

	t_max += delta_time / 5; //t_max становится = 1 за 5 секунд  

	if (t_max > 1) t_max = 0; //после обнуляется 

	double P1[] = { 0,0,0 }; //Наши точки, массивчик double 
	double P2[] = { 3,-6,7 };
	double P3[] = { 5,-6,-5 };
	double P4[] = { 8,-1,-3 };
	double P[3];


	glBegin(GL_LINES); //построим отрезки P1P2  и P2P3 
	glVertex3dv(P1); 
	glVertex3dv(P2); 
	glVertex3dv(P2); 
	glVertex3dv(P3);  
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd(); 

	glLineWidth(3);  //ширина линии 

	glColor3d(0, 1, 0);

	glBegin(GL_LINE_STRIP);         
	for (double t = 0; t <= t_max; t += 0.01)
	{
		P[0] = f2(P1[0], P2[0], P3[0], P4[0], t);    
		P[1] = f2(P1[1], P2[1], P3[1], P4[1], t);
		P[2] = f2(P1[2], P2[2], P3[2], P4[2], t);
		glVertex3dv(P);   //Рисуем точку P  
	}   
		glEnd();   


		glColor3d(1, 0, 1);  
		glLineWidth(1);  //возвращаем ширину линии = 1  
		

		glPointSize(10);
		glBegin(GL_POINTS); 
		glVertex3dv(P); 
		glEnd();  

		glPointSize(5);
		glColor3d(1, 0, 0); 
		glBegin(GL_POINTS); 
		glVertex3dv(P1);
		glVertex3dv(P2); 
		glVertex3dv(P3);
		glEnd();

		/////////////////////////
		
		 /*
		double r1[] = { 0,4,0 }; //Наши точки
		double r2[] = { 0,2,6 };

		double r3[] = { 4,6,3 };
		double r4[] = { 8,8,8 };

		double P5[] = { r1[0],r1[1], r1[2] };
		double P6[] = { r3[0],r3[1], r3[2] };

		double R1[] = { r2[0] - r1[0],r2[1] - r1[1],r2[2] - r1[2] };
		double R2[] = { r4[0] - r3[0],r4[1] - r3[1],r4[2] - r3[2] };
		*/

		double r1[] = { 0,4,0 }; //Наши точки
		double r2[] = { 0,2,6 };

		double r3[] = { 4,6,3 };
		double r4[] = { 8,8,8 };

		double P5[] = { 0,4,0 };;
		double P6[] = { 4,6,3 };

		double R1[] = { 0,-2,6 };
		double R2[] = { 4, 2, 5};
		
		double PPP[3];

		glBegin(GL_LINES); //построим отрезки P1P2  и P2P3 
		glVertex3dv(r1);
		glVertex3dv(r2);
		glVertex3dv(r3);
		glVertex3dv(r4);
		glEnd();

		
		glLineWidth(3);  //ширина линии 

		glColor3d(0, 1, 0);

		glBegin(GL_LINE_STRIP);
		for (double t = 0; t <= t_max; t += 0.01)
		{
			PPP[0] = fer(P5[0], P6[0], R1[0], R2[0], t);
			PPP[1] = fer(P5[1], P6[1], R1[1], R2[1], t);
			PPP[2] = fer(P5[2], P6[2], R1[2], R2[2], t);
			glVertex3dv(PPP);   //Рисуем точку P  
		}
		glEnd();


		glColor3d(1, 0, 1);
		glLineWidth(1);  //возвращаем ширину линии = 1  


		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex3dv(PPP);
		glEnd();

		glPointSize(5);
		glColor3d(1, 0, 0);
		glBegin(GL_POINTS);
		glVertex3dv(r1);
		glVertex3dv(r2);
		glVertex3dv(r3);
		glVertex3dv(r4);
		glEnd();
		
	
		

}