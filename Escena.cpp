#include <cstdlib>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
#include <vector>
#include "Figura.h"

struct Rectangle
{
  int top;
  int bottom;
  int left;
  int right;
};

void ProcessMenu(int);
struct Rectangle boundingRect;
GLuint selectedObject = 0;
float fAspect;
static float angle=0.0,ratio;
static float x=0.0f,y=1.75f,z=5.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
void drawGrid(void);
void ponerGrid();
static int gridFlag = 0;
static vector<Figura*> scene;


void ponerGrid(){
  if (gridFlag == 0)
    {
      gridFlag = 1;
    }else{
    gridFlag = 0;
  }
}

void DrawObjects(void)
{

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  if (gridFlag == 1){drawGrid();}
  glTranslatef(0.0f, 0.0f, -120.5f);

  glInitNames();
  glPushName(0);











  if (scene.size() != 0)
    {
      for (int i = 0; i < scene.size(); ++i)
	{

	  glColor3f((GLfloat)(rand() % 1000) * 0.001,(GLfloat)(rand() % 1000) * 0.001,(GLfloat)(rand() % 1000) * 0.001);
	  printf("%f\n", (GLfloat)(rand() % 1000) * 0.001);

	  glLoadName(i + 1);
	  glPassThrough((GLfloat)i + 1);
	  glPushMatrix();
	  scene[i]->paintMyself();
	  glPopMatrix();
	}
    }
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}



void RenderScene(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  DrawObjects();


  if(selectedObject != 0)
    {
      GLint viewport[4];


      glGetIntegerv(GL_VIEWPORT, viewport);


      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();


      glOrtho(viewport[0], viewport[2], viewport[3], viewport[1], -1, 1);
      glMatrixMode(GL_MODELVIEW);

      glDisable(GL_LIGHTING);
      glColor3f(1.0f, 0.0f, 0.0f);
      glBegin(GL_LINE_LOOP);
      glVertex2i(boundingRect.left, boundingRect.top);
      glVertex2i(boundingRect.left, boundingRect.bottom);
      glVertex2i(boundingRect.right, boundingRect.bottom);
      glVertex2i(boundingRect.right, boundingRect.top);
      glEnd();
      glEnable(GL_LIGHTING);
    }

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  glutSwapBuffers();
}



#define FEED_BUFF_SIZE	32768
void MakeSelection(int nChoice)
{

  static GLfloat feedBackBuff[FEED_BUFF_SIZE];


  int size,i,j,count;


  boundingRect.right = boundingRect.bottom = -999999;
  boundingRect.left = boundingRect.top =  999999;


  glFeedbackBuffer(FEED_BUFF_SIZE,GL_2D, feedBackBuff);


  glRenderMode(GL_FEEDBACK);


  DrawObjects();


  size = glRenderMode(GL_RENDER);



  i = 0;
  while(i < size)
    {

      if(feedBackBuff[i] == GL_PASS_THROUGH_TOKEN)
	if(feedBackBuff[i+1] == (GLfloat)nChoice)
	  {
	    i+= 2;

	    while(i < size && feedBackBuff[i] != GL_PASS_THROUGH_TOKEN)
	      {

		if(feedBackBuff[i] == GL_POLYGON_TOKEN)
		  {

		    count = (int)feedBackBuff[++i];
		    i++;

		    for(j = 0; j < count; j++)
		      {

			if(feedBackBuff[i] > boundingRect.right)
			  boundingRect.right = int(feedBackBuff[i]);

			if(feedBackBuff[i] < int(boundingRect.left))
			  boundingRect.left = int(feedBackBuff[i]);
			i++;


			if(feedBackBuff[i] > boundingRect.bottom)
			  boundingRect.bottom = int(feedBackBuff[i]);

			if(feedBackBuff[i] < boundingRect.top)
			  boundingRect.top = int(feedBackBuff[i]);
			i++;
		      }
		  }
		else
		  i++;
	      }
	    break;
	  }
      i++;
    }
}

#define BUFFER_LENGTH 64
void ProcessSelection(int xPos, int yPos)
{

  static GLuint selectBuff[BUFFER_LENGTH];
  GLint hits, viewport[4];
  glSelectBuffer(BUFFER_LENGTH, selectBuff);
  glGetIntegerv(GL_VIEWPORT, viewport);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glRenderMode(GL_SELECT);
  glLoadIdentity();
  gluPickMatrix(xPos, viewport[3] - yPos + viewport[1], 2,2, viewport);
  gluPerspective(60.0f, fAspect, 1.0, 1000.0);
  DrawObjects();
  hits = glRenderMode(GL_RENDER);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  if(hits == 1)
    {
      MakeSelection(selectBuff[3]);
      if(selectedObject == selectBuff[3])
	selectedObject = 0;
      else
	selectedObject = selectBuff[3];
    }

  printf("holaaaaa donde estoy en %d , %d\n", xPos, yPos);

  glutPostRedisplay();
}

void SetupRC()
{

  GLfloat  dimLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat  sourceLight[] = { 0.65f, 0.65f, 0.65f, 1.0f };
  GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };


  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);



  glEnable(GL_LIGHTING);


  glLightfv(GL_LIGHT0,GL_AMBIENT,dimLight);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
  glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
  glEnable(GL_LIGHT0);


  glEnable(GL_COLOR_MATERIAL);


  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


  glClearColor(0.60f, 0.60f, 0.60f, 1.0f );
  glLineWidth(2.0f);
}




void ChangeSize(int w, int h)
{

  if(h == 0)
    h = 1;


  glViewport(0, 0, w, h);


  fAspect = (GLfloat)w/(GLfloat)h;


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();


  gluPerspective(60.0f, fAspect, 1.0, 1000.0);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(x, y, z,
	    x + lx,y + ly,z + lz,
	    0.0f,1.0f,0.0f);
}

void orientMe(float ang) {


  lx = sin(ang);
  lz = -cos(ang);
  glLoadIdentity();
  gluLookAt(x, y, z,
	    x + lx,y + ly,z + lz,
	    0.0f,1.0f,0.0f);
}


void moveMeFlat(int i) {
  x = x + i*(lx)*0.1;
  z = z + i*(lz)*0.1;
  glLoadIdentity();
  gluLookAt(x, y, z,
	    x + lx,y + ly,z + lz,
	    0.0f,1.0f,0.0f);
}



void MouseCallback(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    ProcessSelection(x, y);
}


void NormalKeys(unsigned char key, int x, int y){
  if (key == 'p') {
    if (globalSelection > -1 && globalSelection < scene.size() - 1)
      {
	globalSelection++;
      }
  }
  if (key == 'o') {
    if (globalSelection > 0 && globalSelection < scene.size())
      {
	globalSelection--;
      }
  }
  if (key == 'q'){ exit(0);}
  if (key == 'e'){ printf("posX: %d ,", x); printf("posY: %d ,", y);}
  if (key == 'w'){
    glTranslatef(0.0f,0.0f,-10.0f);

    Starla *stary2 = new Starla(x - 100, (y*-1) +100);
    scene.push_back(stary2);
    printf("estrellitaaaaaa");
    glutPostRedisplay();
    glFlush();
    printf(" tamanho del vector %d", scene.size());
  }
  if (key == 'r'){ glTranslatef(0.0f,0.0f,-10.0f);  glutPostRedisplay(); printf("alejandomeeeee\n");}


  if (key == 'a'){

    Starla *stary2 = new Starla(0, 0);
    scene.push_back(stary2);
    glutPostRedisplay();
    glFlush();
    printf(" tamanho del vector %d", scene.size());
  }


  if (key =='s')
    {

      Sphere *stary2 = new Sphere(0,0);
      scene.push_back(stary2);
      printf("esferaaaaaaa\n");
      glutPostRedisplay();
      glFlush();
    }

  if (key =='d')
    {

      Cube *stary2 = new Cube(0, 0);
      scene.push_back(stary2);
      printf("Cubooooooo\n");
      glutPostRedisplay();
      glFlush();
    }


  if (key =='f')
    {

      Cone *stary2 = new Cone(x, y);
      scene.push_back(stary2);
      printf("Conoooo\n");
      glutPostRedisplay();
      glFlush();
    }


  if (key =='g')
    {

      Torus *stary2 = new Torus(0, 0);
      scene.push_back(stary2);
      printf("Torusss\n");
      glutPostRedisplay();
      glFlush();
    }


  if (key =='t')
    {

      Cylinder *stary2 = new Cylinder(0, 0);
      scene.push_back(stary2);
      printf("Cilindroooooo\n");
      glutPostRedisplay();
      glFlush();
    }
  if (key == 'z')  {    angle -= 0.1f;orientMe(angle); glutPostRedisplay(); }
  if (key=='v')  {    angle +=0.1f;orientMe(angle); glutPostRedisplay(); }
  if (key == 'x')  {    moveMeFlat(10); glutPostRedisplay(); }
  if (key == 'c')  {      moveMeFlat(-10); glutPostRedisplay(); }


  if (key == 'h')  {      scene[globalSelection]->transladarEjeX(1.0f) ; glutPostRedisplay(); }
  if (key == 'j')  {      scene[globalSelection]->transladarEjeY(1.0f) ; glutPostRedisplay(); }
  if (key == 'k')  {      scene[globalSelection]->transladarEjeZ(1.0f) ; glutPostRedisplay(); }


  if (key == 'y')  {      scene[globalSelection]->transladarEjeX(-1.0f) ; glutPostRedisplay(); }
  if (key == 'u')  {      scene[globalSelection]->transladarEjeY(-1.0f) ; glutPostRedisplay(); }
  if (key == 'i')  {      scene[globalSelection]->transladarEjeZ(-1.0f) ; glutPostRedisplay(); }
  if (key == 'n')  {      scene[globalSelection]->dibujarOrigen(); glutPostRedisplay(); }
  if (key == 'm')  {      ponerGrid(); glutPostRedisplay(); }

}
void SpecialKeys(int key, int x, int y)
{
  if(key == GLUT_KEY_UP)
    scene[globalSelection]->moverEscenaEnX(-5.0f);

  if(key == GLUT_KEY_DOWN)
    scene[globalSelection]->moverEscenaEnX(5.0f);

  if(key == GLUT_KEY_LEFT)
    scene[globalSelection]->moverEscenaEnY(5.0f);

  if(key == GLUT_KEY_RIGHT)
    scene[globalSelection]->moverEscenaEnY(-5.0f);

  glutPostRedisplay();
}

void ProcessMenu(int value)
{
  switch(value)
    {
    case 1:
      iMode = MODE_SOLID;
      break;
    case 2:
      iMode = MODE_LINE;
      break;
    case 3:
      iMode = MODE_POINT;
      break;
    case 4:
      bEdgeFlag = GL_TRUE;
      break;
    case 5:
    default:
      bEdgeFlag = GL_FALSE;
      break;
    }
  glutPostRedisplay();
}

void drawGrid(){
  GLuint i,j;
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
  glTranslatef(-40.0f,-5.0f, -40.0f);
  glTranslatef(0.0f,-5.0f, 0.0f);
  glRotatef(90, 0,1,0);
  glRotatef(90, 1,0,0);
  for (i = 0; i < 80; i++) {
    for (j = 0; j < 80; j ++) {
      glColor3f ((GLfloat) i/80.0, (GLfloat) j/80.0,
		 (GLfloat) (i + j)/80.0);
      glRecti (i, j, i+1, j+1);
    }
  }
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

int main(int argc, char* argv[])
{
  int nModeMenu;
  int nEdgeMenu;
  int nMainMenu;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800,600);
  glutCreateWindow("Little Maya ver0.05");

  nModeMenu = glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("Solid",1);
  glutAddMenuEntry("Outline",2);
  glutAddMenuEntry("Points",3);

  nEdgeMenu = glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("On",4);
  glutAddMenuEntry("Off",5);

  nMainMenu = glutCreateMenu(ProcessMenu);
  glutAddSubMenu("Mode", nModeMenu);
  glutAddSubMenu("Edges", nEdgeMenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutReshapeFunc(ChangeSize);
  glutMouseFunc(MouseCallback);
  glutKeyboardFunc(NormalKeys);
  glutSpecialFunc(SpecialKeys);
  glutDisplayFunc(RenderScene);
  SetupRC();
  glutMainLoop();

  return 0;
}
