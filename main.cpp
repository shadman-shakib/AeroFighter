#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

#include<GL\glut.h>
#include <GL/glu.h>


#define PI 3.1416

GLint i, j, k;
GLfloat sun_spin=0, sun_x=0, sun_y=0;
GLfloat ax=0,bx=0,cx=0,dx=0,str=500.0,mn=500.0;
GLfloat sr=0.0,sg=0.749,sb=1.0;
GLfloat spin = 0.0;
bool endgame=false;
bool startgame=true;


double cameraHeight;
double cameraAngle;
int bullet=0;
int drawgrid;
int drawaxes;
float pl_x=-3;
float pl_y=3;
//float recv;

float game_score=0;

float xx=-90;   //collision dection
float yy=0;


float aa=7;   //collision dection
float bb=-2.5;





float pl_x1=-6;
float pl_y1=6;
float pl_x2=-3;
float pl_y2=3;
bool guli_marmu = false;
double guli_array_x [10000000]= {0};
double guli_array_y [10000000]= {0};
float sender;
float senderx;
float senderxx;
float senderr;
float sendery;
float senderyy;

float sender3;
float sender4;
float sender5;
float sender6;

float pl_x_airfighter=-100;
float pl_y_airfighter=7;

float pl_x_airfighter1=20;
float pl_y_airfighter1=7;

float pl_x_airfighter2=50;
float pl_y_airfighter2=30;
float pl_x_airfighter3=60;
float pl_y_airfighter3=60;
//float pl_x_airfighter1=20;
//float pl_y_airfighter1=7;

double angle;
double angle_c_z=0;
double angle_c_x=0, angle_t_x=0, angle_t_z=0;
double limit=0.0;


struct point
{
    double x,y,z;
};

struct point pos,l,u,r;
double X=0,Z=0;
int Y=-1;
struct point arra[100];



void print(int x, int y,int z, char *string)
{
//set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x,y);
//get the length of the string to display
    int len = (int) strlen(string);

//loop to display character by character
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
    }
}


void circle(GLdouble rad)
{
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    {
        for(i = 0; i <=50; i++, theta += delTheta )
        {
            glVertex2f(rad * cos(theta),rad * sin(theta));
        }
    }
    glEnd();
}
void drawAxes()
{
    if(drawaxes==1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glColor3f(0.0f,1.0f,0.0f);
            glVertex3f( 1000,0,0);
            glVertex3f(-1000,0,0);

            glColor3f(0.0f,0.0f,1.0f);
            glVertex3f(0,-1000,0);
            glVertex3f(0, 1000,0);

            glColor3f(0.0f,0.0f,1.0f);
            glVertex3f(0,0, 1000);
            glVertex3f(0,0,-1000);
        }
        glEnd();
    }
}

void drawGrid()
{
    int i;
    if(drawgrid==1)
    {
        glColor3f(0.6, 0.6, 0.6);	//grey
        glBegin(GL_LINES);
        {
            for(i=-8; i<=8; i++)
            {

                if(i==0)
                    continue;	//SKIP the MAIN axes

                //lines parallel to Y-axis
                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);

                //lines parallel to X-axis
                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }
        glEnd();
    }
}
void  guli_move()
{

    pl_x2+=.1f;
    if(pl_x2 > 180)
    {
        pl_x2 =-10;
        //pl_y1 =0;

    }

}


void start_game()
{
    print(-14,20,0,"AERO FIGHTERS!");

    print(-20,6,0,"Press [P] to start The GAME!");
    print(-14,-5,0,"..................................");

    print(-8,-15,0,"Instruction!");

    print(-50,-25,0,"Use UP, DOWN, LEFT and RIGHT arrow to move the friendly aircraft. ");



}
void  gulijacche(double x)
{
    //glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    {
        glVertex2f(pl_x2, pl_y2);
        glVertex2f(pl_x2+4, pl_y2);
        glVertex2f(pl_x2+4, pl_y2-1);
        glVertex2f(pl_x2, pl_y2-1);
    }

    guli_move();
    glEnd();
}

void create_guli(double x,double y)
{
    glBegin(GL_POLYGON);
    {
        glVertex2f(x, y);
        glVertex2f(x+4, y);
        glVertex2f(x+4, y-1);
        glVertex2f(x, y-1);
    }

    x+=.1f;
    if(x > 180)
    {
        x =-10;
        //pl_y1 =0;

    }
    glEnd();
    glFlush();
}
void draw_circle_line(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    glBegin(GL_LINES);
    {
        for(i=0; i<segments; i++)
        {

            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);

        }
    }
    glEnd();
}


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    glBegin(GL_POLYGON);
    {
        for(i=0; i<segments; i++)
        {

            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);

        }
    }
    glEnd();
}

void draw_cylinder(double radius,double height,int segments)
{
    int i;
    struct point points[2][100];
    for(i=0; i<=segments; i++)
    {
        points[0][i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[0][i].y=radius*sin(((double)i/(double)segments)*2*pi);
        points[0][i].z=0;
        points[1][i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[1][i].y=radius*sin(((double)i/(double)segments)*2*pi);
        points[1][i].z=height;
    }

    for (i=0; i<segments; i++)
    {
        glBegin(GL_QUADS);
        {
            //upper hemisphere
            glColor3f((i)%2,.5,(i)%2);
            glVertex3f(points[0][i].x,points[0][i].y,points[0][i].z);
            glVertex3f(points[0][i+1].x,points[0][i+1].y,points[0][i+1].z);
            glVertex3f(points[1][i+1].x,points[1][i+1].y,points[1][i+1].z);
            glVertex3f(points[1][i].x,points[1][i].y,points[1][i].z);

        }
        glEnd();


    }
}
void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0; i<int(segments-limit); i++)
    {
        //create shading effect
        if(i<segments/2)
            shade=2*(double)i/(double)segments;
        else
            shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,0,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawSphere(double radius,int slices,int stacks)
{
    struct point points[100][100];
    int i,j;
    double h,r;
    //generate points
    for(i=0; i<=stacks; i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));
        r=radius*cos(((double)i/(double)stacks)*(pi/2));
        for(j=0; j<=slices; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }
    }
    //draw quads using generated points
    for(i=0; i<stacks; i++)
    {
        glColor3f((double)i/(double)stacks,1,(double)i/(double)stacks);
        for(j=0; j<slices; j++)
        {
            glBegin(GL_LINE_LOOP);
            {
                //upper hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
            }
            glEnd();



            glBegin(GL_LINE_LOOP);
            {
                //upper hemisphere

                //lower hemisphere

                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);



            }
            glEnd();















        }
    }
}


void quad()
{
    // Draw A Quad
    glBegin(GL_QUADS);

    glColor3f(1.0f,0.0f,1.0f);
    glVertex3f(1.0f,1.0f,8.0f);					    // Top front Of The Quad (right)
    glVertex3f(1.0f,1.0f,1.0f);					    // Top back Of The Quad (right)
    glVertex3f(1.0f,-1.0f,1.0f);					// Bottom back Of The Quad (right)
    glVertex3f(1.0f,-1.0f,8.0f);					// Bottom front Of The Quad (right)

    glColor3f(1.0f,1.0f,0.0f);
    glVertex3f(-1.0f,1.0f,8.0f);					// Top front Of The Quad (left)
    glVertex3f(-1.0f,1.0f,1.0f);					// Top back Of The Quad (left)
    glVertex3f(-1.0f,-1.0f,1.0f);					// Bottom back Of The Quad (left)
    glVertex3f(-1.0f,-1.0f,8.0f);					// Bottom front Of The Quad (left)


    glColor3f(0.0f,0.0f,0.0f);
    glVertex3f(1.0f,1.0f,8.0f);					    // Right front Of The Quad (top)
    glVertex3f(1.0f,1.0f,1.0f);					    // Right back Of The Quad (top)
    glVertex3f(-1.0f,1.0f,1.0f);				    // Left back Of The Quad (top)
    glVertex3f(-1.0f,1.0f,8.0f);				    // Left front Of The Quad (top)


    glColor3f(0.0f,1.0f,1.0f);
    glVertex3f(1.0f,-1.0f,8.0f);					// Right front Of The Quad (bottom)
    glVertex3f(1.0f,-1.0f,1.0f);					// Right back Of The Quad (bottom)
    glVertex3f(-1.0f,-1.0f,1.0f);				    // Left back Of The Quad (bottom)
    glVertex3f(-1.0f,-1.0f,8.0f);				    // Left front Of The Quad (bottom)


    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(1.0f,1.0f,1.0f);					 // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,1.0f,1.0f);					// Top Left Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,1.0f);					// Bottom Left Of The Quad (Back)
    glVertex3f(1.0f,-1.0f,1.0f);					// Bottom Right Of The Quad (Back)


    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(1.0f,1.0f,8.0f);					    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f,1.0f,8.0f);					// Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f,8.0f);					// Bottom Left Of The Quad (Front)
    glVertex3f(1.0f,-1.0f,8.0f);			// Bottom Right Of The Quad (Front)

    glEnd();
}

void castle()
{







    glPushMatrix();
    glTranslatef(-1,1,1);
    glRotatef(90,0,1,0);
    draw_cylinder(.5,2,40);
    glPopMatrix();







    //...............................


    glPushMatrix();
    glTranslatef(-1,-1,1);
    glRotatef(90,0,1,0);
    draw_cylinder(.5,2,40);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-1,1,8);
    glRotatef(90,0,1,0);
    draw_cylinder(.5,2,40);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,-1,8);
    glRotatef(90,0,1,0);
    draw_cylinder(.5,2,40);
    glPopMatrix();




    glPushMatrix();






    glTranslatef(-1,-1,1);
    glRotatef(-90,0,1,0);
    drawCone(.5,2,20);



    glPopMatrix();

    glPushMatrix();

    glTranslatef(-1,1,1);
    glRotatef(-90,0,1,0);
    drawCone(.5,2,20);



    glPopMatrix();

    glPushMatrix();

    glTranslatef(-1,-1,8);
    glRotatef(-90,0,1,0);
    drawCone(.5,2,20);



    glPopMatrix();




    glPushMatrix();

    glTranslatef(-1,1,8);
    glRotatef(-90,0,1,0);
    drawCone(.5,2,20);



    glPopMatrix();















}

void rocket()
{










    glPushMatrix();



    draw_cylinder(1,5,50);



    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,0,5);
    glRotatef(0,0,1,0);
    drawCone(1,3,40);



    glPopMatrix();

    glPushMatrix();
    //  glColor3f(0.0f,1.0f,1.0f);
    glTranslatef(0,0,1.5);
    glScalef(.09,6,.2);

    quad();

    glPopMatrix();




    glPushMatrix();

    glTranslatef(0,6,1.5);

    draw_cylinder(.5,2,50);



    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,-6,1.5);

    draw_cylinder(.5,2,50);



    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,6,3.5);
    glRotatef(0,0,1,0);
    drawCone(.5,2,40);



    glPopMatrix();


    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,-6,3.5);
    glRotatef(0,0,1,0);
    drawCone(.5,2,40);



    glPopMatrix();


    glPushMatrix();
    //  glColor3f(0.0f,1.0f,1.0f);
    glTranslatef(-2,0,0);
    glScalef(1,.08,.2);

    quad();

    glPopMatrix();





    glPushMatrix();

    glTranslatef(-3,0,0);

    draw_cylinder(.5,2,50);



    glPopMatrix();

    glPushMatrix();

    glTranslatef(-3,0,2);
    glRotatef(0,0,1,0);
    drawCone(.5,2,40);



    glPopMatrix();


    glPushMatrix();
    // glRotatef(angle,0,0,1);
    glTranslatef(60,0,0);
    glRotatef(2*angle,1,0,0);
    glColor3f(0,1,0);
    //drawSphere(7,15,15);

    glScalef(.09,.09,.2);

    quad();



    //glPushMatrix();
    // glRotatef(angle,0,0,1);
    // glTranslatef(130,0,0);
    // glRotatef(2*angle,0,0,1);
    //glColor3f(0,1,0);
    // drawSphere(7,15,15);
    // glPopMatrix();












    glPopMatrix();









    glPushMatrix();
    //  glColor3f(0.0f,1.0f,1.0f);

    glRotatef(-90,0,1,0);
    glTranslatef(8,0,-1);
    //  glRotatef(angle,1,0,0);
    glScalef(.09,.09,.2);

    quad();

    glPopMatrix();

















}

void movement3D()
{
    draw_circle_line(110,40);
    glColor3f(1,0,0);
    drawSphere(20,30,30);










    // glPushMatrix();
    // glColor3f(1,0,1);
    // glRotatef(angle,0,1,0);
    //draw_circle_line(110,40);
    // glTranslatef(110,0,0);
    // glRotatef(2*angle,0,0,1);
    // glColor3f(0,1,0);
    // drawSphere(15,30,30);

    // glPopMatrix();










    glPushMatrix();
    // glRotatef(angle,0,0,1);
    glTranslatef(60,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSphere(7,15,15);





    //glPushMatrix();
    // glRotatef(angle,0,0,1);
    // glTranslatef(130,0,0);
    // glRotatef(2*angle,0,0,1);
    //glColor3f(0,1,0);
    // drawSphere(7,15,15);
    // glPopMatrix();












    glPopMatrix();













}
void drawSS()
{
    draw_circle_line(110,40);
    glColor3f(1,0,0);
    drawSphere(20,30,30);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSphere(15,30,30);;

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSphere(10,30,30);;
    }
    glPopMatrix();
    glColor3f(1,1,1);

    /*glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);*/
}


void enemy()
{
    glColor3f(1.0,0.0,1.0);

    glBegin(GL_POLYGON);
    {
        //glVertex2f( pl_x, pl_y);
        //glVertex2f( pl_x+6, pl_y);
        //glVertex2f(pl_x+6, pl_y-3);
        //glVertex2f(pl_x, pl_y-3);


        glVertex2f(pl_x_airfighter1+103,pl_y_airfighter1-7);  //4,0
        glVertex2f(pl_x_airfighter1+104,pl_y_airfighter1-3);   //4,4
        glVertex2f(pl_x_airfighter1+101.5,pl_y_airfighter1-5.5); //1.5,1.5
        glVertex2f(pl_x_airfighter1+98,pl_y_airfighter1-5);    //-2,2

        glVertex2f(pl_x_airfighter1+96,pl_y_airfighter1-7);  //-4,0
        glVertex2f(pl_x_airfighter1+98,pl_y_airfighter1-9);  //-2,-2

        glVertex2f(pl_x_airfighter1+101.5,pl_y_airfighter1-8.5); //1.5,-1.5




        glVertex2f(pl_x_airfighter1+104,pl_y_airfighter1-11);  //-6,-4


        glVertex2f(pl_x_airfighter1+103,pl_y_airfighter1-7);   //4,0




        senderx=pl_x_airfighter1+104;
        sendery=pl_y_airfighter1-3;













    }
    glEnd();
}

void enemy2()
{
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_POLYGON);
    {
        //glVertex2f( pl_x, pl_y);
        //glVertex2f( pl_x+6, pl_y);
        //glVertex2f(pl_x+6, pl_y-3);
        //glVertex2f(pl_x, pl_y-3);


        glVertex2f(pl_x_airfighter2+103,pl_y_airfighter2-7);  //4,0
        glVertex2f(pl_x_airfighter2+104,pl_y_airfighter2-3);   //4,4
        glVertex2f(pl_x_airfighter2+101.5,pl_y_airfighter2-5.5); //1.5,1.5
        glVertex2f(pl_x_airfighter2+98,pl_y_airfighter2-5);    //-2,2

        glVertex2f(pl_x_airfighter2+96,pl_y_airfighter2-7);  //-4,0
        glVertex2f(pl_x_airfighter2+98,pl_y_airfighter2-9);  //-2,-2

        glVertex2f(pl_x_airfighter2+101.5,pl_y_airfighter2-8.5); //1.5,-1.5




        glVertex2f(pl_x_airfighter2+104,pl_y_airfighter2-11);  //-6,-4


        glVertex2f(pl_x_airfighter2+103,pl_y_airfighter2-7);   //4,0




        sender5=pl_x_airfighter2+104;
        sender6=pl_y_airfighter2-3;













    }
    glEnd();
}

void enemy3()
{
    glColor3f(0.0,1.0,1.0);

    glBegin(GL_POLYGON);
    {
        //glVertex2f( pl_x, pl_y);
        //glVertex2f( pl_x+6, pl_y);
        //glVertex2f(pl_x+6, pl_y-3);
        //glVertex2f(pl_x, pl_y-3);


        glVertex2f(pl_x_airfighter3+103,pl_y_airfighter3-7);  //4,0
        glVertex2f(pl_x_airfighter3+104,pl_y_airfighter3-3);   //4,4
        glVertex2f(pl_x_airfighter3+101.5,pl_y_airfighter3-5.5); //1.5,1.5
        glVertex2f(pl_x_airfighter3+98,pl_y_airfighter3-5);    //-2,2

        glVertex2f(pl_x_airfighter3+96,pl_y_airfighter3-7);  //-4,0
        glVertex2f(pl_x_airfighter3+98,pl_y_airfighter3-9);  //-2,-2

        glVertex2f(pl_x_airfighter3+101.5,pl_y_airfighter3-8.5); //1.5,-1.5




        glVertex2f(pl_x_airfighter3+104,pl_y_airfighter3-11);  //-6,-4


        glVertex2f(pl_x_airfighter3+103,pl_y_airfighter3-7);   //4,0




        sender3=pl_x_airfighter3+104;
        sender4=pl_y_airfighter3-3;













    }
    glEnd();
}
void enemy4()
{
    glColor3f(1.0,0.0,1.0);

    glBegin(GL_POLYGON);
    {
        //glVertex2f( pl_x, pl_y);
        //glVertex2f( pl_x+6, pl_y);
        //glVertex2f(pl_x+6, pl_y-3);
        //glVertex2f(pl_x, pl_y-3);


        glVertex2f(pl_x_airfighter1+103,pl_y_airfighter1-7);  //4,0
        glVertex2f(pl_x_airfighter1+104,pl_y_airfighter1-3);   //4,4
        glVertex2f(pl_x_airfighter1+101.5,pl_y_airfighter1-5.5); //1.5,1.5
        glVertex2f(pl_x_airfighter1+98,pl_y_airfighter1-5);    //-2,2

        glVertex2f(pl_x_airfighter1+96,pl_y_airfighter1-7);  //-4,0
        glVertex2f(pl_x_airfighter1+98,pl_y_airfighter1-9);  //-2,-2

        glVertex2f(pl_x_airfighter1+101.5,pl_y_airfighter1-8.5); //1.5,-1.5




        glVertex2f(pl_x_airfighter1+104,pl_y_airfighter1-11);  //-6,-4


        glVertex2f(pl_x_airfighter1+103,pl_y_airfighter1-7);   //4,0




        senderx=pl_x_airfighter1+104;
        sendery=pl_y_airfighter1-3;













    }
    glEnd();
}

void guli()
{
    //glColor3f(1.0,0.0,0.0);

    glBegin(GL_QUADS);
    {
        glVertex2f( pl_x1, pl_y1);
        glVertex2f( pl_x1+1, pl_y1);
        glVertex2f(pl_x1+1, pl_y1-1);
        glVertex2f(pl_x1, pl_y1-1);
    }
    glEnd();
}

void matha()
{
    //glColor3f(1.0,0.0,0.0);
    //glVertex2f( pl_x, pl_y);
    //glVertex2f( pl_x+6, pl_y);
    //glVertex2f(pl_x+6, pl_y-3);
    //glVertex2f(pl_x, pl_y-3);

}
void circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);
    {
		for(i = 0; i < 100; i++)
		{
			angle = 2 * 3.1416 * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

    }

	glEnd();
}
void building()
{

    glPushMatrix();
    glColor3f(0.7,0.7,0.7);
     circle(5,9);
     glPopMatrix();



    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10+8,-50+25-15-15-15-15); //*
    glVertex2f(75+8+10+8,-50+25-15-15-15-15);
    glVertex2f(75+8+10+8,-59+25-15-15-15-15);
    glVertex2f(70+8+10+8,-59+25-15-15-15-15);
    glEnd();
    glPopMatrix();


    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10+8,-50+25-15-15-15); //*
    glVertex2f(75+8+10+8,-50+25-15-15-15);
    glVertex2f(75+8+10+8,-59+25-15-15-15);
    glVertex2f(70+8+10+8,-59+25-15-15-15);
    glEnd();
    glPopMatrix();



    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10+8,-50+25-15-15); //*
    glVertex2f(75+8+10+8,-50+25-15-15);
    glVertex2f(75+8+10+8,-59+25-15-15);
    glVertex2f(70+8+10+8,-59+25-15-15);
    glEnd();
    glPopMatrix();


    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10+8,-50+25-15); //*
    glVertex2f(75+8+10+8,-50+25-15);
    glVertex2f(75+8+10+8,-59+25-15);
    glVertex2f(70+8+10+8,-59+25-15);
    glEnd();
    glPopMatrix();



    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10+8,-50+25); //*
    glVertex2f(75+8+10+8,-50+25);
    glVertex2f(75+8+10+8,-59+25);
    glVertex2f(70+8+10+8,-59+25);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10,-50+25); //*
    glVertex2f(75+8+10,-50+25);
    glVertex2f(75+8+10,-59+25);
    glVertex2f(70+8+10,-59+25);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10,-50+25-15); //*
    glVertex2f(75+8+10,-50+25-15);
    glVertex2f(75+8+10,-59+25-15);
    glVertex2f(70+8+10,-59+25-15);
    glEnd();
    glPopMatrix();



    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10,-50+25-15-15); //*
    glVertex2f(75+8+10,-50+25-15-15);
    glVertex2f(75+8+10,-59+25-15-15);
    glVertex2f(70+8+10,-59+25-15-15);
    glEnd();
    glPopMatrix();


    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10,-50+25-15-15-15); //*
    glVertex2f(75+8+10,-50+25-15-15-15);
    glVertex2f(75+8+10,-59+25-15-15-15);
    glVertex2f(70+8+10,-59+25-15-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8+10,-50+25-15-15-15-15); //*
    glVertex2f(75+8+10,-50+25-15-15-15-15);
    glVertex2f(75+8+10,-59+25-15-15-15-15);
    glVertex2f(70+8+10,-59+25-15-15-15-15);
    glEnd();
    glPopMatrix();


    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8,-50+25-15-15-15-15); //*
    glVertex2f(75+8,-50+25-15-15-15-15);
    glVertex2f(75+8,-59+25-15-15-15-15);
    glVertex2f(70+8,-59+25-15-15-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8,-50+25-15-15-15); //*
    glVertex2f(75+8,-50+25-15-15-15);
    glVertex2f(75+8,-59+25-15-15-15);
    glVertex2f(70+8,-59+25-15-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8,-50+25-15-15); //*
    glVertex2f(75+8,-50+25-15-15);
    glVertex2f(75+8,-59+25-15-15);
    glVertex2f(70+8,-59+25-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8,-50+25-15); //*
    glVertex2f(75+8,-50+25-15);
    glVertex2f(75+8,-59+25-15);
    glVertex2f(70+8,-59+25-15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window Purple building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1, 1, 0);

    glVertex2f(70+8,-50+25); //*
    glVertex2f(75+8,-50+25);
    glVertex2f(75+8,-59+25);
    glVertex2f(70+8,-59+25);
    glEnd();
    glPopMatrix();


    glPushMatrix(); //Purple building
    glTranslatef(25,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.576, 0.439, 0.859);

    glVertex2f(80,-120); //*
    glVertex2f(50,-120);
    glVertex2f(50,-45+5);
    glVertex2f(80,-45+5);
    glEnd();
    glPopMatrix();

    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10-8,-50+5+5+5); //*
    glVertex2f(-75-10-8,-50+5+5+5);
    glVertex2f(-75-10-8,-59+5+5+5);
    glVertex2f(-70-10-8,-59+5+5+5);
    glEnd();
    glPopMatrix();


    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10-8,-50); //*
    glVertex2f(-75-10-8,-50);
    glVertex2f(-75-10-8,-59);
    glVertex2f(-70-10-8,-59);
    glEnd();
    glPopMatrix();

    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10-8,-50-15); //*
    glVertex2f(-75-10-8,-50-15);
    glVertex2f(-75-10-8,-59-15);
    glVertex2f(-70-10-8,-59-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10-8,-50-15-15); //*
    glVertex2f(-75-10-8,-50-15-15);
    glVertex2f(-75-10-8,-59-15-15);
    glVertex2f(-70-10-8,-59-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10-8,-50-15-15-15); //*
    glVertex2f(-75-10-8,-50-15-15-15);
    glVertex2f(-75-10-8,-59-15-15-15);
    glVertex2f(-70-10-8,-59-15-15-15);
    glEnd();
    glPopMatrix();


    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10,-50-15-15-15); //*
    glVertex2f(-75-10,-50-15-15-15);
    glVertex2f(-75-10,-59-15-15-15);
    glVertex2f(-70-10,-59-15-15-15);
    glEnd();
    glPopMatrix();



    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10,-50-15-15); //*
    glVertex2f(-75-10,-50-15-15);
    glVertex2f(-75-10,-59-15-15);
    glVertex2f(-70-10,-59-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10,-50-15); //*
    glVertex2f(-75-10,-50-15);
    glVertex2f(-75-10,-59-15);
    glVertex2f(-70-10,-59-15);
    glEnd();
    glPopMatrix();



    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10,-50); //*
    glVertex2f(-75-10,-50);
    glVertex2f(-75-10,-59);
    glVertex2f(-70-10,-59);
    glEnd();
    glPopMatrix();



    glPushMatrix();//window PINK building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70-10,-50+15); //*
    glVertex2f(-75-10,-50+15);
    glVertex2f(-75-10,-59+15);
    glVertex2f(-70-10,-59+15);
    glEnd();
    glPopMatrix();



    glPushMatrix(); //window PINK building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70,-50-15-15-15); //*
    glVertex2f(-75,-50-15-15-15);
    glVertex2f(-75,-59-15-15-15);
    glVertex2f(-70,-59-15-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window PINK building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70,-50-15-15); //*
    glVertex2f(-75,-50-15-15);
    glVertex2f(-75,-59-15-15);
    glVertex2f(-70,-59-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window PINK building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70,-50-15); //*
    glVertex2f(-75,-50-15);
    glVertex2f(-75,-59-15);
    glVertex2f(-70,-59-15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window PINK building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70,-50); //*
    glVertex2f(-75,-50);
    glVertex2f(-75,-59);
    glVertex2f(-70,-59);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //window PINK building
    // glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 0.498);

    glVertex2f(-70,-50+15); //*
    glVertex2f(-75,-50+15);
    glVertex2f(-75,-59+15);
    glVertex2f(-70,-59+15);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //pink building
    glTranslatef(-17,20,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 0.078, 0.576);

    glVertex2f(-65-5-10,-100-20); //*
    glVertex2f(-35-5-10,-100-20);
    glVertex2f(-35-5-10,-50+5);
    glVertex2f(-65-5-10,-50+5);
    glEnd();
    glPopMatrix();


    glPushMatrix();// window AQUA building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.502, 0.000, 0.000);

    //*
    glVertex2f(-24+23.5+10,-10-35);
    glVertex2f(-29+23.5+10,-10-35);
    glVertex2f(-29+23.5+10,-20-35);
    glVertex2f(-24+23.5+10,-20-35);
    glEnd();
    glPopMatrix();


    glPushMatrix();// window AQUA building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.502, 0.000, 0.000);

    //*
    glVertex2f(-24+23.5+10,-10-35-15);
    glVertex2f(-29+23.5+10,-10-35-15);
    glVertex2f(-29+23.5+10,-20-35-15);
    glVertex2f(-24+23.5+10,-20-35-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window AQUA building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.502, 0.000, 0.000);

    //*
    glVertex2f(-24+23.5+10,-10-35-15-15);
    glVertex2f(-29+23.5+10,-10-35-15-15);
    glVertex2f(-29+23.5+10,-20-35-15-15);
    glVertex2f(-24+23.5+10,-20-35-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window AQUA building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.502, 0.000, 0.000);

    //*
    glVertex2f(-24+23.5+10,-10-35-15-15-15);
    glVertex2f(-29+23.5+10,-10-35-15-15-15);
    glVertex2f(-29+23.5+10,-20-35-15-15-15);
    glVertex2f(-24+23.5+10,-20-35-15-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window AQUA building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.502, 0.000, 0.000);

    //*
    glVertex2f(-24+23.5,-10-35-15-15-15);
    glVertex2f(-29+23.5,-10-35-15-15-15);
    glVertex2f(-29+23.5,-20-35-15-15-15);
    glVertex2f(-24+23.5,-20-35-15-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window AQUA building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.502, 0.000, 0.000);

    //*
    glVertex2f(-24+23.5,-10-35-15-15);
    glVertex2f(-29+23.5,-10-35-15-15);
    glVertex2f(-29+23.5,-20-35-15-15);
    glVertex2f(-24+23.5,-20-35-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window AQUA building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.502, 0.000, 0.000);

    //*
    glVertex2f(-24+23.5,-10-35-15);
    glVertex2f(-29+23.5,-10-35-15);
    glVertex2f(-29+23.5,-20-35-15);
    glVertex2f(-24+23.5,-20-35-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window AQUA building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.502, 0.000, 0.000);

    //*
    glVertex2f(-24+23.5,-10-35);
    glVertex2f(-29+23.5,-10-35);
    glVertex2f(-29+23.5,-20-35);
    glVertex2f(-24+23.5,-20-35);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    glVertex2f(-24-14,-30-20-20-15-15);
    glVertex2f(-29-14,-30-20-20-15-15);
    glVertex2f(-29-14,-20-20-20-15-15);
    glVertex2f(-24-14,-20-20-20-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    glVertex2f(-24-14-9,-30-20-20-15-15);
    glVertex2f(-29-14-9,-30-20-20-15-15);
    glVertex2f(-29-14-9,-20-20-20-15-15);
    glVertex2f(-24-14-9,-20-20-20-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    glVertex2f(-24-14-10-8,-30-20-20-15-15);
    glVertex2f(-29-14-10-8,-30-20-20-15-15);
    glVertex2f(-29-14-10-8,-20-20-20-15-15);
    glVertex2f(-24-14-10-8,-20-20-20-15-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    glVertex2f(-24-14,-30-20-20-15);
    glVertex2f(-29-14,-30-20-20-15);
    glVertex2f(-29-14,-20-20-20-15);
    glVertex2f(-24-14,-20-20-20-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    glVertex2f(-24-14-9,-30-20-20-15);
    glVertex2f(-29-14-9,-30-20-20-15);
    glVertex2f(-29-14-9,-20-20-20-15);
    glVertex2f(-24-14-9,-20-20-20-15);
    glEnd();
    glPopMatrix();


    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    glVertex2f(-24-14-10-8,-30-20-20-15);
    glVertex2f(-29-14-10-8,-30-20-20-15);
    glVertex2f(-29-14-10-8,-20-20-20-15);
    glVertex2f(-24-14-10-8,-20-20-20-15);
    glEnd();
    glPopMatrix();


    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    glVertex2f(-24-14-10-8,-30-20-20);
    glVertex2f(-29-14-10-8,-30-20-20);
    glVertex2f(-29-14-10-8,-20-20-20);
    glVertex2f(-24-14-10-8,-20-20-20);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    //*
    glVertex2f(-24-14-9,-30-20-20);
    glVertex2f(-29-14-9,-30-20-20);
    glVertex2f(-29-14-9,-20-20-20);
    glVertex2f(-24-14-9,-20-20-20);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window RED building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.502);

    //*
    glVertex2f(-24-14,-30-20-20);
    glVertex2f(-29-14,-30-20-20);
    glVertex2f(-29-14,-20-20-20);
    glVertex2f(-24-14,-20-20-20);
    glEnd();
    glPopMatrix();


    glPushMatrix(); // want to move CAR but it dosen't work
    glTranslatef(0,0,0);
    glPushMatrix();//car wheel 2
    glColor3f(1.000, 1.000, 0);
    glTranslatef(40,-56,0);
    drawCircle(2,4);
    glPopMatrix();


    glPushMatrix();// car wheel 1
    glColor3f(1.000, 1.000,0);
    glTranslatef(49,-56,0);
    drawCircle(2,4);
    glPopMatrix();

    glPushMatrix();// car body
    glTranslatef(2,-5,0);
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 0.000,0);

    glVertex2f(35,-50); //*
    glVertex2f(50,-50);
    glVertex2f(50,-40);
    glVertex2f(35,-40);


    glEnd();
    glPopMatrix();
    glPopMatrix(); // here car making code ended

    glPushMatrix();// angle piller 2
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.980, 0.604);

    glVertex2f(150/2,-50); //*
    glVertex2f(150/2,-43.5);
    glVertex2f(90/2,-10);
    glVertex2f(90/2,-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// angle piller 1
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.980, 0.604);

    glVertex2f(30/2,-50); //*
    glVertex2f(30/2,-43.5);
    glVertex2f(90/2,-10);
    glVertex2f(90/2,-15);
    glEnd();
    glPopMatrix();

    glPushMatrix();// road middle  color 3
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 0.980, 0.941);

    glVertex2f(120/2,-69);
    glVertex2f(140/2,-69); //*
    glVertex2f(140/2,-67);
    glVertex2f(120/2,-67);
    glEnd();
    glPopMatrix();


    glPushMatrix();// road middle  color 2
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 0.980, 0.941);

    glVertex2f(80/2,-69);
    glVertex2f(100/2,-69); //*
    glVertex2f(100/2,-67);
    glVertex2f(80/2,-67);
    glEnd();
    glPopMatrix();

    glPushMatrix();// road middle  color
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 0.980, 0.941);

    glVertex2f(40/2,-69);
    glVertex2f(60/2,-69); //*
    glVertex2f(60/2,-67);
    glVertex2f(40/2,-67);
    glEnd();
    glPopMatrix();

    glPushMatrix();// road
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.184, 0.310, 0.310);

    glVertex2f(30/2,-60); //*
    glVertex2f(155/2,-60);
    glVertex2f(155/2,-75);
    glVertex2f(30/2,-75);
    glEnd();
    glPopMatrix();
    glPushMatrix();// river
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0,1,1);

    glVertex2f(20,-110);
    glVertex2f(72,-110); //*
    glVertex2f(45+10,-10-20);
    glVertex2f(25+10,-10-20);
    glEnd();
    glPopMatrix();


    glPushMatrix();// piller 2
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 0.000, 1.000);

    glVertex2f(140/2,-220/2); //*
    glVertex2f(142/2,-220/2);
    glVertex2f(142/2,-5/2);
    glVertex2f(140/2,-5/2);
    glEnd();
    glPopMatrix();


    glPushMatrix();// piller 1
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 0.000, 1.000);

    glVertex2f(40/2,-220/2); //*
    glVertex2f(42/2,-220/2);
    glVertex2f(42/2,-5);
    glVertex2f(40/2,-5);
    glEnd();
    glPopMatrix();

    glPushMatrix();// aqua building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 1.000, 1.000);

    glVertex2f(-18/2,-220/2); //*
    glVertex2f(28/2,-220/2);
    glVertex2f(28/2,-90/2);
    //glVertex2f(-18/2,-90/2);
    glVertex2f(6,-25);
    glVertex2f(-2,-25);
    glVertex2f(-18/2,-90/2);
    glEnd();
    glPopMatrix();

    glPushMatrix(); //red building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 0.000, 0.000);

    glVertex2f(-130/2,-220/2); //*
    glVertex2f(-70/2,-220/2);
    glVertex2f(-70/2,-100/2);
    glVertex2f(-130/2,-100/2);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24,-30-20-20-20);
    glVertex2f(-29,-30-20-20-20);
    glVertex2f(-29,-20-20-20-20);
    glVertex2f(-24,-20-20-20-20);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24+9,-30-20-20-20);
    glVertex2f(-29+9,-30-20-20-20);
    glVertex2f(-29+9,-20-20-20-20);
    glVertex2f(-24+9,-20-20-20-20);
    glEnd();
    glPopMatrix();


    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24+9,-30-20-20);
    glVertex2f(-29+9,-30-20-20);
    glVertex2f(-29+9,-20-20-20);
    glVertex2f(-24+9,-20-20-20);
    glEnd();
    glPopMatrix();


    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24,-30-20-20);
    glVertex2f(-29,-30-20-20);
    glVertex2f(-29,-20-20-20);
    glVertex2f(-24,-20-20-20);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24+9,-30-20-20);
    glVertex2f(-29+9,-30-20-20);
    glVertex2f(-29+9,-20-20-20);
    glVertex2f(-24+9,-20-20-20);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24+9,-30-20);
    glVertex2f(-29+9,-30-20);
    glVertex2f(-29+9,-20-20);
    glVertex2f(-24+9,-20-20);
    glEnd();
    glPopMatrix();


    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24,-30-20);
    glVertex2f(-29,-30-20);
    glVertex2f(-29,-20-20);
    glVertex2f(-24,-20-20);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24+9,-30);
    glVertex2f(-29+9,-30);
    glVertex2f(-29+9,-20);
    glVertex2f(-24+9,-20);
    glEnd();
    glPopMatrix();

    glPushMatrix();// window yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(0.000, 0.000, 0.000);

    //*
    glVertex2f(-24,-30);
    glVertex2f(-29,-30);
    glVertex2f(-29,-20);
    glVertex2f(-24,-20);
    glEnd();
    glPopMatrix();

    glPushMatrix();// yellow building
    glBegin(GL_POLYGON); // DRAWING POLYGON
    glColor3f(1.000, 1.000, 0.000);

    glVertex2f(-20/2,-225/2); //*
    glVertex2f(-68/2,-225/2);
    glVertex2f(-68/2,-20/2);
    glVertex2f(-20/2,-20/2);
    glEnd();
    glPopMatrix();


}

void airfighter()
{
    //glColor3f(1.0,0.0,0.0);

    //glBegin(GL_QUADS);{
    //	glVertex2f( pl_x_airfighter, pl_y_airfighter);
    //	glVertex2f( pl_x_airfighter+12, pl_y_airfighter);
    //	glVertex2f(pl_x_airfighter+12, pl_y_airfighter-6);
    //	glVertex2f(pl_x_airfighter, pl_y_airfighter-6);
    //}
    //glEnd();
    glBegin(GL_POLYGON);
    {

        glVertex2f(pl_x_airfighter+104,pl_y_airfighter-7);
        glVertex2f(pl_x_airfighter+101.5,pl_y_airfighter-5.5);
        glVertex2f(pl_x_airfighter+98,pl_y_airfighter-5);    //-2,2

        glVertex2f(pl_x_airfighter+94,pl_y_airfighter-3); //-6,4

        glVertex2f(pl_x_airfighter+96,pl_y_airfighter-7);  //-4,0
        glVertex2f(pl_x_airfighter+94,pl_y_airfighter-11);  //-6,-4
        glVertex2f(pl_x_airfighter+98,pl_y_airfighter-9);  //-2,-2
        glVertex2f(pl_x_airfighter+101.5,pl_y_airfighter-8.5); //1.5,-1.5
        glVertex2f(pl_x_airfighter+104,pl_y_airfighter-7);


        //glVertex2f(4,0);
        //glVertex2f();
        //glVertex2f();



        //recv=pl_x_airfighter+104;



    }
    glEnd();













    sender=pl_x_airfighter+104;
    senderr=pl_y_airfighter-5.5;






}

void ganjam()
{

    int colision=0;
// printf("x of player: %f\n",sender);
//printf("x of enemy: %f\n",senderx);
    float x_of_rocket=sender;   // rokcet er x
    float y_of_rocket=senderr;    // rocket er y


    float x_of_enemy=senderx;   // enemy er x
    float y_of_enemy=sendery;    // enemy er y

    //y_of_rocket++;

    float x_of_enemy2=sender5;   // enemy er x
    float y_of_enemy2=sender6;

    // senderxx
    //senderyy
    float x_of_enemy3=sender3;   // enemy er x
    float y_of_enemy3=sender4;



    /*
     printf("x co-ordinate of enemy %f\n",x_of_enemy);

     printf("y co-ordinate of enemy %f\n",y_of_enemy);


     printf("x co-ordinate of rocket %f\n",x_of_rocket);

     printf("y co-ordinate of rocket %f\n",y_of_rocket);
    */



    int radius = 5;
    if((x_of_enemy+100<=x_of_rocket+radius&&x_of_enemy+100>=x_of_rocket-radius) && ( y_of_enemy<=y_of_rocket+radius&&y_of_enemy>=y_of_rocket-radius))
    {


        // colision=1;
        printf(" Colision is happend \n");
        // break;

        //exit(0);
        endgame=true;


        // system("cls");
    }
    if((x_of_enemy2+100<=x_of_rocket+radius&&x_of_enemy2+100>=x_of_rocket-radius) && ( y_of_enemy2<=y_of_rocket+radius&&y_of_enemy2>=y_of_rocket-radius))
    {


        // colision=1;
        printf(" Colision is happend \n");
        // break;
        // exit(0);
        endgame=true;
        // system("cls");
    }

    if((x_of_enemy3+100<=x_of_rocket+radius&&x_of_enemy3+100>=x_of_rocket-radius) && ( y_of_enemy3<=y_of_rocket+radius&&y_of_enemy3>=y_of_rocket-radius))
    {


        // colision=1;
        printf(" Colision is happend \n");
        // break;
        //  exit(0);

        endgame=true;
        // system("cls");
    }




    else
    {

        printf("par hoa gese \n");
        printf("x co-ordinate of enemy %f\n",x_of_enemy+100);

        printf("y co-ordinate of enemy %f\n",y_of_enemy);


        printf("x co-ordinate of rocket %f\n",x_of_rocket);

        printf("y co-ordinate of rocket %f\n",y_of_rocket);



    }








}
void enemy_move()
{
    pl_x_airfighter1 -= 0.05f;

    if(pl_x_airfighter1 < -200)
    {
        pl_x_airfighter1 =30;
        pl_y_airfighter1 = rand() % 40;


    }




}

void enemy_move2()
{
    pl_x_airfighter2 -= 0.1f;

    if(pl_x_airfighter2 < -200)
    {
        pl_x_airfighter2=30;
        pl_y_airfighter2 = rand() % 90;


    }

}
void enemy_move3()
{
    pl_x_airfighter3 -= 0.09f;

    if(pl_x_airfighter3 < -200)
    {
        pl_x_airfighter3=30;
        pl_y_airfighter3 = rand() % 90;


    }

}

void call_game()
{


    glPushMatrix();
    //guli_move();
    glPopMatrix();

    //////////////////////////////////


    //////////////////////////////////////////////


    glPushMatrix();
    glColor3f(1,1,.01);


    glTranslatef(xx,yy,0);
    airfighter();




    glPopMatrix();







    glPushMatrix();
    glTranslatef(aa,bb,0);
    enemy();
    // enemy2();
    enemy3();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-90,-2.5,0);
    //gulijacche(1);
    if(guli_marmu)
    {

        create_guli(sender,senderr);
        //guli_marmu = false;
    }

    glPopMatrix();


    enemy_move();
    enemy_move2();
    enemy_move3();


    building();
    char score[10];
    itoa(game_score,score,10);

    print(80,90,0,score);


    print(60,90,0,"Your Score:");























    ganjam();

    game_score=game_score+.01;




}


void keyboardListener(unsigned char key, int xx,int yy)
{
    double x,y,z;
    double rate = 0.01;
    z=0;
    switch(key)
    {

    case 'p':

    {

        startgame=false;
        break;


    }
    break;
    case 'q':

    {
        endgame=false;
        game_score=0;


        pl_x_airfighter=-100;

        call_game();



    }
    break;
    case '3':
        x=l.x;
        y=l.y;
        z=l.z;
        l.x = l.x*cos(rate)+u.x*sin(rate);
        l.y = l.y*cos(rate)+u.y*sin(rate);
        l.z = l.z*cos(rate)+u.z*sin(rate);

        u.x = u.x*cos(rate)-x*sin(rate);
        u.y = u.y*cos(rate)-y*sin(rate);
        u.z = u.z*cos(rate)-z*sin(rate);
        break;
    case '4':
        x=l.x;
        y=l.y;
        z=l.z;
        l.x = l.x*cos(-rate)+1*u.x*sin(-rate);
        l.y = l.y*cos(-rate)+u.y*sin(-rate);
        l.z = l.z*cos(-rate)+u.z*sin(-rate);

        u.x = u.x*cos(-rate)-x*sin(-rate);
        u.y = u.y*cos(-rate)-y*sin(-rate);
        u.z = u.z*cos(-rate)-z*sin(-rate);
        break;
    case '6':
        x=r.x;
        y=r.y;
        z=r.z;
        r.x = r.x*cos(rate)+u.x*sin(rate);
        r.y = r.y*cos(rate)+u.y*sin(rate);
        r.z = r.z*cos(rate)+u.z*sin(rate);

        u.x = u.x*cos(rate)-x*sin(rate);
        u.y = u.y*cos(rate)-y*sin(rate);
        u.z = u.z*cos(rate)-z*sin(rate);
        break;
    case '5':
        x=r.x;
        y=r.y;
        z=r.z;
        r.x = r.x*cos(-rate)+u.x*sin(-rate);
        r.y = r.y*cos(-rate)+u.y*sin(-rate);
        r.z = r.z*cos(-rate)+u.z*sin(-rate);

        u.x = u.x*cos(-rate)-x*sin(-rate);
        u.y = u.y*cos(-rate)-y*sin(-rate);
        u.z = u.z*cos(-rate)-z*sin(-rate);
        break;

    case 'w':
        if(angle_c_z>-45)
        {
            angle_c_z-=1.5;
        }
        break;
    case 'e':
        if(angle_c_x<45)
        {
            angle_c_x+=1.5;
        }
        break;
    case 'r':
        if(angle_c_x>-45)
        {
            angle_c_x-=1.5;
        }
        break;
    case 'a':
        if ( angle_t_x<45)
        {
            angle_t_x+=1.5;
        }
        break;
    case 's':
        if ( angle_t_x>-45)
        {
            angle_t_x-=1.5;
        }
        break;
    case 'd':
        if ( angle_t_z<45)
        {
            angle_t_z+=1.5;
        }
        break;
    case 'f':
        if ( angle_t_z>-45)
        {
            angle_t_z-=1.5;
        }
        break;



    default:
        break;
    }

}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:		//down arrow key

        // pl_y_airfighter+=1;
        //pl_y2+=1;      // guli track
        // pl_y2=0;

        if(pl_y_airfighter>96)
        {


            pl_y_airfighter-=1;

        }
        else
        {

            pl_y_airfighter+=1;


        }

        break;

    case GLUT_KEY_DOWN:		// up arrow key

        //pl_y2-=1;   // guli track
        // pl_y2=0;
        if(pl_y_airfighter<-3)
        {


            pl_y_airfighter+=1;

        }
        else
        {

            pl_y_airfighter-=1;



        }








        break;

    case GLUT_KEY_LEFT :
        pl_x_airfighter-=1;
        //  if(pl_x_airfighter > 0){
        //     pl_x_airfighter-=1;
        // }else{
        //     pl_x_airfighter+=1;
        // }





        break;
    case GLUT_KEY_RIGHT :
        pl_x_airfighter+=1;

        break;

    case GLUT_KEY_PAGE_UP:
        pos.x+=u.x;
        pos.y+=u.y;
        pos.z+=u.z;
        break;
    case GLUT_KEY_PAGE_DOWN:
        pos.x-=u.x;
        pos.y-=u.y;
        pos.z-=u.z;
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
}



void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) 		// 2 times?? in ONE click? -- solution is checking DOWN or UP
        {
            /*bullet =1;
            double length = 649;
            //double length = (649/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
            printf("---> %lf\n",length);
            //X = length* sin(angle_c_z*pi/180);
            X= length* tan(angle_c_z*pi/180);

            Z=-100*sin(angle_c_x*pi/180)-(649-100*cos(angle_c_x*pi/180))*tan((angle_t_x+angle_c_x)*pi/180);*/



        }
        break;


    case GLUT_RIGHT_BUTTON:
        if(state == GLUT_DOWN) 		// 2 times?? in ONE click? -- solution is checking DOWN or UP
        {
            drawaxes=1-drawaxes;
            //(600/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
        }
        break;
    //........

    case GLUT_MIDDLE_BUTTON:
        //........
        break;

    default:
        break;
    }
}






void gameover()
{


    //drawCircle(10,10);

   // print(-7,6,0,"Game Over!");

    char score[10];
    itoa(game_score,score,10);

    print(4,10,0,score);

    //print(-20,40,0,"start again press q!");





    print(-8,20,0,"Game Over!");

    print(-6,10,0,"Score:");
  //  print(-10,-5,0,"..................................");

    print(-14,-15,0,"Start again press [Q]!");






}

void display()
{

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?
    gluLookAt(0,0,100,	0,0,0,	0,1,0);
    //gluLookAt(100,100,100,	0,0,0,	0,0,1);
    //gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    //gluLookAt(pos.x,pos.y,pos.z,	pos.x+l.x,pos.y+l.y,pos.z+l.z,	u.x,u.y,u.z);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects


    //drawAxes();
   // drawGrid();

    //glPushMatrix();
    //glRotatef(45,1,0,0);

    // glPopMatrix();
    //square_move2();


    if(endgame==false && startgame == false)
    {
        call_game();

    }
    else if(endgame == true)
    {

        gameover();


    }
    else
    {
        start_game();
    }


    //  guli_move();
    //glColor3f(1,0,0);
    //drawSquare(10);
//sky();
    //drawSS();
    // movement3D();
    // drawSphere(50,20,10);
    //  quad();
    //drawCone(5,10,50);

    //draw_cylinder(2,500,segment);
    //100*sin(angle_c_x)+(500-100*cos(angle_c_x))*sin(angle_t_x);

    // castle();


    //  rocket();

//	drawSphere(30,24,20);











    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate()
{
    //display();
    angle+=.1;
    //codes for any changes in Models, Camera
    //limit+=0.01;
    //if(limit>=50.0)
    // {
    //    limit=0;
    // }
    glutPostRedisplay();
}

void init()
{
    //codes for initialization
    drawgrid=0;
    drawaxes=1;
    //cameraHeight=150.0;
    //cameraAngle=1.0;
    //angle=0;

    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(90,	1,	1,	5000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

int main(int argc, char **argv)
{
    pos.x=0;
    pos.y=0;
    pos.z=-20;
    l.x=0;
    u.x=-1;
    r.x=0;
    l.y=0;
    u.y=0;
    r.y=1;
    l.z=1;
    u.z=0;
    r.z=0;
    glutInit(&argc,argv);
    glutInitWindowSize(1600, 650);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);




    init();

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}

/*
void drawSphere(double radius,int slices,int stacks,int up)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		if(up==3){
                r= 2*radius- radius*cos(((double)i/(double)stacks)*(pi/2));
		}else{
		     r=  radius*cos(((double)i/(double)stacks)*(pi/2));
		}
		for(j=0;j<=slices;j++)
		{
		    if(up!=3){
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		    }
		    else{
            points[i][j].x= r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=(r*sin(((double)j/(double)slices)*2*pi));
			points[i][j].z=h;

		    }
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);

		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
			    glColor3f(j%2,j%2,j%2);
			    if(up==1 or up==-1 or up==3)
                {
                    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                }
                //lower hemisphere
                if(up==0 or up==-1)
                {

                    glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
                }


			}glEnd();
		}
	}
}


void offline()
{

    glBegin(GL_QUADS);{
        //upper hemisphere
        glColor3f(.1,.1,.1);
        glVertex3f(200,-650,200);
        glVertex3f(200,-650,-200);
        glVertex3f(-200,-650,-200);
        glVertex3f(-200,-650,200);

    }glEnd();


    if(bullet==1 && abs(X)<200 && abs(Z)<200){
    Y++;
    arra[Y].x=X;
    arra[Y].z = Z;
    printf("%lf %lf %lf %lf\n",X,Z,angle_c_x,angle_c_z);

	bullet =0;

    }
    int j;
    for(j=0;j<=Y;j++){
        glColor3f(1.0,0.0,0.0);

            glBegin(GL_QUADS);{
            glVertex3f(arra[j].x+5 ,-649, arra[j].z+5);
            glVertex3f(arra[j].x+5,-649, arra[j].z-5);
            glVertex3f(arra[j].x-5,-649,arra[j].z-5 );
            glVertex3f(arra[j].x-5, -649, arra[j].z+5);
        }glEnd();
    }

    int segment =30;
    glRotatef(angle_c_z,0,0,1);
    glRotatef(angle_c_x,1,0,0);
    glRotatef(90,1,0,0);
    glTranslatef(0,0,20);
    drawSphere(20,segment,segment,0);
    draw_cylinder(20,100,segment);
    glTranslatef(0,0,100);
    drawSphere(20,segment,segment,1);
    double r,l;
    r=15;
    l=170;
    glTranslatef(0,0,20);

    glRotatef(angle_t_x,1,0,0);
    glRotatef(angle_t_z,0,0,1);

    glTranslatef(0,0,r);
    drawSphere(r,segment,segment,0);
    draw_cylinder(r,l,segment);
    glTranslatef(0,0,l);
    drawSphere(r,segment,segment,3);
}
*/
