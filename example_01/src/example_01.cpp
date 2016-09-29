//#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

//include header file for glfw library so that we can use OpenGL
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//include libs for the project
#include "Vec3.h"
#include "Color.h"
#include "Material.h"
#include "dirLight.h"
#include "pntLight.h"
#include "Sphere.h"

using namespace std;

#define MAX_LIGHT_NUM  5


#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

#define PI 3.14159265 // Should be used from mathlib

using namespace std;

//****************************************************
// Global Variables
//****************************************************
GLfloat translation[3] = {0.0f, 0.0f, 0.0f};
bool auto_strech = false;
int Width_global = 400;
int Height_global = 400;

Color ambient_color = Color();
Material material;
dirLight *dllights = new dirLight[MAX_LIGHT_NUM];
pntLight *pngtLights = new pntLight[MAX_LIGHT_NUM];
Sphere sphere;
int pl_num = 0, dl_num = 0, sphere_num = 1;


inline float sqr(float x) { return x*x; }


//****************************************************
// Simple init function
//****************************************************
void initializeRendering()
{
    //generate default material
    material = Material();
    glfwInit();
}


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************
void setPixel(float x, float y, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glVertex2f(x+0.5, y+0.5);  // The 0.5 is to target pixel centers
    // Note: Need to check for gap bug on inst machines.
}

//****************************************************
// Keyboard inputs
//****************************************************
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
            
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
        case GLFW_KEY_Q: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
        case GLFW_KEY_LEFT :
            if (action) translation[0] -= 0.01f * Width_global; break;
        case GLFW_KEY_RIGHT:
            if (action) translation[0] += 0.01f * Width_global; break;
        case GLFW_KEY_UP   :
            if (action) translation[1] += 0.01f * Height_global; break;
        case GLFW_KEY_DOWN :
            if (action) translation[1] -= 0.01f * Height_global; break;
        case GLFW_KEY_F:
            if (action) auto_strech = !auto_strech; break;
        case GLFW_KEY_SPACE: break;
            
        default: break;
    }
    
}

static GLfloat max(GLfloat a , GLfloat b){
    if(a>b)return a;
    else return b;
}

GLfloat power(GLfloat a,int p){
    GLfloat r = 1;
    while(p){
        r *= a;
        p--;
    }
    return r;
}

//****************************************************
//diffuse component iterate through light sources
//****************************************************
Vec3 diffuse_comp(Vec3 nor,Vec3 p_on_sphere){
    //nor & ray_dir already normalized
    Vec3 refle = material.diffuse;
    Vec3 result = Vec3();

    //iterate through directional light
    for(int i = 0; i < MAX_LIGHT_NUM; i++){

        GLfloat d = (-dllights[i].direction) * nor;
        Vec3 comp = d * dllights[i].color.co;

        result += comp.indi_scale(refle);

    }

    //iterate through point light
    for(int i = 0; i < MAX_LIGHT_NUM; i++){

        Vec3 lightDir = - p_on_sphere + pngtLights[i].position;
        lightDir.normal();

        result += (pngtLights[i].color.co * max(0.0f, lightDir * nor)).indi_scale(refle);
    }

    return result;
}

//****************************************************
//specular component iterate through light sources
//
// isotropic material
//****************************************************
Vec3 specular_comp(Vec3 nor, Vec3 p_on_sphere){
    //nar & ray_dir already normalized
    Vec3 refle = material.specular;
    Vec3 result = Vec3();
    Vec3 eye = Vec3(0, 0, -1);
    //vector for eye vector
    //deault as 0,0,-1
    //already normalized


    //iterate through directional light
    for(int i = 0; i < MAX_LIGHT_NUM; i++){
        //find r first
        Vec3 l = dllights[i].direction;
        Vec3 r = (-l) + nor * (2*(nor*l));
        r.normal();

        GLfloat k = eye * r;
        k = max(k, 0);
        k = power(k, material.spu);
        Vec3 comp = dllights[i].color.co * k;

        result += comp.indi_scale(refle);
    }

    //iterate through point light
    for (int i = 0; i < MAX_LIGHT_NUM; i++) {
        Vec3 lightDir = - p_on_sphere + pngtLights[i].position;
        Vec3 reflect = (-lightDir) + nor * (2*(nor*lightDir));
        reflect.normal();

        result += (pngtLights[i].color.co * pow(max(0.0f, reflect * eye), material.spu)).indi_scale(refle);

    }

//    result.to_str();
    return result;

}

//****************************************************
// Draw a filled circle.
//****************************************************
void drawCircle(float centerX, float centerY, float radius) {
    // Draw inner circle
    glBegin(GL_POINTS);

    // We could eliminate wasted work by only looping over the pixels
    // inside the sphere's radius.  But the example is more clear this
    // way.  In general drawing an object by loopig over the whole
    // screen is wasteful.

    int minI = max(0,(int)floor(centerX-radius));
    int maxI = min(Width_global-1,(int)ceil(centerX+radius));


    int minJ = max(0,(int)floor(centerY-radius));
    int maxJ = min(Height_global-1,(int)ceil(centerY+radius));

    //as this is orthognal projection
    //the ray is always points to (0,0,-1)
    Vec3 ray_dirction = Vec3(0,0,-1);
    ray_dirction.normal();
    for (int i = 0; i < Width_global; i++) {
        for (int j = 0; j < Height_global; j++) {

            // Location of the center of pixel relative to center of sphere
            float x = (i + 0.5 - centerX);
            float y = (j + 0.5 - centerY);
            GLfloat red = 0, green = 0, blue = 0;


            float dist = sqrt(sqr(x) + sqr(y));

            if (dist <= radius) {

                // This is the front-facing Z coordinate
                float z = sqrt(radius * radius - dist * dist);
                //this is the point on surface
                //this is also the vector of normal
                Vec3 normal = Vec3(x,y,z);
                Vec3 p_sphere = Vec3(x,y,z);
                normal.normal();//normalize it's self

                Vec3 step_color;
                //ambient component
//                step_color = material.ambient.indi_scale(ambient_color.co );

                //diffuse component
//                step_color = step_color + diffuse_comp(normal,p_sphere);
                //specular component
                step_color += specular_comp(normal, p_sphere);
                //color blender
                setPixel(i, j, step_color.x, step_color.y, step_color.z);

                // This is amusing, but it assumes negative Color values are treated reasonably.
                // setPixel(i,j, x/radius, y/radius, z/radius );
                
                // Just for fun, an example of making the boundary pixels yellow.
                // if (dist > (radius-1.0)) {
                //     setPixel(i, j, 1.0, 1.0, 0.0);
                // }
            }




        }
    }

    glEnd();
}

//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void display( GLFWwindow* window )
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); //clear background screen to black
    
    glClear(GL_COLOR_BUFFER_BIT);                // clear the Color buffer (sets everything to black)
    
    glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
    glLoadIdentity();                            // make sure transformation is "zero'd"
    
    //----------------------- code to draw objects --------------------------
    glPushMatrix();
    glTranslatef (translation[0], translation[1], translation[2]);
    drawCircle(Width_global / 2.0 , Height_global / 2.0 , min(Width_global, Height_global) * 0.8 / 2.0);
    glPopMatrix();
    
    glfwSwapBuffers(window);
    
}

//****************************************************
// function that is called when window is resized
//***************************************************
void size_callback(GLFWwindow* window, int width, int height)
{
    // Get the pixel coordinate of the window
    // it returns the size, in pixels, of the framebuffer of the specified window
    glfwGetFramebufferSize(window, &Width_global, &Height_global);
    
    glViewport(0, 0, Width_global, Height_global);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Width_global, 0, Height_global, 1, -1);
    
    display(window);
}


//****************************************************
// function to get input coefficients
//****************************************************
Vec3 readingVector(char **argv, int st_pos){
    GLfloat r = (GLfloat)atof(argv[st_pos]);
    GLfloat g = (GLfloat)atof(argv[st_pos+1]);
    GLfloat b = (GLfloat)atof(argv[st_pos+2]);
    return Vec3(r,g,b);
}


void getInputCoefficients(int argc, char *argv[]) {
    int i = 0;
    //print out all arguments listed
    for(int i=0; i<argc; i++)
    {
//        cout<<"参数序号="<<i<<" ";
        cout<<argv[i];
    }
    cout<<"  arguments listed"<<endl;

    //non-exist ambient color part
    ambient_color = Color(0.0,0.0,0.0);
    //white light source

    while (i < argc) {
        if (!strcmp(argv[i], "-ka")) {
            i++;
            Vec3 ambient = readingVector(argv, i);
            material.ambient = ambient;
            printf("ambient component:%f %f %f\n",ambient.x,ambient.y,ambient.z);
        }
        else if(!strcmp(argv[i],"-kd")){
            i++;
            Vec3 diffuse = readingVector(argv, i);
            material.diffuse = diffuse;
            printf("diffuse component:%f %f %f\n",diffuse.x,diffuse.y,diffuse.z);
        }
        else if(!strcmp(argv[i],"-ks")){
            i++;
            Vec3 diffuse = readingVector(argv, i);
            material.specular = diffuse;
            printf("specular component:%f %f %f\n",diffuse.x,diffuse.y,diffuse.z);
        }
        else if(!strcmp(argv[i],"-spu")){
            i++;
            material.spu = (GLfloat)atof(argv[i]);
            printf("spu compo:%f \n",material.spu);
        }
        else if(!strcmp(argv[i],"-spv")){
            i++;
            material.spv = (GLfloat)atof(argv[i]);
            printf("spv compo:%f \n",material.spv);
        }
        else if(!strcmp(argv[i],"-sp")){
            i++;
            material.spu = (GLfloat)atof(argv[i]);
            printf("sp compo:%f \n",material.spu);
        }
        //adding light source
        else if(!strcmp(argv[i],"-dl")){
            i++;
            Vec3 pos = readingVector(argv, i);
            i+=3;
            Vec3 color = readingVector(argv, i);
            dirLight dl = dirLight(pos,Color(color));
            //put this light into specifc position
            dllights[dl_num] = dl;
            dl_num++;

        }
        else if(!strcmp(argv[i],"-pl")){
            i++;
            Vec3 pos = readingVector(argv, i);
            i+=3;
            Vec3 color = readingVector(argv, i);
            pntLight pl = pntLight(pos,Color(color));
            printf("reading pos");
            pl.position.to_str();
            //put this light into specifc position
            pngtLights[pl_num] = pl;
            pl_num++;
//            pngtLights[0].position.to_str();


        }
        i++;
    }


}










//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
    //    vec3test();
    //This initializes glfw
    initializeRendering();
    getInputCoefficients(argc, argv);
    
    GLFWwindow* window = glfwCreateWindow( Width_global, Height_global, "CS184", NULL, NULL );
    if ( !window )
    {
        cerr << "Error on window creating" << endl;
        glfwTerminate();
        return -1;
    }
    
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if ( !mode )
    {
        cerr << "Error on getting monitor" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent( window );
    
    // Get the pixel coordinate of the window
    // it returns the size, in pixels, of the framebuffer of the specified window
    glfwGetFramebufferSize(window, &Width_global, &Height_global);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Width_global, 0, Height_global, 1, -1);
    
    glfwSetWindowTitle(window, "CS184");
    glfwSetWindowSizeCallback(window, size_callback);
    glfwSetKeyCallback(window, key_callback);
    
    while( !glfwWindowShouldClose( window ) ) // infinite loop to draw object again and again
    {   // because once object is draw then window is terminated
        display( window );
        
        if (auto_strech){
            glfwSetWindowSize(window, mode->width, mode->height);
            glfwSetWindowPos(window, 0, 0);
        }
        
        glfwPollEvents();
        
    }

    return 0;
}

