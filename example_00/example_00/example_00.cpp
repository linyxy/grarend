// CS184 Simple OpenGL Example
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

#define PI 3.14159265

const int BLOCK_NUM = 150;
const int TOTAL_LINE= 150;

using namespace std;

//****************************************************
// Some Classes
//****************************************************
class Viewport {
  public:
    int w, h; // width and height
};


//****************************************************
// Global Variables
//****************************************************
Viewport    viewport;

//*******************************
//use to draw the triangle
//*******************************
int ruleCheck(int a, int b, int c) {
  int res;
  a = 2*2*a;
  b = 2*b;
  res = a+b+c;
  switch(res) {
  case 0:
    return 0;
  case 1:
    return 1;
  case 2:
    return 0;
  case 3:
    return 1;
  case 4:
    return 1;
  case 5:
    return 0;
  case 6:
    return 1;
  case 7:
    return 0;
  }
  return 0;
}

void resize(int li, int c,float* position){
  float line = (float)li;
  float cc = (float)c;
  
  float LINE_W = 2/(float)BLOCK_NUM;
  float LINE_H = 2/(float)TOTAL_LINE;
  cc = LINE_W*c -1;

  line = LINE_H*line -1;

  float left = cc;
  float right = cc+LINE_W;

  float up = line;
  float down = line+LINE_H;

  position[0] = left*-1;
  position[1] = up*-1;
  position[2] = right*-1;
  position[3] = up*-1;
  position[4] = right*-1;
  position[5] = down*-1;
  position[6] = left*-1;
  position[7] = down*-1;
  // printf("BLOCK_NUM = %f, LINE_W = %f\n",2/BLOCK_NUM,LINE_W );

}

void update(int* l,int* tmp) {
  //rule #1
  
  if (l[0] == 1 || l[1] ==1 )
    tmp[0] = 1;
  if (l[BLOCK_NUM-1] ==1 || l[BLOCK_NUM-2] ==1 )
    tmp[BLOCK_NUM-1] = 1;

  //rule #2
  // tmp[0] = 0;
  // tmp[l.length-1] = 0;

  for (int i =1; i<BLOCK_NUM-1; i++) {
    tmp[i] = ruleCheck(l[i-1], l[i], l[i+1]);
  }

  // int counter = 0;

  for (int i =0; i<BLOCK_NUM; i++) {
    l[i] = tmp[i];
  }
}

void colorpicker(float* base,int line,int hor){
  float r = (float)line / (float)TOTAL_LINE ;
  float g = (float)hor / (float)BLOCK_NUM;
  float b = 1 - r - g;
  base[0] = r;
  base[1] = g;
  base[2] = b;
}

//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport(0,0,viewport.w,viewport.h);// sets the rectangle that will be the window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // loading the identity matrix for the screen

  //----------- setting the projection -------------------------
  // glOrtho sets left, right, bottom, top, zNear, zFar of the chord system


  // glOrtho(-1, 1 + (w-400)/200.0 , -1 -(h-400)/200.0, 1, 1, -1); // resize type = add
  // glOrtho(-w/400.0, w/400.0, -h/400.0, h/400.0, 1, -1); // resize type = center

  glOrtho(-1, 1, -1, 1, 1, -1);    // resize type = stretch

  //------------------------------------------------------------
}


//****************************************************
// sets the window up
//****************************************************
void initScene(){
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Clear to black, fully transparent

  myReshape(viewport.w,viewport.h);
}


//***************************************************
// function that does the actual drawing
//***************************************************
void myDisplay() {


  //----------------------- ----------------------- -----------------------
  // This is a quick hack to add a little bit of animation.
  static int tip = 1;
  const  int stp = 1;
  const  int beg = 0;
  const  int end = TOTAL_LINE;

  tip += stp;
  if (tip>end) tip = beg;
  //----------------------- ----------------------- -----------------------


  glClear(GL_COLOR_BUFFER_BIT);                // clear the color buffer (sets everything to black)

  glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
  glLoadIdentity();                            // make sure transformation is "zero'd"

  //----------------------- code to draw objects --------------------------


  int line_count = 0;

  int line[BLOCK_NUM],tem[BLOCK_NUM];
  for(int i = 0; i<BLOCK_NUM;i++){
    line[i] = 0;
    tem[i] = 0;
  }
  line[BLOCK_NUM/2] = 1;
  for (line_count = 0; line_count < tip; ++line_count)
  {
    // printf("%d\n",line_count);
    for(int sq = 0; sq<BLOCK_NUM;sq++){
      if(line[sq]==1){
        float pos[8];
        float color[3];
        resize(line_count,sq,pos);
        colorpicker(color,line_count,sq);
        glColor3f(color[0],color[1],color[2]); 
        glBegin(GL_POLYGON);                         // draw rectangle 
        //glVertex3f(x val, y val, z val (won't change the point because of the projection type));
        glVertex3f(pos[0], pos[1], 0.0f);             // bottom right corner of rectangle
        glVertex3f(pos[2], pos[3], 0.0f);  
        glVertex3f(pos[4], pos[5], 0.0f);  
        glVertex3f(pos[6], pos[7], 0.0f);  
        glEnd();
        // printf("%f\n",pos[6] );
      }

    }
    // printf("\n");
    update(line,tem);
  }

  //-----------------------------------------------------------------------
  glFlush();
  glutSwapBuffers();                           // swap buffers (we earlier set double buffer)
}


//****************************************************
// called by glut when there are no messages to handle
//****************************************************
void myFrameMove() {
  //nothing here for now
#ifdef _WIN32
  Sleep(10);                                   //give ~10ms back to OS (so as not to waste the CPU)
#endif
  glutPostRedisplay(); // forces glut to call the display function (myDisplay())
}


//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 600;
  viewport.h = 600;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Triangle!");

  initScene();                                 // quick function to set up scene

  glutDisplayFunc(myDisplay);                  // function to run when its time to draw something
  glutReshapeFunc(myReshape);                  // function to run when the window gets resized
  glutIdleFunc(myFrameMove);                   // function to run when not handling any other task
  glutMainLoop();                              // infinite loop that will keep drawing and resizing and whatever else

  return 0;
} 







