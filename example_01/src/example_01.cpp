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
dirLight *dllights = new dirLight[MAX_LIGHT_NUM ];
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

//****************************************************
//diffuse component iterate through light sources
//****************************************************
Vec3 diffuse_comp(Vec3 ray_dir,Vec3 nor){
    Vec3 refle = material.diffuse;

    return refle;
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
                normal.normal();//normalize it's self

                Vec3 step_color;
                //ambient component
                step_color = material.ambient.indi_scale(ambient_color.co );

                //diffuse component
                step_color = step_color + diffuse_comp(ray_dirction,normal);
                //specular component

                //color blender
                setPixel(i, j, step_color.x, step_color.y, step_color.z);

                // This is amusing, but it assumes negative Color values are treated reasonably.
                // setPixel(i,j, x/radius, y/radius, z/radius );
                
                // Just for fun, an example of making the boundary pixels yellow.
                // if (dist > (radius-1.0)) {
                //     setPixel(i, j, 1.0, 1.0, 0.0);
                // }
            }

            Vec3 NORMAL =  Vec3();


            //directional light
//            for (int dl_id = 0; dl_id < dl_num; dl_id++) {

//                Vec3 L =  Vec3(directional_light_location[dl_id][0], directional_light_location[dl_id][1], directional_light_location[dl_id][2]);
//                L.inverse();
//                Vec3 V;//TODO
//                Vec3 R = Vec3::sub(2* Vec3::dot(N, Vec3::dot(N, L)), L);
//                GLfloat n;//TODO
//
//                //diffuse + specular
//                red += Vec3::dot(L, NORMAL) * diffuse_color[id][0] * directional_light_color[id][0] * 255 + specular_color[id][0] * directional_light_color[id][0] * pow(Vec3::dot(R, V), n) * 255;
//
//                green += Vec3::dot(L, NORMAL) * diffuse_color[id][1] * directional_light_color[id][1] * 255 + specular_color[id][1] * directional_light_color[id][1] * pow(Vec3::dot(R, V), n) * 255;
//
//                blue += Vec3::dot(L, NORMAL) * diffuse_color[id][2] * directional_light_color[id][2] * 255 + specular_color[id][2] * directional_light_color[id][2] * pow(Vec3::dot(R, V), n) * 255;

//            }
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
Vec3 readingColor(char *argv[],int st_pos){
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
    ambient_color = Color(1.0,1.0,1.0);
    //white light source

    while (i < argc) {
        if (!strcmp(argv[i], "-ka")) {
            i++;
            Vec3 ambient = readingColor(argv,i);
            material.ambient = ambient;
            printf("ambient component:%f %f %f\n",ambient.x,ambient.y,ambient.z);
        }
        else if(!strcmp(argv[i],"-kd")){
            i++;
            Vec3 diffuse = readingColor(argv,i);
            material.diffuse = diffuse;
            printf("ambient component:%f %f %f\n",diffuse.x,diffuse.y,diffuse.z);
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
//        else if()
        i++;
    }
}


//******************
//test for vec3
//******************
void prfloatVec(Vec3 &vec)
{
    cout << "["
         << vec.x << ","
         << vec.y << ","
         << vec.z << "]" << endl;
}


void vec3test(){
    cout << "hello vector" << endl;

    //测试构造函数
    Vec3 v1(10,20,30);
    prfloatVec(v1);

    //测试默认拷贝构造函数
    Vec3 v2(v1);
    prfloatVec(v2);

    //测试负向量
    Vec3 v3 = -v1;
    prfloatVec(v3);

    //测试零向量
    v2.zero();
    prfloatVec(v2);

    //测试计算向量长度
    Vec3 v4(5,-4,7);
    float r = v4.length();
    cout << r << endl;

    //测试向量乘以标量
    Vec3 v5(-5,0,0.4f);
    Vec3 v6 = v5 * (float)-3;
    prfloatVec(v6);

    //测试向量乘等于标量
    v5 *= -3;
    prfloatVec(v5);

    //测试向量除以标量
//    Vec3 v7(4.7f,-6,8);
//    Vec3 v8 = v7 / 2;
//    prfloatVec(v8);

    //测试标量乘以向量
    Vec3 v9(1,2,3);
    Vec3 v10 = 2 * v9;
    prfloatVec(v10);

    //测试向量标准化
    Vec3 v11(12,-5,0);
    v11.normal();
    prfloatVec(v11);

    //测试向量相加
    Vec3 a(1,2,3);
    Vec3 b(4,5,6);
    Vec3 r1 = a + b;
    prfloatVec(r1);

    //测试向量相减
    Vec3 r2 = b - a;
    prfloatVec(r2);

    //测试向量间距离
    Vec3 x(5,0,0);
    Vec3 y(-1,8,0);
    float d = x.dist(y);
    cout << d << endl;

    //向量相乘
    Vec3 h1(3,-2,7);
    Vec3 h2(0,4,-1);
    float dp = h1 * h2;
    cout << dp << endl;

    //两向量间的角度
    float arc = static_cast<float>(acos(dp/(h1.length()*h2.length())) * 180 / 3.14149);
    cout << arc << endl;

    //两向量叉乘
    Vec3 t1(1,3,4);
    Vec3 t2(2,-5,8);
    Vec3 cp = t1.cross(t2);
    prfloatVec(cp);

    system("pause");
//    return 0;
}







//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
    vec3test();
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

