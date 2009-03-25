using namespace std;
#include <math.h>
#define GL_PI 3.1415f

#define MODE_SOLID 0
#define MODE_LINE  1
#define MODE_POINT 2
int iMode = MODE_SOLID;
GLboolean bEdgeFlag = GL_TRUE;
static int globalSelection = 0;
#define drawOneLine(x1,y1,x2,y2)  glBegin(GL_LINES);  \
   glVertex2f ((x1),(y1)); glVertex2f ((x2),(y2)); glEnd();

class Figura{
public:

  GLfloat xRot1;
  GLfloat yRot1;
  GLfloat xPos;
  GLfloat yPos;
  GLfloat zPos;
  int origenON;

  virtual void paintMyself(){
    printf("no deberia de aparecer esto");
  }
  virtual void moverEscenaEnX(GLfloat x){
    printf("no deberia de aparecer esto 1");
  }
  virtual void moverEscenaEnY(GLfloat y){
    printf("no deberia de aparecer esto 2");
  }
  virtual void transladarEjeX(GLfloat x){
    /* xPos += x; */
  }
  virtual void transladarEjeY(GLfloat y){
    /* yPos += y; */
  }
  virtual void transladarEjeZ(GLfloat z){
    /* zPos += z; */
  }
  virtual void dibujarOrigen(){
    /* zPos += z; */
  }

};

 
 
class Starla : public Figura
{
public: 

  GLfloat xRot1;
  GLfloat yRot1;
  GLfloat xPos;
  GLfloat yPos;
  GLfloat zPos;
  int origenON;
  
Starla(GLfloat x, GLfloat y){
  xRot1 = x;
  yRot1 = y;
  xPos = 0;
  yPos = 0;
  zPos = 0;
  origenON = 0;
}

void paintMyself(){

  if(iMode == MODE_LINE)
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  if(iMode == MODE_POINT)
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
  if(iMode == MODE_SOLID)
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glPushMatrix();
   
  glTranslatef(xPos, yPos, zPos);
    glRotatef(xRot1, 1.0f, 0.0f, 0.0f);  
    glRotatef(yRot1, 0.0f, 1.0f, 0.0f);
    
    if (origenON == 1)   {      ponerOrigen();    }

    glBegin(GL_TRIANGLES);
    glEdgeFlag(bEdgeFlag);     glVertex2f(-20.0f, 0.0f);
    glEdgeFlag(GL_TRUE);       glVertex2f(20.0f, 0.0f);  
    glVertex2f(0.0f, 40.0f);
    glVertex2f(-20.0f,0.0f);   glVertex2f(-60.0f,-20.0f);
    glEdgeFlag(bEdgeFlag);     glVertex2f(-20.0f,-40.0f);
    glEdgeFlag(GL_TRUE);       glVertex2f(-20.0f,-40.0f);
    glVertex2f(0.0f, -80.0f);  glEdgeFlag(bEdgeFlag);
    glVertex2f(20.0f, -40.0f); glEdgeFlag(GL_TRUE);
    glVertex2f(20.0f, -40.0f); glVertex2f(60.0f, -20.0f);
    glEdgeFlag(bEdgeFlag);     glVertex2f(20.0f, 0.0f);
    glEdgeFlag(GL_TRUE);
    glEdgeFlag(bEdgeFlag);     glVertex2f(-20.0f, 0.0f);
    glVertex2f(-20.0f,-40.0f); glVertex2f(20.0f, 0.0f);
    glVertex2f(-20.0f,-40.0f); glVertex2f(20.0f, -40.0f);
    glVertex2f(20.0f, 0.0f);   glEdgeFlag(GL_TRUE);
    glEnd();
    

     
  glPopMatrix();
   
   
   
}
  void moverEscenaEnX(GLfloat x){
    if (globalSelection < 0) {globalSelection = 0; }
    xRot1 += x;
  }
  void moverEscenaEnY(GLfloat y){
    if (globalSelection < 0){ globalSelection = 0;  }
    yRot1 += y;
  }
  void transladarEjeX(GLfloat x){
    xPos += x;
  }
  void transladarEjeY(GLfloat y){
    yPos += y;
  }
  void transladarEjeZ(GLfloat z){
    zPos += z;
  }
  void dibujarOrigen(){
    printf("dibujando el origen de la estrella\n");
    if (origenON == 0)
      {
	origenON = 1;
      }else{
      origenON = 0;
    }
  }

  void ponerOrigen(){
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(50.0f, 0.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 50.0f);
    glEnd( );
  }

  
};
 
 
class Sphere : public Figura
{
public: 
  GLfloat xRot1;
  GLfloat yRot1;
  GLfloat xPos;
  GLfloat yPos;
  GLfloat zPos;
  int origenON;

Sphere(GLfloat x, GLfloat y){
  xRot1 = x;
  yRot1 = y;
  xPos = 0;
  yPos = 0;
  zPos = 0;
  origenON = 0;
}

void paintMyself(){
   
  if(iMode == MODE_LINE) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
  if(iMode == MODE_POINT){ glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);}
  if(iMode == MODE_SOLID){ glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); }
    
  glPushMatrix();

     
    glTranslatef(xPos, yPos, zPos);
    glRotatef(xRot1, 1.0f, 0.0f, 0.0f);  
    glRotatef(yRot1, 0.0f, 1.0f, 0.0f);
     
    
     
     
     
     
        
    
    
    /* DIBUJAR EL ORIGEN ACA */
    if (origenON == 1)    {           ponerOrigen();    }
      glutSolidSphere(20, 30 ,20);
  glPopMatrix();
}

  void moverEscenaEnX(GLfloat x){if (globalSelection < 0) {globalSelection = 0; }
    xRot1 += x + globalSelection;
  }
  void moverEscenaEnY(GLfloat y){if (globalSelection < 0){ globalSelection = 0; }
    yRot1 += y + globalSelection;
  }
  void transladarEjeX(GLfloat x){
    xPos += x;
  }
  void transladarEjeY(GLfloat y){
    yPos += y;
  }
  void transladarEjeZ(GLfloat z){
    zPos += z;
  }
  
  /* LO QUE VA A HACER ESTE METODO ES PRENDER LA FLAG DE ORIGEN */
  /* AHORA VOY A HACER QUE LO HEREDEN */

  void dibujarOrigen(){
    printf("dibujando el origen de la estrella\n");
    if (origenON == 0)
      {
	origenON = 1;
      }else{
      origenON = 0;
    }
  }

  void ponerOrigen(){
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(50.0f, 0.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 50.0f);
    glEnd( );
  }
  
};
 
 
class Cube : public Figura
{
public: 
  GLfloat xRot1;
  GLfloat yRot1;
  GLfloat xPos;
  GLfloat yPos;
  GLfloat zPos;
  int origenON;

Cube(GLfloat x, GLfloat y){
  xRot1 = x;
  yRot1 = y;
  xPos = 0;
  yPos = 0;
  zPos = 0;
}

void paintMyself(){
   
  if(iMode == MODE_LINE) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
  if(iMode == MODE_POINT){ glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);}
  if(iMode == MODE_SOLID){ glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); }
    
  glPushMatrix();
     
     
    glTranslatef(xPos, yPos, zPos);
    glRotatef(xRot1, 1.0f, 0.0f, 0.0f);  
    glRotatef(yRot1, 0.0f, 1.0f, 0.0f);
     
  
     
     
     
    if (origenON == 1)    {           ponerOrigen();    }
     
    glutSolidCube(20);

     
  glPopMatrix();
}

  void moverEscenaEnX(GLfloat x){if (globalSelection < 0) {globalSelection = 0; }
    xRot1 += x + globalSelection;
  }
  void moverEscenaEnY(GLfloat y){if (globalSelection < 0){ globalSelection = 0; }
    yRot1 += y + globalSelection;
  }
  void transladarEjeX(GLfloat x){
    xPos += x;
  }
  void transladarEjeY(GLfloat y){
    yPos += y;
  }
  void transladarEjeZ(GLfloat z){
    zPos += z;
  }
  void dibujarOrigen(){
    printf("dibujando el origen de la estrella\n");
    if (origenON == 0)
      {
	origenON = 1;
      }else{
      origenON = 0;
    }
  }

  void ponerOrigen(){
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(50.0f, 0.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 50.0f);
    glEnd( );
  }
};
 
 
class Cone : public Figura
{
public: 
  GLfloat xRot1;
  GLfloat yRot1;
  GLfloat xPos;
  GLfloat yPos;
  GLfloat zPos;
  int origenON;
  
Cone(GLfloat x, GLfloat y){
  xRot1 = 0;
  yRot1 = 0;
  xPos = 0;
  yPos = 0;
  zPos = 0;
}

void paintMyself(){
  if(iMode == MODE_LINE) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
  if(iMode == MODE_POINT){ glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);}
  if(iMode == MODE_SOLID){ glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); }
  glPushMatrix();
  glTranslatef(xPos, yPos, zPos);
  glRotatef(xRot1, 1.0f, 0.0f, 0.0f);  
  glRotatef(yRot1, 0.0f, 1.0f, 0.0f);
    if (origenON == 1)    {           ponerOrigen();    }
    glutSolidCone(20, 40, 30, 10);
  glPopMatrix();
}

  void moverEscenaEnX(GLfloat x){if (globalSelection < 0) {globalSelection = 0; }
    xRot1 += x + globalSelection;
  }
  void moverEscenaEnY(GLfloat y){if (globalSelection < 0){ globalSelection = 0; }
    yRot1 += y + globalSelection;
  }
  void transladarEjeX(GLfloat x){
    xPos += x;
  }
  void transladarEjeY(GLfloat y){
    yPos += y;
  }
  void transladarEjeZ(GLfloat z){
    zPos += z;
  }
    void dibujarOrigen(){
    printf("dibujando el origen de la estrella\n");
    if (origenON == 0)
      {
	origenON = 1;
      }else{
      origenON = 0;
    }
  }

  void ponerOrigen(){
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(50.0f, 0.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 50.0f);
    glEnd( );
  }

};
 
 
class Torus : public Figura
{
public: 
  GLfloat xRot1;
  GLfloat yRot1;
  GLfloat xPos;
  GLfloat yPos;
  GLfloat zPos;
  int origenON;

Torus(GLfloat x, GLfloat y){
  xRot1 = x;
  yRot1 = y;
  xPos = 0;
  yPos = 0;
  zPos = 0;
}

void paintMyself(){
   
  if(iMode == MODE_LINE) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
  if(iMode == MODE_POINT){ glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);}
  if(iMode == MODE_SOLID){ glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); }
    
   
   
     
  glPushMatrix();
    glTranslatef(xPos, yPos, zPos);
    glRotatef(xRot1, 1.0f, 0.0f, 0.0f);  
    glRotatef(yRot1, 0.0f, 1.0f, 0.0f);
         
    if (origenON == 1)    {           ponerOrigen();    }
    glutSolidTorus(10,30,20,20);
  glPopMatrix();
   
   
}

  void moverEscenaEnX(GLfloat x){if (globalSelection < 0) {globalSelection = 0; }
    xRot1 += x + globalSelection;
  }
  void moverEscenaEnY(GLfloat y){if (globalSelection < 0){ globalSelection = 0; }
    yRot1 += y + globalSelection;
  }
  void transladarEjeX(GLfloat x){
    xPos += x;
  }
  void transladarEjeY(GLfloat y){
    yPos += y;
  }
  void transladarEjeZ(GLfloat z){
    zPos += z;
  }
        void dibujarOrigen(){
    printf("dibujando el origen de la estrella\n");
    if (origenON == 0)
      {
	origenON = 1;
      }else{
      origenON = 0;
    }
  }

  void ponerOrigen(){
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(50.0f, 0.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 50.0f);
    glEnd( );
  }


};
 

class Cylinder : public Figura
{
public: 
  GLfloat xRot1;
  GLfloat yRot1;
  GLfloat xPos;
  GLfloat yPos;
  GLfloat zPos;
  int origenON;
  
Cylinder(GLfloat x, GLfloat y){
  xRot1 = x;
  yRot1 = y;
  xPos = 0;
  yPos = 0;
  zPos = 0;
}

void paintMyself(){
   
  if(iMode == MODE_LINE) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
  if(iMode == MODE_POINT){ glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);}
  if(iMode == MODE_SOLID){ glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); }
    
  glPushMatrix();

    glTranslatef(xPos, yPos, zPos);
    glRotatef(xRot1, 1.0f, 0.0f, 0.0f);  
    glRotatef(yRot1, 0.0f, 1.0f, 0.0f);

     
    if (origenON == 1)    {           ponerOrigen();    }
    GLUquadricObj *quadratic;	
    quadratic=gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);

    gluCylinder(quadratic,1.0f,1.0f,10.0f,40,40);	

  glPopMatrix();
}

  void moverEscenaEnX(GLfloat x){if (globalSelection < 0) {globalSelection = 0; }
    xRot1 += x + globalSelection;
  }
  void moverEscenaEnY(GLfloat y){if (globalSelection < 0){ globalSelection = 0; }
    yRot1 += y + globalSelection;
  }
  void transladarEjeX(GLfloat x){
    xPos += x;
  }
  void transladarEjeY(GLfloat y){
    yPos += y;
  }
  void transladarEjeZ(GLfloat z){
    zPos += z;
  }
    void dibujarOrigen(){
    printf("dibujando el origen de la estrella\n");
    if (origenON == 0)
      {
	origenON = 1;
      }else{
      origenON = 0;
    }
  }

  void ponerOrigen(){
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(50.0f, 0.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd( );
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 50.0f);
    glEnd( );
  }

};
 

