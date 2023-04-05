//gcc NBodyInBox.c -o temp2 -lglut -lm -lGLU -lGL
//To stop hit "control c" in the window you launched it from.
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define XWindowSize 1000
#define YWindowSize 1000

#define STOP_TIME 10000.0
#define DT        0.0001

#define GRAVITY 0.1 

#define MASS 10.0  	
#define DIAMETER 1.0

#define SPRING_STRENGTH 50.0
#define SPRING_REDUCTION 0.1

#define DAMP 0.0

#define DRAW 10

#define LENGTH_OF_BOX 6.0
#define MAX_VELOCITY 50.0

#define NUMBER_OF_BALLS 10

const float XMax = (LENGTH_OF_BOX/2.0);
const float YMax = (LENGTH_OF_BOX/2.0);
const float ZMax = (LENGTH_OF_BOX/2.0);
const float XMin = -(LENGTH_OF_BOX/2.0);
const float YMin = -(LENGTH_OF_BOX/2.0);
const float ZMin = -(LENGTH_OF_BOX/2.0);

// Globals
typedef struct spheres
{
	float px, py, pz, vx, vy, vz, fx, fy, fz, mass; 
}spheres;

struct spheres *Spheres;

void set_initial_conditions()
{ 
	time_t t;
	srand((unsigned) time(&t));
	int yeahBuddy;
	float dx, dy, dz, seperation;

	for(int i = 0; i < NUMBER_OF_BALLS; i++)
	{
		Spheres[i].px = (LENGTH_OF_BOX - DIAMETER)*rand()/RAND_MAX - (LENGTH_OF_BOX - DIAMETER)/2.0;
		Spheres[i].py = (LENGTH_OF_BOX - DIAMETER)*rand()/RAND_MAX - (LENGTH_OF_BOX - DIAMETER)/2.0;
		Spheres[i].pz = (LENGTH_OF_BOX - DIAMETER)*rand()/RAND_MAX - (LENGTH_OF_BOX - DIAMETER)/2.0;
	
		for(int j = i-1; j > 0; j--)	
		{
			dx = Spheres[i].px - Spheres[j].px;
			dy = Spheres[i].py - Spheres[j].py;
			dz = Spheres[i].pz - Spheres[j].pz;
			seperation = sqrt(dx*dx + dy*dy + dz*dz);
			printf("separation generated\n");
			if(seperation < DIAMETER)
			{
				i = i-1;
				printf("separation test failed, breaking inner loop\n");
				break;
			}
		}	
	}
	printf("ball positions set\n"); 
	
	for(int i = 0; i < NUMBER_OF_BALLS; i ++)
	{
		Spheres[i].vx = 0*2.0*MAX_VELOCITY*rand()/RAND_MAX - MAX_VELOCITY;
		Spheres[i].vy = 0*2.0*MAX_VELOCITY*rand()/RAND_MAX - MAX_VELOCITY;
		Spheres[i].vz = 0*2.0*MAX_VELOCITY*rand()/RAND_MAX - MAX_VELOCITY;

		Spheres[i].mass = 1.0;
		
	}	
	printf("set mass and velocity\n");
}

void Drawwirebox()
{		
	glColor3f (5.0,1.0,1.0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(XMax,YMax,ZMax);
		glVertex3f(XMax,YMax,ZMin);	
		glVertex3f(XMax,YMin,ZMin);
		glVertex3f(XMax,YMin,ZMax);
		glVertex3f(XMax,YMax,ZMax);
		
		glVertex3f(XMin,YMax,ZMax);
		
		glVertex3f(XMin,YMax,ZMax);
		glVertex3f(XMin,YMax,ZMin);	
		glVertex3f(XMin,YMin,ZMin);
		glVertex3f(XMin,YMin,ZMax);
		glVertex3f(XMin,YMax,ZMax);	
	glEnd();
	
	glBegin(GL_LINES);
		glVertex3f(XMin,YMin,ZMax);
		glVertex3f(XMax,YMin,ZMax);		
	glEnd();
	
	glBegin(GL_LINES);
		glVertex3f(XMin,YMin,ZMin);
		glVertex3f(XMax,YMin,ZMin);		
	glEnd();
	
	glBegin(GL_LINES);
		glVertex3f(XMin,YMax,ZMin);
		glVertex3f(XMax,YMax,ZMin);		
	glEnd();
	
}

void draw_picture()
{
	float radius = DIAMETER/2.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	Drawwirebox();
	
	for(int i = 0; i < NUMBER_OF_BALLS; i++)
	{
		glColor3d(1.0,0.5,0.0);
		glPushMatrix();
		glTranslatef(Spheres[i].px, Spheres[i].py, Spheres[i].pz);
		glutSolidSphere(radius,20,20);
		glPopMatrix();
		
	}	
	

	glutSwapBuffers();
}

void keep_in_box()
{
	float halfBoxLength = (LENGTH_OF_BOX - DIAMETER)/2.0;
	for(int i = 0; i < NUMBER_OF_BALLS; i++)
	{	
		if(Spheres[i].px > halfBoxLength)
		{
			Spheres[i].px = 2.0*halfBoxLength - Spheres[i].px;
			Spheres[i].vx = - Spheres[i].vx;
		}
		else if(Spheres[i].px < -halfBoxLength)
		{
			Spheres[i].px = -2.0*halfBoxLength - Spheres[i].px;
			Spheres[i].vx = - Spheres[i].vx;
		}
		
		if(Spheres[i].py > halfBoxLength)
		{
			Spheres[i].py = 2.0*halfBoxLength - Spheres[i].py;
			Spheres[i].vy = - Spheres[i].vy;
		}
		else if(Spheres[i].py < -halfBoxLength)
		{
			Spheres[i].py = -2.0*halfBoxLength - Spheres[i].py;
			Spheres[i].vy = - Spheres[i].vy;
		}
				
		if(Spheres[i].pz > halfBoxLength)
		{
			Spheres[i].pz = 2.0*halfBoxLength - Spheres[i].pz;
			Spheres[i].vz = - Spheres[i].vz;
		}
		else if(Spheres[i].pz < -halfBoxLength)
		{
			Spheres[i].pz = -2.0*halfBoxLength - Spheres[i].pz;
			Spheres[i].vz = - Spheres[i].vz;
		}
	}	
	
}

void get_forces()
{
	float dx,dy,dz,r,r2,dvx,dvy,dvz,forceMag,inout;
	
	for(int i = 0; i < NUMBER_OF_BALLS; i++)
	{
		for(int j = 0; j < NUMBER_OF_BALLS; j++)
		{
			if(i!=j)
			{	
				dx = Spheres[j].px - Spheres[i].px;
				dy = Spheres[j].py - Spheres[i].py;
				dz = Spheres[j].pz - Spheres[i].pz;
							
				r2 = dx*dx + dy*dy + dz*dz;
				r = sqrt(r2);

				forceMag =  Spheres[i].mass*Spheres[j].mass*GRAVITY/r2;
						
				if (r < DIAMETER)
				{
					dvx = Spheres[j].vx - Spheres[i].vx;
					dvy = Spheres[j].vy - Spheres[i].vy;
					dvz = Spheres[j].vz - Spheres[i].vz;
					inout = dx*dvx + dy*dvy + dz*dvz;
					if(inout <= 0.0)
					{
						forceMag +=  SPRING_STRENGTH*(r - DIAMETER);
					}
					else
					{
						forceMag +=  SPRING_REDUCTION*SPRING_STRENGTH*(r - DIAMETER);
					}
				}

				Spheres[i].fx = forceMag*dx/r;
				Spheres[i].fy = forceMag*dy/r;
				Spheres[i].fz = forceMag*dz/r;
			}
				
		}	
	}
}

void move_bodies(float time)
{
	if(time == 0.0)
	{
		for(int i = 0; i < NUMBER_OF_BALLS; i++)
		{
			Spheres[i].vx += 0.5*DT*(Spheres[i].fx - DAMP*Spheres[i].vx)/Spheres[i].mass;
			Spheres[i].vy += 0.5*DT*(Spheres[i].fy - DAMP*Spheres[i].vy)/Spheres[i].mass;
			Spheres[i].vz += 0.5*DT*(Spheres[i].fz - DAMP*Spheres[i].vz)/Spheres[i].mass;
		}
	}
	else
	{
		for(int i = 0; i < NUMBER_OF_BALLS; i++)
		{
			Spheres[i].vx += DT*(Spheres[i].fx - DAMP*Spheres[i].vx)/Spheres[i].mass;
			Spheres[i].vy += DT*(Spheres[i].fy - DAMP*Spheres[i].vy)/Spheres[i].mass;
			Spheres[i].vz += DT*(Spheres[i].fz - DAMP*Spheres[i].vz)/Spheres[i].mass;
		}
	}

	for(int i = 0; i < NUMBER_OF_BALLS; i++)
	{	
		Spheres[i].px += DT*Spheres[i].vx;
		Spheres[i].py += DT*Spheres[i].vy;
		Spheres[i].pz += DT*Spheres[i].vz;
	}	
	keep_in_box();
}

void nbody()
{	
	int    tdraw = 0;
	float  time = 0.0;

	set_initial_conditions();
	
	draw_picture();
	
	while(time < STOP_TIME)
	{
		get_forces();
	
		move_bodies(time);
	
		tdraw++;
		if(tdraw == DRAW) 
		{
			draw_picture(); 
			tdraw = 0;
		}
		
		time += DT;
	}
	printf("\n DONE \n");
	while(1);
}

void Display(void)
{
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glutSwapBuffers();
	glFlush();
	nbody();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-0.2, 0.2, -0.2, 0.2, 0.2, 50.0);

	glMatrixMode(GL_MODELVIEW);
}

void setup()
{
	Spheres = (spheres*)malloc(NUMBER_OF_BALLS*sizeof(spheres));
	printf("\nSetup complete\n");
}

void cleanup()
{
	free(Spheres);
	printf("\nCleaned up\n");
}

int main(int argc, char** argv)
{
	setup();

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(XWindowSize,YWindowSize);
	glutInitWindowPosition(0,0);
	glutCreateWindow("wow... balls");
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat light_ambient[]  = {0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat mat_specular[]   = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[]  = {10.0};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	cleanup();
	return 0;
}





