//
// Created by Linyxy on 16/9/25.
//

#ifndef ASSIGNMENT1_COLOR_H
#define ASSIGNMENT1_COLOR_H

#include <GLFW/glfw3.h>
#include "vec3.cpp"
#include <cmath>



class Color {
    private:
        Vec3 co;
        GLfloat alpha;
    public:
        Color();
        Color(GLfloat r,GLfloat g, GLfloat b,GLfloat alpha);


        GLfloat R();
        GLfloat G();
        GLfloat B();

        Color add();
};


#endif //ASSIGNMENT1_COLOR_H
