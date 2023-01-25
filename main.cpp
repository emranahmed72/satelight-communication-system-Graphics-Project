
#include <windows.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
static double x=0.0;
static double move=-60;
static float rx[100]= {0}, ry[100]= {0};

//control waves
static double w1=0,w2=0,w3=0;
static bool transmit=false;

void *font;
void *currentfont;

double radius = 10;
double eyex = 0;
double eyey = -0.75;
double eyez = radius;
double centerx = 0;
double centery = -0.75;
double centerz = 0;
double upx = 0;
double upy = 1;
double upz = 0;
double myval = 0;



#include "BmpLoader.h"
#include<stdio.h>
#include <iostream>

unsigned int ID1, ID2;

BmpLoader::BmpLoader(const char* filename)
{
    FILE *file=0;
    file=fopen(filename, "rb");
    if(!file)
        std::cout<<"File not found"<<std::endl;
    fread(&bfh, sizeof(BITMAPFILEHEADER),1,file);
    if(bfh.bfType != 0x4D42)
        std::cout<<"Not a valid bitmap"<<std::endl;
    fread(&bih, sizeof(BITMAPINFOHEADER),1,file);
    if(bih.biSizeImage==0)
        bih.biSizeImage=bih.biHeight*bih.biWidth*3;
    textureData = new unsigned char[bih.biSizeImage];
    fseek(file, bfh.bfOffBits, SEEK_SET);
    fread(textureData, 1, bih.biSizeImage, file);
    unsigned char temp;
    for(int i=0; i<bih.biSizeImage; i+=3)
    {
        temp = textureData[i];
        textureData[i] = textureData[i+2];
        textureData[i+2] = temp;

    }

    iWidth = bih.biWidth;
    iHeight = bih.biHeight;
    fclose(file);
}

BmpLoader::~BmpLoader()
{
    delete [] textureData;
}


int i=0;
void LoadTexture1(const char*filename)
{
    i++;
    glGenTextures(i, &ID1);
    glBindTexture(GL_TEXTURE_2D, ID1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );

}


void setFont(void *font)
{
    currentfont=font;
}

void drawstring(float x,float y,float z,char *string)
{
    char *c;
    glRasterPos3f(x,y,z);
    for(c=string; *c!='\0'; c++)
    {
        glColor3f(0.0,1.0,1.0);
        glutBitmapCharacter(currentfont,*c);
    }
}

void
stroke_output(GLfloat x, GLfloat y, char *format,...)
{
    va_list args;
    char buffer[200], *p;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    glPushMatrix();
    glTranslatef(-3.0, y, 2);
    glScaled(0.002, 0.003, 0.003);
    for (p = buffer; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
}
void satellite()
{

    glRotatef(60,1,0,0);

//body
    glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glScaled(1,0.6,1);
    glTranslatef(3.0,0,0.0);
    glutSolidCube(0.4);
    glPopMatrix();

//Solar Panels

    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(3,0,0.0);
    glScaled(3.7,0.0,1);
    glutSolidCube(0.4);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.2,0.1,0.1);
    glTranslatef(3.0,0,-0.4);
    glScaled(0.5,0.5,0.5);
    glutSolidSphere(0.3,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2,0.2,0.1);
    glTranslatef(3.0,0,0.4);
    glScaled(0.4,0.4,0.3);
    glutSolidTorus(0.3,0.2,20,20);
    glPopMatrix();

}

// Second Screen

void sat2(double ang)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-13.0f);
    glRotatef(ang,0.0f,1.0f,0.0f);

//earth

    glPushMatrix();
    glColor3f(0.066, 0.200, 0.933);
    //glutSolidSphere(2.0,50,50);
    glEnable(GL_TEXTURE_2D);
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, 1);

    //glTranslatef(2,00,2);
    gluSphere(quad,2,100,100);

    gluDeleteQuadric(quad);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    satellite();

    glTranslatef(5.0,4,0.0);

    glEnable(GL_TEXTURE_2D);
    GLUquadric *quad1;
    quad1 = gluNewQuadric();
    gluQuadricTexture(quad1, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, 2);
    glColor3f(1,1,1);

    //glTranslatef(2,00,2);
    gluSphere(quad1,0.6,10,10);

    gluDeleteQuadric(quad1);

    glDisable(GL_TEXTURE_2D);

    glFlush();
    glutSwapBuffers();
}

void building(float x1,float y1,float z1)
{

//Main Structure
    glPushMatrix();
    glColor3f(0.180, 0.435, 0.105);
    glTranslatef(x1,y1,z1);
    glScaled(0.5,1.5,0.5);
    glutSolidCube(2);
    glPopMatrix();

//Dish on top
    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(x1,y1+1.8,z1);
    glRotatef(60,1,0,0);
    glScaled(0.5,1.5,0.5);
    glutSolidCone(0.5,1,20,20);
    glPopMatrix();

//windows
    glPushMatrix();
    glColor3f(0.243, 0.937, 0.698);
    glTranslatef(x1-0.2,y1+0.7,z1);
    glScaled(0.5,0.5,0.5);
//glutSolidCube(.3);
    for(float j=-3; j<1.5; j+=.8)
    {
        for(float i=0; i<1; i+=0.8)
        {
            glPushMatrix();
            glTranslatef(i,j,1);
            glutSolidCube(0.4);
            glPopMatrix();
        }
    }
    glPopMatrix();

}

void waves()
{

    glPushMatrix();
    glTranslatef(0,1,0);
    glScaled(0.05,0.5,0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-8,0,0,1);
    glTranslatef(0.01,1,0);
    glScaled(0.05,0.5,0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(8,0,0,1);
    glTranslatef(-0.01,1,0);
    glScaled(0.05,0.6,0.1);
    glutSolidCube(0.5);
    glPopMatrix();

}

void sat1()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-13.0f);
//glRotatef(x,0.0f,1.0f,0.0f);

//Moon
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-3.8,2.8,0);
    glScaled(0.5,0.5,0.1);
    //glutSolidSphere(0.6,50,50);


    glEnable(GL_TEXTURE_2D);
    GLUquadric *quad1;
    quad1 = gluNewQuadric();
    gluQuadricTexture(quad1, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, 2);
    glColor3f(1,1,1);

    //glTranslatef(2,00,2);
    gluSphere(quad1,1.6,30,30);

    gluDeleteQuadric(quad1);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

//Earth
    glPushMatrix();
    glColor3f(0.039, 0.698, 0.098);
    glTranslatef(0,-12,0);
    //glutSolidSphere(10.0,50,50);

    glEnable(GL_TEXTURE_2D);
    GLUquadric *quad2;
    quad2 = gluNewQuadric();
    gluQuadricTexture(quad2, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, 1);
    glColor3f(1,1,1);

    //glTranslatef(2,00,2);
    glRotatef(90,1,0,0);
    gluSphere(quad2,10,50,50);

    gluDeleteQuadric(quad2);

    glDisable(GL_TEXTURE_2D);


    glPopMatrix();

//Building Center
    glPushMatrix();
    glColor3f(0.1, 0.6, 0.8);
    glRotatef(10,1,0,0);
    building(1.2,-1.2,3.2);
    glPopMatrix();

//Building left
    glPushMatrix();
    glColor3f(0.121, 0.698, 0.196);
    glRotatef(5,0,0,1);
    building(-3.8,-1.2,0);
    glPopMatrix();

//signal
    glPushMatrix();
    glColor3f(0,0,1);

    if(transmit)
    {
        glRotatef(-25,0,0,1);
        glTranslatef(-1.25,-1.6+w1,0);
    }
    else glTranslatef(1,20,3.3);
    waves();

    glPopMatrix();

//Main Dish
//Tower
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-1,-2,4);
    glRotatef(270,1,0,0);
    glScaled(1.0,1,2.0);
    glutWireCone(0.5,1,4,10);
    glPopMatrix();

//Dish
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-1.08,0.2,3);
    glRotatef(60,1,0,0);
    glScaled(0.7,1.3,0.7);
    glutSolidCone(0.4,0.5,20,20);
    glPopMatrix();

//Building right
    glPushMatrix();
    glColor3f(0.894, 0.035, 0.027);
    glRotatef(-5,0,0,1);
    building(3.8,-1.2,0);
    glPopMatrix();

//Saltellite

    glPushMatrix();
    glTranslatef(-4.5,4.0,0);
    glScalef(1.5,2,1.5);
    satellite();
    glPopMatrix();

//Ack to right building
    glPushMatrix();
    if(transmit)
    {
        glRotatef(50,0,0,1);
        glTranslatef(2.8,3.2-w2,0);
    }
    else glTranslatef(1,20,3.3);
    waves();

    glPopMatrix();

//Ack to Left building
    glPushMatrix();
    if(transmit)
    {
        glRotatef(-50,0,0,1);
        glTranslatef(-2.8,3.2-w2,0);
    }
    else glTranslatef(1,20,3.3);
    waves();

    glPopMatrix();

//Ack to Center building
    glPushMatrix();
    if(transmit)
    {
        glRotatef(23,0,0,1);
        glTranslatef(1,3.2-w3,3.3);
    }
    else glTranslatef(1,20,3.3);
    waves();

    glPopMatrix();

//stars
    glPushMatrix();
    glTranslatef(-10,-10,0);
    glPointSize(1);
    for(int j=0; j<100; j++)
    {
        for(int i=0; i<100; i++)
        {
            rx[j]=rand()/500;
            ry[i]=rand()/500;

            glBegin(GL_POINTS);
            glColor3f(0,2,2);
            glVertex3f(-6+rx[j],ry[i],-5);
            glEnd();

        }
    }
    glPopMatrix();

//    glPushMatrix();
//
//    glTranslatef(0.0,0.0,-2.0);
//    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
//    glColor3f(1,1,1);
//    drawstring(1,3.7,-1.0,"SATELITE");
//    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
//    glColor3f(1,1,1);
//    drawstring(-4.4,.5,-1.0,"RECEIVER");
//    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
//    glColor3f(1,1,0);
//    drawstring(0,-2,7,"RECEIVER");
//    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
//    glColor3f(1,1,1);
//    drawstring(-1.5,-1,-1.0,"TRANSMITTER");
//    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
//    glColor3f(1,1,1);
//    drawstring(3.2,1,3,"RECEIVER");
//    glPopMatrix();

    glFlush();
    glutSwapBuffers();

}
// Third Screen

//void sat3(double ang)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    glTranslatef(0.0f,0.0f,-13.0f);
//    glRotatef(ang,0.0f,1.0f,0.0f);
//
////earth
//    glPushMatrix();
//    glColor3f(0.3,0.9,1);
//
//    glutSolidSphere(2.0,50,50);
//    glPopMatrix();
//
//    satellite();
//
//    glFlush();
//    glutSwapBuffers();
//}
void e()
{

    x-=1;
    sat2(x);
}

void s()
{

    x-=0.5;
    sat2(x);

}

void S()
{
    x += .07;
    if(transmit)
    {
        if(w1<=4.2)
            w1+=0.02;

        if(w1>=2.5 && w2<=6.9)
            w2+=0.02;

        if(w1>=2.5 && w3<=5)
            w3+=0.02;
    }

    sat1();

}

void doInit()
{

    /* Background and foreground color */
    glClearColor(0.0,0.0,0.0,0);
    glViewport(0,0,640,480);
    /* Select the projection matrix and reset it then
    setup our view perspective */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(30.0f,(GLfloat)640/(GLfloat)480,0.1f,200.0f);
    glFrustum(-30,30,-30,30,0.1,100);
    gluLookAt(eyex, eyey, eyez,  centerx,centery,centerz,   upx,upy,upz);

    /* Select the modelview matrix, which we alter with rotatef() */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable( GL_COLOR_MATERIAL );

    glDepthFunc(GL_LEQUAL);
}







double limit = 360;
double roll_value = 5;
GLfloat angleYaw = 90.0, anglePitch = 90.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 180.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 0.0, angleRollLimit2 = -90.0;
int f=0;
double scale_x = 1;
double scale_y = 1;
double scale_z = 1;
int bv = 0;



void b_swap()
{
    //if(bv==1)
  //  {
        int tmp = eyey;
        eyey = eyez;
        eyez = tmp;

        tmp = upy;
        upy = upz;
        upz = tmp;
   // }
}

void setCameraEye_Yaw() /// y axis , y u
{

    centerx = eyex+radius*(cos(angleYaw*3.1416/180.0));
    centerz = eyez+radius*(sin(angleYaw*3.1416/180.0));

//    eyex = 200.0*(cos(angleYaw*3.1416/180.0));//-sin(anglePitch*3.1416/180.0));
//    eyez = 200.0*(sin(angleYaw*3.1416/180.0));//+cos(anglePitch*3.1416/180.0));
}

void setCameraEye_Roll() // z axis ,i o
{
    upx = (cos(angleRoll*3.1416/180.0));//-sin(angleYaw*3.1416/180.0));
    upy = (sin(angleRoll*3.1416/180.0));//+cos(angleYaw*3.1416/180.0));

}

void setCameraEye_Pitch() // x axis , r t
{

    centery = eyey+radius*(cos(anglePitch*3.1416/180.0));
    centerz = eyez+radius*(sin(anglePitch*3.1416/180.0));
}


int ch =1;

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glClearColor(0.0,0.0,0.0,0);
    glViewport(0,0,1000,600);
    /* Select the projection matrix and reset it then
    setup our view perspective */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f,(GLfloat)640/(GLfloat)480,0.1f,200.0f);
    //glFrustum(-30,30,-30,30,0.1,100);
    gluLookAt(eyex, eyey, eyez,  centerx,centery,centerz,   upx,upy,upz);

    /* Select the modelview matrix, which we alter with rotatef() */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable( GL_COLOR_MATERIAL );

    glDepthFunc(GL_LEQUAL);
    glTranslatef(0.0f,0.0f,-12.0f);
    stroke_output(-2.0, 1.7, "Press Z--> Start");
    stroke_output(-2.0, 0.9, "Press X--> Transmit");
    stroke_output(-2.0, 0.0, "Press Q--> Quit");
    stroke_output(-2.0,-1.0, "InfO:");
    stroke_output(-2.0,-1.5, "Imran Hossain  1707072");


    GLfloat mat_ambient[]= {0.0f,1.0f,2.0f,1.0f};
    GLfloat mat_diffuse[]= {0.0f,1.5f,.5f,1.0f};
    GLfloat mat_specular[]= {5.0f,1.0f,1.0f,1.0f};
    GLfloat mat_shininess[]= {50.0f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

    GLfloat lightIntensity[]= {1.7f,1.7f,1.7f,1.0f};
    GLfloat light_position3[]= {0.0f,8.0f,10.0f,0.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,light_position3);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

    GLfloat lightIntensity1[]= {1.7f,1.7f,1.7f,1.0f};
    GLfloat light_position31[]= {-2.0f,8.0f,10.0f,0.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light_position31);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,lightIntensity1);

    glEnable(GL_COLOR_MATERIAL);

    glScalef(100,100,100);
    //sat1();

    glFlush();

    glutSwapBuffers();

   // glutPostRedisplay();

}

void menu(int id)
{
    switch(id)
    {
    case 1:
        glutIdleFunc(S);
        break;
    case 2:
        glutIdleFunc(s);
        break;

    case 5:
        exit(0);
        break;
    }
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}


#include<bits/stdc++.h>
using namespace std;

void mykey(unsigned char key,int x,int y)
{
    switch (key)
    {
    case 'w':
        eyez+=5;
        centerz+=5;
        cout<<"call p"<<endl;
        glutPostRedisplay();

        break;
    case 'e':

        eyez-=5;
        centerz-=5;
        cout<<"call e"<<endl;
        glutPostRedisplay();

        break;

    case 'r':
//        if(anglePitch>=anglePitchLimit1)
//                break;
        anglePitch += roll_value;
        cout<<"call pitch"<<endl;

        //printf("%lf  p\n ", anglePitch);
        //if(anglePitch > limit)
        //    anglePitch -= limit;
        setCameraEye_Pitch();
        glutPostRedisplay();

        // eyex = eyex;

        break;
    case 't':
//        if(anglePitch<=anglePitchLimit2)
//                break;
        anglePitch -= roll_value;
        //if(anglePitch < 0)
        //   anglePitch += limit;
        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'y':
//        if(angleYaw==angleYawLimit1)
//            break;
        angleYaw += roll_value;
        //if(angleYaw > limit)
        //    angleYaw -= limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'u':
//        if(angleYaw==angleYawLimit2)
//            break;
        angleYaw -= roll_value;
        //if(angleYaw < 0)
        //   angleYaw += limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'i':
        //if(angleRoll>=angleRollLimit1)
        //   break;
        angleRoll += roll_value;
        //if(angleRoll >= limit)
        //    angleRoll -= limit;
        printf("%lf\n", angleRoll);
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'o':
        //if(angleRoll<=angleRollLimit2)
        //   break;
        angleRoll -= roll_value;
        //if(angleRoll < 0)
        //    angleRoll += limit;
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;

    case 'b':
        //if(angleRoll<=angleRollLimit2)
        //   break;
       b_swap();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;

    case 's':
       // glutIdleFunc(s);
        break;
    case 'S':
       // glutIdleFunc(S);
        break;
    case 'a':
        eyex-=2;
        centerx-=2;
        glutPostRedisplay();
        break;
    case 'd':
        eyex+=2;
        centerx+=2;
        glutPostRedisplay();
        break;

    case 'f':
        eyey+=2;
        centery+=2;
        glutPostRedisplay();
        break;
    case 'g':
        eyey-=2;
        centery-=2;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        //glutIdleFunc(S);
        break;
    case 'x':
        glutIdleFunc(S);
        //exit(0);
        //glutIdleFunc(S);
        break;
    case 'z':
        glutIdleFunc(e);
        //exit(0);
        //glutIdleFunc(S);
        break;

    case 'T':
         transmit=!transmit;
        if(!transmit)
        {
            w1=0;
            w2=0;
            w3=0;

        }
        glutIdleFunc(S);
        break;

    case '1':
        glEnable(GL_LIGHT0);
        break;
    case '2':
        glDisable(GL_LIGHT0);
        break;

    case '3':
        glEnable(GL_LIGHT1);
        break;
    case '4':
        glDisable(GL_LIGHT1);
        break;


    }

    return;

    if(key=='S')
    {
        glutIdleFunc(S);
    }

    if(key=='e')
    {
        glutIdleFunc(e);
    }
    if(key=='t')

    {
        transmit=!transmit;
        if(!transmit)
        {
            w1=0;
            w2=0;
            w3=0;

        }
        glutIdleFunc(S);
    }

    if(key=='q'||key=='Q')
    {
        exit(0);
    }

    if(key==27)
    {
        exit(0);
    }

}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Working of a Satellite");
    glutDisplayFunc(display);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glutKeyboardFunc(mykey);
    glutCreateMenu(menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    LoadTexture1("C:\\Users\\ADMIN\\Desktop\\ghfinal\\earth.bmp");
    LoadTexture1("C:\\Users\\ADMIN\\Desktop\\ghfinal\\moon.bmp");
    //doInit();
    glutMainLoop();
    return 0;
}
