//
// Created by Linyxy on 16/9/27.
//

#ifndef ASSIGNMENT1_VEC3_H
#define ASSIGNMENT1_VEC3_H

#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
using namespace std;

class Vec3
{

public:
    GLfloat x,y,z;

public:
    //constructor
    Vec3(GLfloat  x, GLfloat  y, GLfloat  z);
    Vec3();


    //normal vectors
    void zero();
    Vec3 operator-() const;
    void normal();

    GLfloat length() const ;
    //重载
    //add
    Vec3 operator+(Vec3 va) const ;
    Vec3& operator+=(const Vec3 &va);
    //sub
    Vec3 operator-(Vec3 &va) const;
    Vec3 operator-=(Vec3 &va);
    //scale
    Vec3 operator*(GLfloat m) const;
    Vec3& operator*=(GLfloat m);

    Vec3 operator/(GLfloat m) const;

    //dist
    GLfloat  dist(Vec3 &va) const ;
    //dot prodcut
    GLfloat  operator*(Vec3 &va) const;

    Vec3 indi_scale(Vec3 &va) const;
    //cross product
    Vec3 cross(Vec3 &va) const;

    void to_str() const;
};

Vec3 operator*(GLfloat m, Vec3 &va);

#endif //ASSIGNMENT1_VEC3_H
