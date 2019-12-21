
#include <iostream>

//#include "bitmap_image.hpp"
//#pragma warning(disable:4996)
#include <GL/glut.h>
#include<vector>
#include <stdio.h>
#include "imageloader.h"

using namespace std;



struct linestrip
{
        float x;
        float y;
		int r,g,b;
};

struct line
{
        float ix,fx;
        float iy,fy;
		int r,g,b;
};

struct point
{
        float x;
        float y;
		int r,g,b;
};
struct filledrectangle
{
        float ix;
        float iy;
		float fx,fy;
		int r,g,b;
};
GLuint sel=0, _textureId;
int colorsel=0,icount=0,br=0,contrast=0;
float BOX_SIZE1 = 1.0f,ixtex=0,iytex=0,fxtex=1,fytex=1,ixt=0,iyt=0,fxt=1,fyt=1;
float BOX_SIZE2 = 1.0f;
float _angle = 0;            
float  scale_x=1,scale_y=1,alightx=1,alighty=1,alightz=1;         
int ix,iy,fx=0,fy=0,kk=0,height=0,width=0,red=0,green=0,blue=0,isel=0,curimage=0;
string imar[3]={"bag1.bmp","ts.bmp","yts.bmp"};

        vector <linestrip> linestrips;
		vector <line> lines;
		vector <point> points;
		vector <filledrectangle> filledrectangles;

		line linepoint;
		point pointpoint;
		filledrectangle filledrectanglepoint;
        linestrip linestrippoint;




	void reset()
	{
		sel=0;
br=0;contrast=0;
ixtex=0;iytex=0;fxtex=1;fytex=1;ixt=0;iyt=0;fxt=1;fyt=1;

_angle = 0;            
scale_x=1;scale_y=1;alightx=1;alighty=1;alightz=1;         
fx=0;fy=0;kk=0;red=0;green=0;blue=0;
linestrips.clear(); lines.clear(); points.clear(); filledrectangles.clear();
	}

void mouse(int button,int state,int x,int y)
{
	
      if (state == GLUT_DOWN)
      {      cout<<x-width/2<<" "<<height-y-height/2<<endl;
			if(sel==13)
			{   
				filledrectanglepoint.r=red;filledrectanglepoint.g=green;filledrectanglepoint.b=blue;
				filledrectanglepoint.ix=((float)x-(float)width/2)*.83/scale_x;
				filledrectanglepoint.iy=(float)(height-y-height/2)*.827/scale_y;
			}
			else if(sel==10)
			{
				linepoint.r=red;linepoint.g=green;linepoint.b=blue;
				cout<<linepoint.r<<" "<<red<<" "<<linepoint.g<<" "<<linepoint.b<<endl;
				linepoint.ix=((float)x-(float)width/2)*.83/scale_x;
				cout<<x<<" "<<(float)(x-width/2)*.827<<endl;
				linepoint.iy=(float)(height-y-height/2)*.827/scale_y;
			}
			else if(sel==14)
			{
				
				ixt=(((float)x-(float)width/2)*.83/scale_x+((float)width/2))/BOX_SIZE1;
				cout<<x<<" "<<(float)(x-width/2)*.827<<endl;
				iyt=((float)(height-y-height/2)*.827/scale_y+((float)height/2))/BOX_SIZE2;
			}

                   
	  }
	  else if(state==GLUT_UP)
	  {
			cout<<x-width/2<<" "<<height-y-height/2<<endl;
		    if(sel==11)
			{   
				linestrippoint.r=red;linestrippoint.g=green;linestrippoint.b=blue;
				linestrippoint.x= ((float)x-(float)width/2)*.83/scale_x;
                linestrippoint.y= (float)(height-y-height/2)*.827/scale_y; 
                linestrips.push_back(linestrippoint);
                for (int i =0; i <= linestrips.size() -1; i++)
                  {
                          printf("linestrip is %d  %d\n",linestrips[i].x, linestrips[i].y);
                  }
                  printf("*****\n");
		  }
		
		   else if(sel==13)
		  {
		  filledrectanglepoint.fx=((float)x-(float)width/2)*.83/scale_x;
					filledrectanglepoint.fy=(float)(height-y-height/2)*.827/scale_y;
					filledrectangles.push_back(filledrectanglepoint);
                  for (int i =0; i <= filledrectangles.size() -1; i++)
                  {
                          printf("rectanglePoint is %d  %d %d  %d\n",filledrectangles[i].ix, filledrectangles[i].iy,filledrectangles[i].fx, filledrectangles[i].fy);
                  }
                  printf("*****\n");
		  }
		  else if(sel==10)
		  {
			  linepoint.fx=((float)x-(float)width/2)*.83/scale_x;
			  linepoint.fy=(float)(height-y-height/2)*.827/scale_y;
					lines.push_back(linepoint);
                  for (int i =0; i <= lines.size() -1; i++)
                  {
                          printf("LinePoint is %f  %f %f  %f\n",lines[i].ix,lines[i].iy,lines[i].fx, lines[i].fy);
                  }
                  printf("*****\n");
		  }
		   else if(sel==14)
			{
				
				ixtex=ixt;iytex=iyt;
				fxtex=(((float)x-(float)width/2)*.83/scale_x+((float)width/2))/BOX_SIZE1;
				cout<<x<<" "<<(float)(x-width/2)*.827<<endl;
				fytex=((float)(height-y-height/2)*.827/scale_y+((float)height/2))/BOX_SIZE2;
				BOX_SIZE1=ixtex*BOX_SIZE1-fxtex*BOX_SIZE1;
				BOX_SIZE2=iytex*BOX_SIZE2-fytex*BOX_SIZE2;
				if(BOX_SIZE1<0) BOX_SIZE1*=-1;
				if(BOX_SIZE2<0) BOX_SIZE2*=-1;
				if(ixtex>fxtex)
				{
					float flo=ixtex;
					ixtex=fxtex;
					fxtex=ixtex;
				}
				if(ixtex>fxtex)
				{
					float flo=ixtex;
					ixtex=fxtex;
					fxtex=flo;
				}if(iytex>fytex)
				{
					float flo=iytex;
					iytex=fytex;
					fytex=flo;
				}
		  }


		   glutPostRedisplay();
	  }
	

}

void activemotionprocessMouse(int x,int y)
	{
		   if(sel==9)
		  {   
			  pointpoint.r=red;pointpoint.g=green;pointpoint.b=blue;
				  pointpoint.x=((float)x-(float)width/2)*.83/scale_x;
                  pointpoint.y= (float)(height-y-height/2)*.827/scale_y; 
				//  cout<<x<<" "<<y<<" "<< pointpoint.x<<" "<< pointpoint.y<<endl;
                  points.push_back(pointpoint);
                 /* for (int i =0; i <= points.size() -1; i++)
                  {
                          printf("pointPoint is %f  %f\n",points[i].x, points[i].y);
                  }
                  printf("*****\n");*/
		  }


		   glutPostRedisplay();
	}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}


void options(int item)
{
	
	 if(item>100)
	{
		colorsel=item;
	}
	 else if(item>30)
	 {
		isel=item;
	 }
	else if(item>0)
	{sel=item;
	}
}



GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	BOX_SIZE1=image->width;
	BOX_SIZE2=image->height;
	

	cout<<BOX_SIZE1<<" "<<BOX_SIZE2<<endl;

	return textureId;
}
bool c=true;
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1,1,1,1);
	Image* image = loadBMP(imar[curimage],c,br,contrast);
	
	_textureId = loadTexture(image);
	
	

	delete image;
}

void handleResize(int w, int h) {
	height=h;width=w;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0,1500.0);
	glutReshapeWindow(700,500);
}


bool a=true;
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -500.0f);
	
	GLfloat ambientLight[] = {alightx, alighty, alightz, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	glRotatef(-_angle, 0.0f, 0.0f, 1.0f);
	 glScalef(scale_x, scale_y, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 0.0f, 0.0f);
	
	//glPushMatrix();
//	glTranslatef(2.0f,0.0f,0.0f);
	glBegin(GL_QUADS);
	
	//Front face
	glNormal3f(0.0, 0.0f, 1100.0f);
	glTexCoord2f(ixtex, iytex);	glVertex3f(-BOX_SIZE1 / 2, -BOX_SIZE2 / 2, 0);
	glTexCoord2f(fxtex, iytex);	glVertex3f(BOX_SIZE1 / 2, -BOX_SIZE2 / 2,0);
	glTexCoord2f(fxtex, fytex);	glVertex3f(BOX_SIZE1 / 2, BOX_SIZE2 / 2,0);
	glTexCoord2f(ixtex, fytex);	glVertex3f(-BOX_SIZE1 / 2, BOX_SIZE2 / 2, 0);
	
	glEnd();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT);
	          
				glBegin(GL_LINE_STRIP);
                for(int i =0; i < linestrips.size();i++)
                {
					glColor3ub(linestrips[i].r,linestrips[i].g,linestrips[i].b);
				//	glBegin(GL_LINE_STRIP);
                        glVertex3f(linestrips[i].x, linestrips[i].y,0);
                }
				glEnd();
				//glPointSize(2);
			//	glColor3f(1,0,0);
				
				
				glBegin(GL_LINES);
				//glVertex3i(200,200,0);
				//glVertex3i(200,100,0);
                for(int i =0; i < lines.size();i++)
				{      glColor3f(lines[i].r/255,lines[i].g/255,lines[i].b/255);
				//	glBegin(GL_LINES);
                        glVertex3f(lines[i].ix, lines[i].iy,0);
						glVertex3f(lines[i].fx, lines[i].fy,0);
						

                }
				glEnd();
					//glPointSize(60);
				
				{
				glBegin(GL_POINTS);
				glPointSize(6);
				 for(int i =0; i < points.size();i++)
					 
				 {     glColor3ub(points[i].r,points[i].g,points[i].b);
				// glBegin(GL_POINTS);
                        glVertex3f(points[i].x, points[i].y,0);
                }
				}
				glEnd();
				
				{   /* glColor3f(0,1,0);
					glVertex3f(0,0,0);
					glVertex3f(1,0,0);
					glVertex3f(1,1,0);
					glVertex3f(0,1,0);*/glBegin(GL_QUADS);
					for(int i =0; i < filledrectangles.size();i++)
                {
					glColor3ub(filledrectangles[i].r,filledrectangles[i].g,filledrectangles[i].b);
			//		glBegin(GL_QUADS);
                        glVertex3f(filledrectangles[i].ix, filledrectangles[i].iy,0);
						glVertex3f(filledrectangles[i].ix, filledrectangles[i].fy,0);
						glVertex3f(filledrectangles[i].fx, filledrectangles[i].fy,0);
						glVertex3f(filledrectangles[i].fx, filledrectangles[i].iy,0);
                }
				}
				
				glEnd();
				

	glutSwapBuffers();
}



void saveimage()
{ 
	size_t cur;
	FILE *file=fopen("ss1.PPM","w");
				
	fprintf(file, "P3\n%d %d\n%d\n", BOX_SIZE1, BOX_SIZE2, 255);
				unsigned char *pixels =(unsigned char *)malloc((int)(BOX_SIZE1*BOX_SIZE2*(3)));
				glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);
				for(int i=0;i<BOX_SIZE2;i++)
				{
					for(int j=0;j<BOX_SIZE1;j++)
					{
						cur=3 * ((BOX_SIZE2 - i - 1) * BOX_SIZE1 + j);
						fprintf(file,"%3d %3d %3d ", (*pixels), (*pixels+1), (*pixels+2));
					}
					fprintf(file,"\n");
				}
				fclose(file);
}

void update(int value) {
	/*_angle += 1.0f;
	if (_angle > 360) {
		_angle -= 360;
	}*/
	if(sel==1)
	{ sel=0;
		_angle+=180;// cout<<"hre"<<endl;
	}
	else if(sel==2)
	{sel=0;
		_angle-=90;
	}

	else if(sel==3)
	{sel=0;
		scale_y*=-1;
	}

	else if(sel==4)
	{sel=0;
		scale_x*=-1;
	}
	else if(sel==5)
	{sel=0;
		br-=10;
		
		initRendering();
	}
	else if(sel==6)
	{sel=0;
		br+=10;
		
		initRendering();
	}
	else if(sel==7)
	{sel=0;
		scale_x*=1.25;
		scale_y*=1.25;
		//scale_z*=1.5;
		
	}
	else if(sel==8)
	{sel=0;
		scale_x*=.8;
		scale_y*=.8;
		//scale_z*=1.5;
		
	}
	else if(sel==16)
	{sel=0;
		if(!c)
		{
			c=true;
			initRendering();
		}
	}
	else if(sel==15)
	{sel=0;
		if(c)
		{
			c=false;
			initRendering();
		}
		
	}
	else if(sel==17)
	{sel=0;
	saveimage();
		
	}
	else if(sel==18)
	{sel=0;

	contrast+=10;
	initRendering();
	}
	else if(sel==19)
	{sel=0;
	contrast-=10;
	initRendering();
	}
	
	if(_angle>360)
	{
		_angle-=360;
	}
	

	/*
	glutAddMenuEntry("Red",11);
		glutAddMenuEntry("Green",12);
		glutAddMenuEntry("Blue",13);
		glutAddMenuEntry("While",14);
		glutAddMenuEntry("Black",15);
		glutAddMenuEntry("Yellow",16);
		glutAddMenuEntry("Violet",17);
	*/if(colorsel==101)
	{colorsel=0;
		red=255;green=0;blue=0;
		cout<<"color "<<red<<endl;

	}
	else if(colorsel==102)
	{colorsel=0;
		red=0;green=255;blue=0;
		
	}
	else if(colorsel==103)
	{colorsel=0;
		red=0;green=0;blue=255;

	}
	else if(colorsel==104)
	{colorsel=0;
		red=255;green=255;blue=255;

	}
	else if(colorsel==105)
	{colorsel=0;
		red=0;green=0;blue=0;

	}
	else if(colorsel==106)
	{colorsel=0;
		red=253;green=233;blue=127;

	}
	else if(colorsel==107)
	{colorsel=0;
		red=108;green=0;blue=255;

	}

	if(isel==31&&curimage!=0)
	{
		curimage=0;
		reset();
		initRendering();
	}
	else if(isel==32&&curimage!=1)
	{
		curimage=1;
		reset();
		initRendering();
	}
	else if(isel==33&&curimage!=2)
	{
		curimage=2;
		reset();
		initRendering();
	}
	glutPostRedisplay();
	glutTimerFunc(1, update, 0);
}

void colors(int item)
{
		colorsel=item;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 500);
	
	glutCreateWindow("24-Bit BMP photo editor");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutTimerFunc(1, update, 0);
	glutKeyboardFunc(handleKeypress);
	glutMouseFunc(mouse);
	glutMotionFunc(activemotionprocessMouse);
	int fmenu=glutCreateMenu(options);
	glutAddMenuEntry("01. Rotate 90 degree",1);
	glutAddMenuEntry("02. Rotate -90 degree",2);
	glutAddMenuEntry("03. Flip Vertically",3);
	glutAddMenuEntry("04. Flip Horizontally",4);
	glutAddMenuEntry("05. Reduce Brightness",5);
	glutAddMenuEntry("06. Increase Brightness",6);
	glutAddMenuEntry("07. Zoom in",7);
	glutAddMenuEntry("08. Zoom out",8);
	glutAddMenuEntry("09. Pencil",9);
	glutAddMenuEntry("10. Lines",10);
	glutAddMenuEntry("11. Line Strips",11);
	//glutAddMenuEntry("12. Ractangles",12);
	glutAddMenuEntry("12. FilledRectangles",13);
	glutAddMenuEntry("13. Crop",14);
	glutAddMenuEntry("14. To Grayscale",15);
	glutAddMenuEntry("15. To Color",16);	
	glutAddMenuEntry("16. Save Image",17);
	glutAddMenuEntry("17. Increase Contrast",18);
	glutAddMenuEntry("18. Reduce Contrast",19);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	int cmenu=glutCreateMenu(options);
		glutAddMenuEntry("Red",101);
		glutAddMenuEntry("Green",102);
		glutAddMenuEntry("Blue",103);
		glutAddMenuEntry("While",104);
		glutAddMenuEntry("Black",105);
		glutAddMenuEntry("Yellow",106);
		glutAddMenuEntry("Violet",107);
		
		
	int imenu=glutCreateMenu(options);
		glutAddMenuEntry("Bag image",31);
		glutAddMenuEntry("Shirt image",32);
		glutAddMenuEntry("YTS image",33);
		
	glutCreateMenu(options);
	glutAddSubMenu("Funcctions", fmenu);
	glutAddSubMenu("Colors", cmenu);
	glutAddSubMenu("Change Image", imenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
